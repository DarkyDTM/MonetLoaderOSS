#pragma once

// ALYN: 0x27C4F0 + 0x1, 0x141948 + 0x1, "\xF0\xB5\x03\xAF", 0x180A0C + 0x1, 528

// libGTASA.so (only needed for SAMP)
#define OFF_NVEVENTINSERTNEWEST_FOR_SAMP (0x27C4F0 + 0x1)

// libsamp.so
// Scan: F0 B5 03 AF 2D E9 00 07 88 B0 0D 46 ?? ?? 91 46 ?? ?? 04 46 00 20 79 44 7A 44
// #define OFF_CNETGAME_CTOR (0x302458 + 0x1)
// #define OFF_CNETGAME_CTOR_CHECK_MAGIC "\xF0\xB5\x03\xAF"

// Scan: F0 B5 03 AF 2D E9 00 ?? ?? B0 04 46 00 68 C1 6A 20 46 88 47
// #define OFF_RAKPEER_RECEIVEIGNORERPC (0x350B3C + 0x1)

// Pretty much constant
#define OFF_RAKCLIENTINTERFACE 528