#pragma once
#include "CVector.h"
#include "CCamera.h"
#include "RenderWare.h"
#include "lib_manager.h"

#include "gta_struct.inl"
namespace game {
struct ScreenCoors {
  bool result;
  CVector pos;
  float scale_x, scale_y;
};
inline ScreenCoors CalcScreenCoors(const CVector& world, bool check_fc = false, bool check_nc = false)
{
  ScreenCoors result {};
  result.result = reinterpret_cast<int (*)(const CVector&, CVector*, float, float, int, int)>(
                      lib_manager::calc_screen_coors)(world, &result.pos, result.scale_x, result.scale_y, check_fc, check_nc)
      != 0;
  return result;
}

inline CVector CalcWorldCoors(CVector screen)
{
  CMatrix invView = CCamera::GetCamera()->m_viewMatrix.Inverted();
  float fRecip = 1.0f / screen.z;
  screen.x /= fRecip * static_cast<float>(rw::RsGlobal()->screenWidth);
  screen.y /= fRecip * static_cast<float>(rw::RsGlobal()->screenHeight);

  return screen * invView + invView.pos;
}

inline void AsciiToGxtChar(const char* ascii, std::uint16_t* gxt)
{
  return GTA_FUNC_AT(AsciiToGxtChar, lib_manager::ascii_to_gxt_char)(ascii, gxt);
}

inline char* GxtCharToAscii(std::uint16_t* gxt, std::uint8_t shift = 0)
{
  return GTA_FUNC_AT(GxtCharToAscii, lib_manager::gxt_char_to_ascii)(gxt, shift);
}

inline bool IsPaused()
{
  return *reinterpret_cast<bool*>(lib_manager::pause_1) || *reinterpret_cast<bool*>(lib_manager::pause_2);
}
}
#include "gta_struct.inl"