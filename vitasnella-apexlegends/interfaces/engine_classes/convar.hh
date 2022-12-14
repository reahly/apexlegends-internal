#pragma once
#include "../../utilities/utils.hh"

struct cvar {
	char pad_0x0000[0x8]; //0x0000
	cvar* next; //0x0008 
	__int64 registered; //0x0010 
	char* convar_name; //0x0018 
	char* descrption; //0x0020 
	char pad_0x0028[0x28]; //0x0028
	char* default_value; //0x0050 
	char* current_value; //0x0058 
	__int64 string_length; //0x0060 
	float fvalue; //0x0068 
	__int32 value; //0x006C 
	__int32 has_min; //0x0070 
	float min_value; //0x0074 
	__int32 has_max; //0x0078 
	float max_value; //0x007C 
};

struct convar_t {
	cvar* find_var( const char* name ) {
		return utils::get_vfunc<16, cvar*>( this, name );
	}
};
