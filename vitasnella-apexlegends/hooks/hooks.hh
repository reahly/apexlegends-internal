#pragma once
#include "../interfaces/engine_classes/input.hh"
#include <D3D11.h>

typedef bool( __fastcall* createmove_fn )( void*, int, float, bool );
typedef void ( __fastcall* present_fn )( void*, void* );
typedef bool( __thiscall* get_player_info_fn )( void*, int, void* );
typedef bool( __fastcall* lookup_file_fn )( void*, const char*, uintptr_t );
inline IDXGISwapChain* swapchain;

namespace hooks {
	void init( );

	bool __fastcall createmove( input_t*, int, float, bool );
	inline createmove_fn original_createmove = nullptr;

	void __fastcall present( void*, void* );
	inline present_fn original_present = nullptr;

	bool __fastcall get_player_info( void*, int, void* );
	inline get_player_info_fn original_get_player_info;

	bool __fastcall lookup_file( void*, const char*, uintptr_t );
	inline lookup_file_fn original_lookup_file;
}