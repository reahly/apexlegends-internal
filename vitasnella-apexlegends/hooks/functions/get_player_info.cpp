#include <xorstr.hh>
#include "../hooks.hh"
#include "../../settings.hh"
#include "../../interfaces/engine_classes/engine_client.hh"

bool __fastcall hooks::get_player_info( void* rcx, const int num, void* info ) {	
	const auto ret = original_get_player_info( rcx, num, info );

	if ( settings::misc_hide_names )
		strcpy( static_cast<player_info_t*>( info )->name, _( "hidden name" ) );

	return ret;
}
