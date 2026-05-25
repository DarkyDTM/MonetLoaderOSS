#pragma once
#include <cstdint>

struct CControllerState
{
  std::int16_t LeftStickX;
  std::int16_t LeftStickY;
  std::int16_t RightStickX;
  std::int16_t RightStickY;
  std::int16_t LeftShoulder1;
  std::int16_t LeftShoulder2;
  std::int16_t RightShoulder1;
  std::int16_t RightShoulder2;
  std::int16_t DPadUp;
  std::int16_t DPadDown;
  std::int16_t DPadLeft;
  std::int16_t DPadRight;
  std::int16_t Start;
  std::int16_t Select;
  std::int16_t ButtonSquare;
  std::int16_t ButtonTriangle;
  std::int16_t ButtonCross;
  std::int16_t ButtonCircle;
  std::int16_t ShockButtonL;
  std::int16_t ShockButtonR;
  std::int16_t m_bChatIndicated;
  std::int16_t m_bPedWalk;
  std::int16_t m_bVehicleMouseLook;
  std::int16_t m_bRadioTrackSkip;
};
