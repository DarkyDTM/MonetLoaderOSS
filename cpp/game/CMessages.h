#pragma once

#include "gta_struct.inl"
namespace CMessages {
inline std::uint16_t* GetBuffer()
{
	static std::uint16_t buffer[256];
	return buffer;
}

inline void AddBigMessage(std::uint16_t* gxt, std::uint32_t time, std::uint16_t style)
{
	return GTA_FUNC_AT(AddBigMessage, lib_manager::add_big_message)(gxt, time, style);
}

inline void AddMessage(const char* unk, std::uint16_t* gxt, std::uint32_t time, std::uint16_t flags, bool add_to_prev_brief)
{
	return GTA_FUNC_AT(AddMessage, lib_manager::add_message)(unk, gxt, time, flags, add_to_prev_brief);
}

inline void AddMessageJumpQ(const char* unk, std::uint16_t* gxt, std::uint32_t time, std::uint16_t flags, bool add_to_prev_brief)
{
	return GTA_FUNC_AT(AddMessageJumpQ, lib_manager::add_message_jumpq)(unk, gxt, time, flags, add_to_prev_brief);
}

}
#include "gta_struct.inl"
