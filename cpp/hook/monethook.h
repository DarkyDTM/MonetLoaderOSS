#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

namespace monethook {
namespace detail {
  enum class hook_result {
    hook_is_dummy,
    already_hooked,
    not_hooked,
    backend_error,
    success
  };
  void write_code(void* dest, const void* src, std::size_t size);
  void write_got(void* dest, const void* src, std::size_t size);
  hook_result hook(void* symbol, void* replace, void** trampoline);
  hook_result unhook(void* symbol);
}

// ------ Libraries ------

namespace library_map {
  struct segment {
    std::uintptr_t start;
    std::uintptr_t end;
    std::uintptr_t offset;
    std::uint8_t dev_major;
    std::uint8_t dev_minor;
    std::uint32_t inode;
    bool r;
    bool w;
    bool x;
    bool s;
  };

  struct entry {
    std::uintptr_t start;
    std::uintptr_t end;
    std::vector<segment> segments;
  };

  [[nodiscard]] inline std::unordered_map<std::string, entry>& get()
  {
    static std::unordered_map<std::string, entry> map;
    return map;
  }

  inline bool find(std::uintptr_t addr, std::string* library_name = nullptr, segment* seg = nullptr)
  {
    bool found = false;

    for (auto& i : get()) {
      if (i.second.start <= addr && addr <= i.second.end) {
        if (library_name != nullptr) {
          *library_name = i.first;
        }
        if (seg == nullptr) {
          found = true;
          break;
        }
        for (auto& j : i.second.segments) {
          if (j.start <= addr && addr <= j.end) {
            *seg = j;
            found = true;
            break;
          }
        }
      }
    }

    return found;
  }

  void snapshot();
}

// ------ Memory ------

template <typename T>
void replace_got(std::uintptr_t address, T* replace)
{
  monethook::detail::write_got(reinterpret_cast<void*>(address), &replace, sizeof(replace));
}

class plt_scanner {
  public:
  plt_scanner(std::uintptr_t base, const char* path);

  bool ok();
  std::uintptr_t sym(const char* name);

  private:
  unsigned char* lib {};
  std::uintptr_t min_va { static_cast<std::uintptr_t>(-1) };
  std::uintptr_t reltype {};
  std::uintptr_t symtab {}, hashtab {}, strtab {}, reltab {}, relatab {}, jmpreltab {}, ghashtab {};
  std::uintptr_t relsize {}, relasize{}, jmprelsize{}, symcnt {};
  bool inited {};
};

namespace scanner {
  enum class result {
    library_not_found,
    match_not_found,
    success
  };

  [[nodiscard]] std::pair<result, std::uintptr_t> pattern_scan(std::uintptr_t start, std::uintptr_t end, std::string_view pattern);
  [[nodiscard]] inline std::pair<result, std::uintptr_t> pattern_scan(const std::string& library, std::string_view pattern)
  {
    auto lib = monethook::library_map::get().find(library);
    if (lib == monethook::library_map::get().end())
      return { monethook::scanner::result::library_not_found, 0 };

    for (auto& i : lib->second.segments) {
      if (!i.r)
        continue;

      auto res = pattern_scan(i.start, i.end, pattern);
      if (res.first == monethook::scanner::result::success) {
        return res;
      }
    }

    return { monethook::scanner::result::match_not_found, 0 };
  }
}

// ------ Hooking ------

template <typename... T>
class hook;

template <typename R, typename... Args>
class hook<R(Args...)> {
  public:
  using result = monethook::detail::hook_result;
  using func_ptr = R (*)(Args...);


  hook()
      : address_(0)
      , replace_(nullptr)
      , trampoline_(0)
  {
  }
  hook(std::uintptr_t address, func_ptr replace)
      : address_(address)
      , replace_(replace)
      , trampoline_(0)
  {
  }
  hook(hook&& from) noexcept
      : hooked_(from.hooked_)
      , address_(from.address_)
      , replace_(from.replace_)
      , trampoline_(from.trampoline_)
  {
    from.hooked_ = false;
    from.address_ = 0;
    from.replace_ = nullptr;
    from.trampoline_ = nullptr;
  }

  hook& operator=(hook&& from) noexcept
  {
    hooked_ = from.hooked_;
    address_ = from.address_;
    replace_ = from.replace_;
    trampoline_ = from.trampoline_;

    from.hooked_ = false;
    from.address_ = 0;
    from.replace_ = nullptr;
    from.trampoline_ = nullptr;

    return *this;
  }

  // Copying not allowed.

  hook(const hook&) = delete;
  hook& operator=(const hook&) = delete;


  result apply()
  {
    if (address_ == 0)
      return result::hook_is_dummy;
    if (hooked_)
      return result::already_hooked;

    auto res = monethook::detail::hook(reinterpret_cast<void*>(address_), reinterpret_cast<void*>(replace_), reinterpret_cast<void**>(&trampoline_));
    if (res == result::success)
      hooked_ = true;

    return res;
  }

  result restore()
  {
    if (!hooked_)
      return result::not_hooked;

    auto res = monethook::detail::unhook(reinterpret_cast<void*>(address_));
    if (res == result::success)
      hooked_ = false;

    return res;
  }

  bool applied()
  {
    return hooked_;
  }

  R operator()(Args... args)
  {
    return trampoline_(std::forward<Args>(args)...);
  }

  private:
  bool hooked_ = false;
  std::uintptr_t address_;
  func_ptr replace_;
  func_ptr trampoline_;
};

template <>
class hook<> {
  public:
  using result = monethook::detail::hook_result;
};

template <typename... T>
class plt_hook;

template <typename R, typename... Args>
class plt_hook<R(Args...)> {
  public:
  using result = monethook::detail::hook_result;
  using func_ptr = R (*)(Args...);

  plt_hook()
      : address_(0)
      , replace_(nullptr)
      , trampoline_(0)
  {
  }
  plt_hook(std::uintptr_t address, func_ptr replace)
      : address_(address)
      , replace_(replace)
      , trampoline_(0)
  {
  }
  plt_hook(plt_hook&& from) noexcept
      : hooked_(from.hooked_)
      , address_(from.address_)
      , replace_(from.replace_)
      , trampoline_(from.trampoline_)
  {
    from.hooked_ = false;
    from.address_ = 0;
    from.replace_ = nullptr;
    from.trampoline_ = nullptr;
  }

  plt_hook& operator=(plt_hook&& from) noexcept
  {
    hooked_ = from.hooked_;
    address_ = from.address_;
    replace_ = from.replace_;
    trampoline_ = from.trampoline_;

    from.hooked_ = false;
    from.address_ = 0;
    from.replace_ = nullptr;
    from.trampoline_ = nullptr;

    return *this;
  }

  // Copying not allowed.

  plt_hook(const plt_hook&) = delete;
  plt_hook& operator=(const plt_hook&) = delete;

  result apply()
  {
    if (address_ == 0)
      return result::hook_is_dummy;
    if (hooked_)
      return result::already_hooked;

    std::memcpy(reinterpret_cast<void*>(&trampoline_), reinterpret_cast<void*>(address_), sizeof(std::uintptr_t));
    monethook::detail::write_got(reinterpret_cast<void*>(address_), reinterpret_cast<void*>(&replace_), sizeof(std::uintptr_t));
    hooked_ = true;
    return result::success;
  }

  result restore()
  {
    if (!hooked_)
      return result::not_hooked;

    monethook::detail::write_got(reinterpret_cast<void*>(address_), reinterpret_cast<void*>(&trampoline_), sizeof(std::uintptr_t));
    hooked_ = false;
    return result::success;
  }

  bool applied()
  {
    return hooked_;
  }

  R operator()(Args... args)
  {
    return trampoline_(std::forward<Args>(args)...);
  }

  private:
  bool hooked_ = false;
  std::uintptr_t address_;
  func_ptr replace_;
  func_ptr trampoline_;
};

template <>
class plt_hook<> {
  public:
  using result = monethook::detail::hook_result;
};
}
