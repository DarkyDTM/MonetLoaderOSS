#pragma once
#include "imgui/imgui.h"
#include <string>
#include <vector>

class keyboard {
  public:
  static keyboard& instance()
  {
    static keyboard inst;
    return inst;
  }

  void show(ImGuiIO* a_io, ImGuiStyle* a_style)
  {
    shown = true;
    io = a_io;
    style = a_style;
    layout = layout_type::en;
    caps = caps_type::none;
  }

  void hide()
  {
    shown = false;
    reset_keys();
  }

  void render(bool disable_movement = false);

  private:
  enum class layout_type {
    en,
    ru,
    special
  };
  enum class caps_type {
    none,
    single,
    lock
  };

  keyboard() = default;

  const std::vector<std::string>& get_num_row()
  {
    if (caps == caps_type::single && layout != layout_type::special) {
      return num_caps;
    }
    return num;
  }
  const std::vector<std::vector<std::string>>& get_lang_rows()
  {
    if (layout == layout_type::en) {
      if (caps == caps_type::none) {
        return en;
      } else {
        return en_caps;
      }
    } else if (layout == layout_type::special) {
      return special;
    } else if (layout == layout_type::ru) {
      if (caps == caps_type::none) {
        return ru;
      } else {
        return ru_caps;
      }
    }

    return en;
  }
  void on_character(const std::string& character);

  void reset_keys()
  {
    io->KeysDown[ImGuiKey_Backspace] = false;
    io->KeysDown[ImGuiKey_Enter] = false;
    io->KeysDown[ImGuiKey_A] = false;
    io->KeysDown[ImGuiKey_C] = false;
    io->KeysDown[ImGuiKey_V] = false;
    io->KeysDown[ImGuiKey_X] = false;
    io->KeysDown[ImGuiKey_Y] = false;
    io->KeysDown[ImGuiKey_Z] = false;
    io->KeyCtrl = false;
  }

  bool shown { false };
  ImGuiIO* io { nullptr };
  ImGuiStyle* style { nullptr };
  layout_type layout { layout_type::en };
  layout_type old_layout { layout_type::en }; // for special layout
  caps_type caps { caps_type::none };

  const std::vector<std::string> num {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"
  };
  const std::vector<std::string> num_caps {
    "!", "@", "#", "$", "%", "^", "&", "*", "(", ")"
  };

  const std::vector<std::vector<std::string>> en {
    { "q", "w", "e", "r", "t", "y", "u", "i", "o", "p" },
    { "a", "s", "d", "f", "g", "h", "j", "k", "l" },
    { "z", "x", "c", "v", "b", "n", "m" }, // +2: caps & backspace
    { ",", "." } // fixed layout
  };
  const std::vector<std::vector<std::string>> en_caps {
    { "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P" },
    { "A", "S", "D", "F", "G", "H", "J", "K", "L" },
    { "Z", "X", "C", "V", "B", "N", "M" }, // +2: caps & backspace
    { ",", "." } // fixed layout
  };

  const std::vector<std::vector<std::string>> ru {
    { "й", "ц", "у", "к", "е", "н", "г", "ш", "щ", "з", "х" },
    { "ф", "ы", "в", "а", "п", "р", "о", "л", "д", "ж", "э" },
    { "я", "ч", "с", "м", "и", "т", "ь", "б", "ю" }, // +2: caps & backspace
    { "ё", "ъ" } // fixed layout
  };
  const std::vector<std::vector<std::string>> ru_caps {
    { "Й", "Ц", "У", "К", "Е", "Н", "Г", "Ш", "Щ", "З", "Х" },
    { "Ф", "Ы", "В", "А", "П", "Р", "О", "Л", "Д", "Ж", "Э" },
    { "Я", "Ч", "С", "М", "И", "Т", "Ь", "Б", "Ю" }, // +2: caps & backspace
    { "Ё", "Ъ" } // fixed layout
  };

  const std::vector<std::vector<std::string>> special {
    { "@", "#", "$", "_", "&", "-", "+", "(", ")", "/" },
    { "*", "\"", "'", ":", ";", "!", "?", "~", "`" },
    { "|", "^", "=", "\\", "%", "[", "]", "{", "}" }, // +2: caps & backspace
    { ",", "." } // fixed layout
  };
};