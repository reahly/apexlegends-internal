#pragma once
#include <lazy_importer.hh>
#include <Windows.h>
#include <xorstr.hh>
#include "../utilities/utils.hh"
#include "engine_classes/chl_client.hh"
#include "engine_classes/global_vars.hh"
#include "engine_classes/input_system.hh"
#include "engine_classes/engine_trace_client.hh"
#include "engine_classes/client_state.hh"
#include "engine_classes/input.hh"
#include "engine_classes/convar.hh"
#include "engine_classes/client_entity_list.hh"
#include "engine_classes/engine_client.hh"

namespace interfaces {
	inline engine_trace_client_t* engine_trace_client;
	inline chl_client_t* chl_client;
	inline global_vars_t* global_vars;
	inline input_system_t* input_system;
	inline client_state_t* client_state;
	inline input_t* input;
	inline convar_t* convar;
	inline client_entity_list_t* client_entity_list;
	inline engine_client_t* engine_client;
	inline uintptr_t file_system;
	inline uint8_t* send_packet;
	
	static void* find_interface( const char* name ) {
		const auto* addr = utils::find_pattern( _( "E9 ? ? ? ? CC CC 89 91 ? ? ? ?" ) );
		if ( !addr )
			return nullptr;

		return reinterpret_cast<void*( __stdcall* )( const char*, int* )>( addr )( name, nullptr );
	}

	inline void init( ) {
		chl_client = reinterpret_cast<chl_client_t*>( RESOLVE_RVA( utils::find_pattern( _( "48 8D 0D ? ? ? ? 48 8B 05 ? ? ? ? 4C 8D 05 ? ? ? ?" ) ) ) );
		global_vars = reinterpret_cast<global_vars_t*>( RESOLVE_RVA( utils::find_pattern( _( "4C 8D 05 ? ? ? ? 48 8D 15 ? ? ? ? 41 FF D1" ) ) ) );
		input_system = reinterpret_cast<input_system_t*>( RESOLVE_RVA( utils::find_pattern( _( "48 8D 0D ? ? ? ? 85 FD" ) ) ) );
		client_state = reinterpret_cast<client_state_t*>( RESOLVE_RVA( utils::find_pattern( _( "48 8D 0D ? ? ? ? FF 50 48 48 8B 03" ) ) ) );
		input = reinterpret_cast<input_t*>( RESOLVE_RVA( utils::find_pattern( _( "48 8D 0D ? ? ? ? 33 D2 FF 90 ? ? ? ? 88 1D ? ? ?" ) ) ) );
		engine_trace_client = static_cast<engine_trace_client_t*>( find_interface( _( "EngineTraceClient004" ) ) );
		convar = reinterpret_cast<convar_t*>( RESOLVE_RVA( utils::find_pattern( _( "48 89 05 ? ? ? ? 48 83 C4 28 C3 CC CC CC CC CC CC 48 83 EC 28 48 8D 05 ? ? ? ?" ) ) ) );
		client_entity_list = static_cast<client_entity_list_t*>( find_interface( _( "VClientEntityList003" ) ) );
		engine_client = reinterpret_cast<engine_client_t*>( RESOLVE_RVA( utils::find_pattern( _( "48 89 05 AA 01 3D 00 ? ? ? ? ? ? ?" ) ) ) );
		file_system = RESOLVE_RVA( utils::find_pattern( _( "48 89 05 ? ? ? ? 48 8D 0D ? ? ? ? 48 8D 05 ? ? ? ? 48 89 05 ? ? ? ? E9 ? ? ? ?" ) ) );

		send_packet = utils::find_pattern( _( "40 B6 01 4C 89 AC 24 ? ? ? ?" ) ) + 0x2;
		DWORD old;
		LI_FN( VirtualProtect ).cached( )( reinterpret_cast<void*>( send_packet ), 0x1, PAGE_EXECUTE_READWRITE, &old );
	}
}
