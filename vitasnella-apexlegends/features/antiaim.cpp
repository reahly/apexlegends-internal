#include "antiaim.hh"
#include "../settings.hh"
#include "../classes/entity.hh"
#include "../interfaces/interfaces.hh"

void antiaim::init( usercmd* cmd ) {
	const auto allow = [ & ]( ) {
		auto* local_player = entity_t::get_local_player( );
		if ( !local_player || !local_player->alive( ) )
			return false;

		const auto* const weapon = local_player->get_active_weapon( );
		if ( !weapon )
			return false;

		if ( cmd->buttons & ( in_attack | in_use ) || local_player->velocity( ).length_2d( ) > 0 )
			return false;

		return true;
	};

	if ( !settings::antiaim_enabled || !allow( ) )
		return;

	auto input = vec3_t( );
	switch ( settings::antiaim_pitch_type ) {
	case 0:
		input.x = 89.f;
		break;
	case 1:
		input.x = -89.f;
		break;
	case 2:
		input.x = 1800089;
		break;
	case 3:
		input.x = 0.f;
		break;
	case 4:
		input.x = -270.f;
		break;

	default: break;
	}

	switch ( settings::antiaim_yaw_type ) {
	case 0:
		input.y += 180.0f;
		break;
	case 1:
		input.y += 323210000.0f;
		break;
	case 2:
		input.y += interfaces::global_vars->curtime * ( 500 * 1000 );
		break;
	case 3: {
		static vec3_t angle;
		angle.y += 50;
		input.y = angle.y;

		break;
	}

	default: break;
	}

	cmd->viewangles = input;
}
