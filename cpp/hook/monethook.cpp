// ----- monethook Implementation -----

#include "monethook.h"
#ifdef __arm__
#include "backend32/inlineHook.h"
#elif defined(__aarch64__)
#include "backend64/And64InlineHook.hpp"
#endif
#include <dlfcn.h>
#include <elf.h>
#include <fstream>
#include <link.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sstream>

#ifdef __APPLE__
extern "C" void sys_icache_invalidate(const void* start, std::size_t len);
#endif

namespace {
/**
 * @brief Clears cache at \p start so that new instructions will be executed.
 *
 * @param start Address to clear cache at.
 * @param len Length of fragment at which cache clear is required.
 */
void clear_cache(void* start, std::size_t len)
{
#ifdef __APPLE__
  sys_icache_invalidate(start, len);
#elif defined(__GNUC__)
  __builtin___clear_cache(reinterpret_cast<char*>(start), reinterpret_cast<char*>(reinterpret_cast<std::uintptr_t>(start) + len));
#else
#error "Cannot find clear cache function"
#endif
}

void protect_memory(void* dest, std::size_t size, int prot)
{
  static std::size_t page_size = sysconf(_SC_PAGE_SIZE);
  static auto page_size_mask = ~static_cast<uintptr_t>(page_size - 1);

  void* start = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(dest) & page_size_mask);
  std::size_t protect_size = (reinterpret_cast<std::uintptr_t>(dest) + size - reinterpret_cast<std::uintptr_t>(start) + page_size - 1) & page_size_mask;

  mprotect(start, protect_size, prot);
  clear_cache(start, protect_size);
}
}

void monethook::detail::write_code(void* dest, const void* src, std::size_t size)
{
  protect_memory(dest, size, PROT_READ | PROT_WRITE | PROT_EXEC);
  std::memcpy(dest, src, size);
  // protect_memory(start, size, PROT_READ | PROT_EXEC);
}

void monethook::detail::write_got(void* dest, const void* src, std::size_t size)
{
  protect_memory(dest, size, PROT_READ | PROT_WRITE);
  std::memcpy(dest, src, size);
  // protect_memory(start, size, PROT_READ | PROT_EXEC);
}

monethook::detail::hook_result monethook::detail::hook(void* symbol, void* replace, void** trampoline)
{
#ifdef __arm__
  ele7en_status status = registerInlineHook(reinterpret_cast<std::uint32_t>(symbol), reinterpret_cast<std::uint32_t>(replace), reinterpret_cast<std::uint32_t**>(trampoline));
  if (status != ELE7EN_OK) {
    if (status == ELE7EN_ERROR_ALREADY_REGISTERED || status == ELE7EN_ERROR_ALREADY_HOOKED) {
      return hook_result::already_hooked;
    }

    return hook_result::backend_error;
  }

  if (inlineHook(reinterpret_cast<std::uint32_t>(symbol)) != ELE7EN_OK)
    return hook_result::backend_error;

  return hook_result::success;

#elif defined(__aarch64__)
  A64HookError err = A64HookFunction(symbol, replace, trampoline);
  if (err != A64_HOOK_SUCCESS) {
    if (err == A64_HOOK_ALREADY_HOOKED) {
      return hook_result::already_hooked;
    }

    return hook_result::backend_error;
  }

  return hook_result::success;
#endif
}

monethook::detail::hook_result monethook::detail::unhook(void* symbol)
{
#ifdef __arm__
  ele7en_status status = inlineUnHook(reinterpret_cast<std::uint32_t>(symbol));
  if (status != ELE7EN_OK) {
    if (status == ELE7EN_ERROR_NOT_HOOKED) {
      return hook_result::not_hooked;
    }

    return hook_result::backend_error;
  }

  return hook_result::success;

#elif defined(__aarch64__)
  A64HookError err = A64UnHookFunction(symbol);
  if (err != A64_HOOK_SUCCESS) {
    if (err == A64_HOOK_NOT_HOOKED) {
      return hook_result::not_hooked;
    }

    return hook_result::backend_error;
  }

  return hook_result::success;
#endif
}

void monethook::library_map::snapshot()
{
  auto& map = get();
  map.clear();
  std::ifstream ifs { "/proc/self/maps" };
  segment seg;
  char sep, c_r, c_w, c_x, c_s;
  std::uint16_t temp_1, temp_2;
  std::string s, path;
  while (std::getline(ifs, s)) {
    std::istringstream iss { s };

    iss >> std::hex >> seg.start >> sep >> seg.end >> c_r >> c_w >> c_x >> c_s >> seg.offset >> temp_1 >> sep >> temp_2 >> std::dec >> seg.inode >> std::ws;
    std::getline(iss, path);

    if (path.length() == 0) {
      continue;
    }

    seg.dev_major = static_cast<std::uint8_t>(temp_1);
    seg.dev_minor = static_cast<std::uint8_t>(temp_2);
    seg.r = c_r == 'r';
    seg.w = c_w == 'w';
    seg.x = c_x == 'x';
    seg.s = c_s == 's';

    if (!map.count(path))
      map[path] = { seg.start, seg.end, { seg } };
    else {
      entry& e = map[path];
      if (seg.start < e.start) {
        e.start = seg.start;
      }
      if (seg.end > e.end) {
        e.end = seg.end;
      }

      e.segments.push_back(seg);
    }
  }
}

namespace {
std::uint8_t char_to_hex(const char c)
{
  if (c >= '0' && c <= '9')
    return static_cast<std::uint8_t>(c - '0');
  else {
    char lower = c | 0x20; // ASCII hack to convert to lower case
    return static_cast<std::uint8_t>(lower - 'a' + 10);
  }
}
}

std::pair<monethook::scanner::result, std::uintptr_t> monethook::scanner::pattern_scan(std::uintptr_t start, std::uintptr_t end, std::string_view pattern)
{
  struct pattern_scan_byte {
    bool first_nibble_any;
    bool second_nibble_any;
    std::uint8_t byte;
  };

  if (pattern.size() < 2)
    return { monethook::scanner::result::match_not_found, 0 };

  std::vector<pattern_scan_byte> bytes {};
  bytes.reserve((pattern.size() + 2) / 3);

  int read = 0;
  pattern_scan_byte current_byte { false, false, 0 };
  for (char i : pattern) {
    if (i != ' ' && i != '\t' && i != '\n') {
      if (read == 0) {
        if (i == '?') {
          current_byte.first_nibble_any = true;
        } else {
          current_byte.byte |= char_to_hex(i) << 4;
        }
      } else {
        if (i == '?') {
          current_byte.second_nibble_any = true;
        } else {
          current_byte.byte |= char_to_hex(i);
        }
      }
      ++read;
    }

    if (read == 2) {
      bytes.push_back(current_byte);
      current_byte.first_nibble_any = current_byte.second_nibble_any = false;
      current_byte.byte = 0;
      read = 0;
    }
  }

  std::size_t j = 0;
  std::uintptr_t match = 0;
  bool done = false;
  for (std::uintptr_t i = start; i < end; ++i) {
    if (j >= bytes.size()) {
      done = true;
      break;
    }

    unsigned char data = *reinterpret_cast<unsigned char*>(i);
    pattern_scan_byte byte = bytes[j];

    if ((byte.first_nibble_any && byte.second_nibble_any)
        || (byte.first_nibble_any && (data & 0x0F) == (byte.byte & 0x0F))
        || (byte.second_nibble_any && (data & 0xF0) == (byte.byte & 0xF0))
        || (data == byte.byte)) {
      if (match == 0) {
        match = i;
      }
      ++j;
    } else {
      if (match != 0) {
        i = match;
        match = 0;
      }
      j = 0;
    }
  }

  return { done ? monethook::scanner::result::success : monethook::scanner::result::match_not_found, match };
}

monethook::plt_scanner::plt_scanner(std::uintptr_t base, const char* path)
{
  lib = reinterpret_cast<unsigned char*>(base);
  ElfW(Dyn)* dyn = nullptr;

  // main path: calculate dyn VA by reading headers from ELF file
  std::ifstream ifs { path, std::ios::binary };
  if (ifs.is_open() && ifs) {
    ElfW(Ehdr) hdr;
    if (ifs.read(reinterpret_cast<char*>(&hdr), sizeof(hdr))
        && ifs.seekg(static_cast<std::ifstream::off_type>(hdr.e_phoff), std::ios::beg)) {
      ElfW(Addr) dyn_va = 0;

      ElfW(Phdr) pht;
      for (std::size_t i = 0; i < hdr.e_phnum; ++i) {
        if (!ifs.seekg(hdr.e_phoff + static_cast<std::ifstream::off_type>(i) * sizeof(pht), std::ios::beg)
            || !ifs.read(reinterpret_cast<char*>(&pht), sizeof(pht))) {
          break;
        }

        min_va = std::min<std::uintptr_t>(min_va, pht.p_vaddr);

        if (pht.p_type != PT_DYNAMIC)
          continue;
        dyn_va = pht.p_vaddr;
      }

      if (dyn_va != 0) {
        dyn = reinterpret_cast<ElfW(Dyn)*>(&lib[dyn_va - min_va]);
      }
    }
  }
  ifs.clear();
  ifs.close();

  // fallback: assume phoff == vaddroff (in most cases true)
  if (!dyn) {
    ElfW(Addr) dyn_va = 0;

    auto* hdr = reinterpret_cast<ElfW(Ehdr)*>(lib);
    auto* pht = reinterpret_cast<ElfW(Phdr)*>(&lib[hdr->e_phoff]);
    for (std::size_t i = 0; i < hdr->e_phnum; ++i, ++pht) {
      min_va = std::min<std::uintptr_t>(min_va, pht->p_vaddr);

      if (pht->p_type != PT_DYNAMIC)
        continue;
      dyn_va = pht->p_vaddr;
    }

    if (dyn_va != 0) {
      dyn = reinterpret_cast<ElfW(Dyn)*>(&lib[dyn_va - min_va]);
    }
  }

  if (!dyn) {
    inited = false;
    return;
  }

  for (; dyn->d_tag != DT_NULL; dyn++) {
    switch (dyn->d_tag) {
    case DT_SYMTAB: {
      symtab = dyn->d_un.d_ptr - min_va;
      break;
    }
    case DT_HASH: {
      hashtab = dyn->d_un.d_ptr - min_va;
      break;
    }
    case DT_STRTAB: {
      strtab = dyn->d_un.d_ptr - min_va;
      break;
    }
    case DT_REL: {
      reltab = dyn->d_un.d_ptr - min_va;
      break;
    }
    case DT_RELSZ: {
      relsize = dyn->d_un.d_val;
      break;
    }
    case DT_RELA: {
      relatab = dyn->d_un.d_ptr - min_va;
      break;
    }
    case DT_RELASZ: {
      relasize = dyn->d_un.d_val;
      break;
    }
    case DT_JMPREL: {
      jmpreltab = dyn->d_un.d_ptr - min_va;
      break;
    }
    case DT_GNU_HASH: {
      ghashtab = dyn->d_un.d_ptr - min_va;
      break;
    }
    case DT_PLTREL: {
      reltype = dyn->d_un.d_val;
      break;
    }
    case DT_PLTRELSZ: {
      jmprelsize = dyn->d_un.d_val;
      break;
    }
    default: {
      break;
    }
    }
  }

  if (!symtab || !strtab || !reltype
      || (reltype == DT_REL && (!reltab || !relsize)) || (reltype == DT_RELA && (!relatab || !relasize))
      || !jmpreltab || !jmprelsize || (!hashtab && !ghashtab)) {
    inited = false;
    return;
  }

  if (hashtab) {
    symcnt = reinterpret_cast<ElfW(Word)*>(&lib[hashtab])[1];
  } else {
    auto* ghashtab_data = reinterpret_cast<std::uint32_t*>(&lib[ghashtab]);
    auto* buckets = ghashtab_data + 4 + (ghashtab_data[2] * (sizeof(ElfW(Addr)) / sizeof(std::uint32_t))); // NOLINT
    auto nbuckets = ghashtab_data[0];

    std::uint32_t last_symbol = 0;
    for (std::uint32_t i = 0; i < nbuckets; ++i) {
      std::uint32_t bucket = buckets[i];
      if (last_symbol <= bucket) {
        last_symbol = bucket;
      }
    }

    if (last_symbol == 0) {
      inited = false;
      return;
    }

    last_symbol -= ghashtab_data[1];
    std::uint32_t* chain = buckets + nbuckets + last_symbol;
    do {
      ++last_symbol;
    } while (!(*chain++ & 1));
    symcnt = last_symbol;
  }

  inited = true;
}

bool monethook::plt_scanner::ok()
{
  return inited;
}

std::uintptr_t monethook::plt_scanner::sym(const char* name)
{
  if (!inited) {
    return 0;
  }

  bool found = false;
  std::size_t index = 0;
  auto* sym = reinterpret_cast<ElfW(Sym)*>(&lib[symtab]);
  for (std::size_t i = 0; i < symcnt; ++i, ++sym) {
    const char* symname = reinterpret_cast<char*>(&lib[strtab + sym->st_name]);
    if (!std::strcmp(symname, name)) {
      found = true;
      index = i;
      break;
    }
  }

  if (!found) {
    return 0;
  }

  if (reltype == DT_RELA) {
    auto* rela = reinterpret_cast<ElfW(Rela)*>(&lib[relatab]);
    auto* jmprela = reinterpret_cast<ElfW(Rela)*>(&lib[jmpreltab]);

    for (std::size_t i = 0; i < relasize / sizeof(ElfW(Rela)); ++i, ++rela) {
#ifdef __arm__
      if (ELF32_R_SYM(rela->r_info) != index)
        continue;
#elif defined(__aarch64__)
      if (ELF64_R_SYM(rela->r_info) != index)
        continue;
#else
#error "Unknown platform"
#endif

      return reinterpret_cast<std::uintptr_t>(&lib[rela->r_offset - min_va]);
    }

    for (std::size_t i = 0; i < jmprelsize / sizeof(ElfW(Rela)); ++i, ++jmprela) {
#ifdef __arm__
      if (ELF32_R_SYM(jmprela->r_info) != index)
        continue;
#elif defined(__aarch64__)
      if (ELF64_R_SYM(jmprela->r_info) != index)
        continue;
#else
#error "Unknown platform"
#endif

      return reinterpret_cast<std::uintptr_t>(&lib[jmprela->r_offset - min_va]);
    }
  } else {
    auto* rel = reinterpret_cast<ElfW(Rel)*>(&lib[reltab]);
    auto* jmprel = reinterpret_cast<ElfW(Rel)*>(&lib[jmpreltab]);

    for (std::size_t i = 0; i < relsize / sizeof(ElfW(Rel)); ++i, ++rel) {
#ifdef __arm__
      if (ELF32_R_SYM(rel->r_info) != index)
        continue;
#elif defined(__aarch64__)
      if (ELF64_R_SYM(rel->r_info) != index)
        continue;
#else
#error "Unknown platform"
#endif

      return reinterpret_cast<std::uintptr_t>(&lib[rel->r_offset - min_va]);
    }

    for (std::size_t i = 0; i < jmprelsize / sizeof(ElfW(Rel)); ++i, ++jmprel) {
#ifdef __arm__
      if (ELF32_R_SYM(jmprel->r_info) != index)
        continue;
#elif defined(__aarch64__)
      if (ELF64_R_SYM(jmprel->r_info) != index)
        continue;
#else
#error "Unknown platform"
#endif

      return reinterpret_cast<std::uintptr_t>(&lib[jmprel->r_offset - min_va]);
    }
  }

  return 0;
}