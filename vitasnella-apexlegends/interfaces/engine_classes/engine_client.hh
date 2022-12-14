#pragma once
#include "../../utilities/utils.hh"

struct player_info_t {
	char name[128];
};

struct engine_client_t {
	bool in_game( ) {
		return utils::get_vfunc<46, bool>( this );
	}

	bool get_player_info( const int num, player_info_t* info ) {
		return utils::get_vfunc<24, bool>( this, num, info );
	}
};