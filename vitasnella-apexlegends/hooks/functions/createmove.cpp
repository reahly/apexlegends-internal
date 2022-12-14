#include "../hooks.hh"
#include "../../settings.hh"
#include "../../classes/entity.hh"
#include "../../features/aimbot.hh"
#include "../../features/antiaim.hh"
#include "../../features/misc.hh"
#include "../../features/skinchanger.hh"
#include "../../interfaces/interfaces.hh"

bool __fastcall hooks::createmove( input_t* input, const int sequence_number, const float sample_time, const bool activate ) {
	const auto ret = original_createmove( input, sequence_number, sample_time, activate );
	
	auto* const cmd = input->get_user_cmd( -1, sequence_number );
	if ( !cmd || !cmd->command_number )
		return ret;

	utils::global::send_packet = true;

	const auto old_view = cmd->viewangles;
	const auto old_move = cmd->move;

	aimbot::init( cmd );
	antiaim::init( cmd );
	misc::init( cmd );
	skinchanger::init( );

	if ( auto* local_player = entity_t::get_local_player( ); settings::aimbot_silent == 2 && local_player && local_player->alive( ) ) {
		static auto chockes = int( );

		if ( auto* weapon = local_player->get_active_weapon( ) ) {
			if ( cmd->buttons & in_attack && weapon->fire_ready( ) && ++chockes <= 14 )  
				utils::global::send_packet = false;
			else {
				utils::global::send_packet = true;
				cmd->viewangles = old_view;
				cmd->move = old_move;
				chockes = 0;
			}
		}
	}

	cmd->viewangles.clamp( );
	*reinterpret_cast<bool*>( interfaces::send_packet ) = utils::global::send_packet;
	return ret;
}
