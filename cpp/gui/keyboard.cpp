#include "keyboard.h"
#include "imgui/imgui.h"

void keyboard::render(bool disable_movement)
{
  if (!shown) {
    return;
  }

  reset_keys();

#ifndef NEW_INPUT_SYSTEM
  const ImVec2 display_size { ImGui::GetIO().DisplaySize };
  const float min_x_spacing { display_size.x * 0.005f };
  const float min_y_spacing { display_size.y * 0.005f };
  const float bottom_padding { display_size.y * 0.025f };

  // inherit color from calling style
  ImGui::PushStyleColor(ImGuiCol_WindowBg, style->Colors[ImGuiCol_WindowBg]);
  ImGui::PushStyleColor(ImGuiCol_Button, style->Colors[ImGuiCol_Button]);
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, style->Colors[ImGuiCol_ButtonHovered]);
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, style->Colors[ImGuiCol_ButtonActive]);
  ImGui::PushStyleColor(ImGuiCol_ResizeGrip, style->Colors[ImGuiCol_ResizeGrip]);
  ImGui::PushStyleColor(ImGuiCol_ResizeGripHovered, style->Colors[ImGuiCol_ResizeGripHovered]);
  ImGui::PushStyleColor(ImGuiCol_ResizeGripActive, style->Colors[ImGuiCol_ResizeGripActive]);
  ImGui::PushStyleColor(ImGuiCol_Text, style->Colors[ImGuiCol_Text]);

  float font_size = display_size.x * 0.015f;
  float font_scale = font_size / ImGui::GetFontSize();
  if (ImGui::GetFontSize() < font_size) {
    font_scale = std::min(font_size / ImGui::GetFontSize(), 2.f);
    font_size = ImGui::GetFontSize() * font_scale;
  }

  const float min_row_height { font_size + ImGui::GetStyle().FramePadding.y * 2.f + min_y_spacing };
  const float default_row_height { display_size.y * 0.07f };
  ImGui::SetNextWindowSizeConstraints(
      ImVec2 { display_size.x * 0.4f, 6.f * min_row_height + 2.f * min_y_spacing + bottom_padding },
      ImVec2 { display_size.x, display_size.y });
  ImGui::SetNextWindowSize(ImVec2 { display_size.x * 0.7f, 6.f * default_row_height + 2.f * min_y_spacing + bottom_padding }, ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowPos(ImVec2 { display_size.x * 0.5f, display_size.y * 0.9f }, ImGuiCond_FirstUseEver, ImVec2 { 0.5f, 1.f });
  ImGui::Begin("Keyboard", nullptr,
      ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | (disable_movement ? ImGuiWindowFlags_NoMove : 0));

  if (font_scale != 1.f) {
    ImGui::SetWindowFontScale(font_scale);
  }

  const float cr_height = ImGui::GetWindowContentRegionMax().y - ImGui::GetWindowContentRegionMin().y;
  const float cr_width = ImGui::GetWindowContentRegionWidth();
  const float x_spacing { std::max(cr_width * 0.005f, min_x_spacing) };
  const float y_spacing { std::max(cr_height * 0.008f, min_y_spacing) };
  const float row_height { (cr_height - bottom_padding - y_spacing) / 6.f };
  const float row_height_spaced { row_height - y_spacing };
  const float cr_width_mx = cr_width + x_spacing;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2 { x_spacing, y_spacing });
  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2 { x_spacing, (row_height_spaced - font_size) * 0.5f });
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2 { x_spacing, y_spacing });

  const float max_key_width { cr_width_mx * 0.1f };
  const float max_key_width_spaced { max_key_width - x_spacing };

  // special keys
  const ImVec2 spkey_size { cr_width_mx / 6.f - x_spacing, row_height_spaced };

  if (ImGui::Button("copy", spkey_size)) {
    io->KeyCtrl = true;
    io->KeysDown[ImGuiKey_C] = true;
  }
  ImGui::SameLine();
  if (ImGui::Button("paste", spkey_size)) {;
    io->KeyCtrl = true;
    io->KeysDown[ImGuiKey_V] = true;
  }
  ImGui::SameLine();
  if (ImGui::Button("cut", spkey_size)) {
    io->KeyCtrl = true;
    io->KeysDown[ImGuiKey_X] = true;
  }
  ImGui::SameLine();
  if (ImGui::Button("all", spkey_size)) {
    io->KeyCtrl = true;
    io->KeysDown[ImGuiKey_A] = true;
  }
  ImGui::SameLine();
  if (ImGui::Button("undo", spkey_size)) {
    io->KeyCtrl = true;
    io->KeysDown[ImGuiKey_Z] = true;
  }
  ImGui::SameLine();
  if (ImGui::Button("redo", spkey_size)) {
    io->KeyCtrl = true;
    io->KeysDown[ImGuiKey_Y] = true;
  }

  // programmable

  const auto& num_row { get_num_row() };
  for (const auto& i : num_row) {
    if (ImGui::Button(i.c_str(), ImVec2 { max_key_width_spaced, row_height_spaced })) {
      on_character(i);
    }
    ImGui::SameLine();
  }
  ImGui::NewLine();

  const auto& lang { get_lang_rows() };
  for (int i = 0; i < 3; ++i) { // last row is manually layouted
    const std::size_t keys { lang[i].size() + (i == 2 ? 2 : 0) };
    const float key_width { std::min(cr_width_mx / static_cast<float>(keys), max_key_width) };
    const float key_width_spaced { key_width - x_spacing };
    const float side_space { key_width == max_key_width ? (cr_width_mx - static_cast<float>(keys) * key_width) * 0.5f : 0 };
    const ImVec2 side_size { key_width_spaced + side_space, row_height_spaced };
    const ImVec2 normal_size { key_width_spaced, row_height_spaced };

    if (i == 2) {
      const char* key { "caps" };
      if (caps == caps_type::single) {
        key = "Caps";
      } else if (caps == caps_type::lock) {
        key = "CAPS";
      }

      if (ImGui::Button(key, side_size)) {
        if (caps == caps_type::none) {
          caps = caps_type::single;
        } else {
          caps = caps_type::none;
        }
      }
      if (ImGui::IsItemActive() && ImGui::IsMouseDoubleClicked(0)) {
        caps = caps_type::lock;
      }

      ImGui::SameLine();
    }

    for (std::size_t j = 0; j < lang[i].size(); ++j) {
      ImVec2 size { normal_size };
      if ((j == 0 || j == lang[i].size() - 1) && i != 2) {
        size = side_size;
      }

      if (ImGui::Button(lang[i][j].c_str(), size)) {
        on_character(lang[i][j]);
      }
      ImGui::SameLine();
    }

    if (i == 2) {
      if (ImGui::Button("back", side_size) || ImGui::IsItemActive()) {
        io->KeysDown[ImGuiKey_Backspace] = true;
      }
      ImGui::SameLine();
    }

    ImGui::NewLine();
  }

  // last row
  {
    const ImVec2 small_size { cr_width_mx * 0.1f - x_spacing, row_height_spaced };
    const ImVec2 big_size { cr_width_mx * 0.15f - x_spacing, row_height_spaced };
    const ImVec2 space_size { cr_width_mx * 0.4f - x_spacing, row_height_spaced };

    if (layout != layout_type::special) {
      if (ImGui::Button("?123", big_size)) {
        old_layout = layout;
        layout = layout_type::special;
      }
    } else {
      if (ImGui::Button("abc", big_size)) {
        layout = old_layout;
      }
    }
    ImGui::SameLine();
    if (ImGui::Button(lang[3][0].c_str(), small_size)) {
      on_character(lang[3][0]);
    }
    ImGui::SameLine();
    if (ImGui::Button("lang", small_size)) {
      layout_type& layout_var = layout == layout_type::special ? old_layout : layout;
      if (layout_var == layout_type::en) {
        layout_var = layout_type::ru;
      } else if (layout_var == layout_type::ru) {
        layout_var = layout_type::en;
      }
    }
    ImGui::SameLine();
    if (ImGui::Button("space", space_size)) {
      on_character(" ");
    }
    ImGui::SameLine();
    if (ImGui::Button(lang[3][1].c_str(), small_size)) {
      on_character(lang[3][1]);
    }
    ImGui::SameLine();
    if (ImGui::Button("enter", big_size)) {
      io->KeysDown[ImGuiKey_Enter] = true;
    }
  }

  ImGui::PopStyleVar(3);
  ImGui::End();
  ImGui::PopStyleColor(8);
#endif
}

void keyboard::on_character(const std::string& character)
{
  io->AddInputCharactersUTF8(character.c_str());

  if (caps == caps_type::single) {
    caps = caps_type::none;
  }
}