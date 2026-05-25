#pragma once
#include "CVector.h"
#include <cstdint>

struct CEntity;

struct CNodeAddress {
  std::uint16_t Region;
  std::uint16_t Index;
};

struct CLinkAddress {
  std::uint16_t CarPathLinkId : 10;
  std::uint16_t AreaId : 6;
};

struct CAutoPilot {
  CNodeAddress OldNode;
  CNodeAddress NewNode;
  CNodeAddress VeryOldNode;
  std::int32_t TimeToLeaveLink;
  std::int32_t TimeToGetToNextLink;
  CLinkAddress OldLink;
  CLinkAddress NewLink;
  CLinkAddress VeryOldLink;
  std::uint32_t LastTimeNotStuck;
  std::uint32_t LastTimeMoving;
  std::int8_t InvertDirVeryOldLink;
  std::int8_t InvertDirOldLink;
  std::int8_t InvertDirNewLink;
  std::int8_t OldLane;
  std::int8_t NewLane;
  std::int8_t DrivingMode;
  std::int8_t Mission;
  std::int8_t TempAction;
  std::uint32_t TempActionFinish;
  std::uint32_t LastTimeWeStartedTempActReverse;
  std::uint8_t WhatToTryForReverse;
  std::uint8_t NumTimesWantingToChangeNodes;
  float ActualSpeed;
  float MaxSpeedBuffer;
  std::uint8_t CruiseSpeed;
  std::int8_t SpeedFromNodes;
  float SpeedMultiplier;
  std::uint8_t HooverDistFromTarget;
  std::int8_t SpeedCheat;
  std::int8_t AimAheadOfTarget;
  std::uint8_t SlowingDownForCar : 1;
  std::uint8_t SlowingDownForPed : 1;
  std::uint8_t AvoidLevelTransitions : 1;
  std::uint8_t bAlwaysInFastLane : 1;
  std::uint8_t bAlwaysInSlowLane : 1;
  std::uint8_t bWarnTargetEntity : 1;
  std::uint8_t bDontGoAgainstTraffic : 1;
  std::uint8_t bLeaveAfterAWhile : 1;
  std::uint8_t bWaitForValidNodes : 1;
  std::uint8_t bCarHasToReverseFirst : 1;
  std::uint8_t AISwitchToStraightLineDistance;
  std::uint8_t FollowCarDistance;
  std::uint8_t TargetReachedDist;
  std::int8_t LaneChangeCounter;
  std::int8_t FramesFloating;
  std::int16_t ConstrainAreaMinX;
  std::int16_t ConstrainAreaMaxX;
  std::int16_t ConstrainAreaMinY;
  std::int16_t ConstrainAreaMaxY;
  CVector TargetCoors;
  CNodeAddress aPathNodeList[8];
  std::int16_t NumPathNodes;
  CEntity* pTargetEntity;
  CEntity* pObstructingEntity;
  std::int8_t RecordingNumber;
  std::int8_t Diversion;
};
