#include "aimbot.hh"
#include <iostream>
#include <lazy_importer.hh>
#include "../settings.hh"
#include "../classes/entity.hh"
#include "../interfaces/interfaces.hh"
#include "../utilities/prediction.hh"
#include "../utilities/vec3.hh"

entity_t* closest_enemy( usercmd* cmd, entity_t* local_player, weapon_t* weapon ) {
	const auto fov_scale = [&]( ) {
		if ( local_player->zooming( ) )
			if ( weapon->zoom_fov( ) != 0.0f && weapon->zoom_fov( ) != 1.0f )
				return weapon->zoom_fov( ) / 90.0f;

		return 1.0f;
	};
	
	if ( !local_player || !local_player->alive( ) )
		return nullptr;

	entity_t* best_entity = nullptr;
	auto fov = settings::aimbot_fov * fov_scale( );
	
	for ( auto i = 1; i < 100; i++ ) {
		auto* const entity = entity_t::get_client_entity( i );
		if ( !entity || !entity->alive( ) || entity->team_number( ) == local_player->team_number( ) )
			continue;

		auto target_position = entity->get_bone_position( 12 );
		const auto calculated_fov = utils::get_fov( cmd->viewangles, utils::calc_angle( entity_t::camera_position( ), target_position ) );
		if ( calculated_fov > fov )
			continue;

		if ( settings::aimbot_visible && !entity->is_visible( entity_t::camera_position( ), target_position ) )
			continue;

		if ( settings::aimbot_downed && entity->knocked( ) != 0 )
			continue;

		fov = calculated_fov;
		best_entity = entity;
	}

	return best_entity;
}

void aimbot::init( usercmd* cmd ) {
	auto* local_player = entity_t::get_local_player( );
	if ( !settings::aimbot_enabled || !LI_FN( GetAsyncKeyState ).cached( )( settings::aimbot_bind ) || !local_player || !local_player->alive( ) )
		return;
	
	auto* const weapon = local_player->get_active_weapon( );
	if ( !weapon )
		return;

	auto* entity = closest_enemy( cmd, local_player, weapon );
	if ( !entity || !entity->alive( ) )
		return;

	prediction::prediction_ctx prediction_ctx{ };
	if ( weapon->bullet_speed( ) > 1.0f ) {
		if ( !solve( entity, weapon, prediction_ctx ) )
			return;	
	} else {
		const auto calc_angle = utils::calc_angle( entity_t::camera_position( ), entity->get_bone_position( 12 ) );
		prediction_ctx = prediction::prediction_ctx{ calc_angle.x, calc_angle.y, 0.f };
	}
	
	auto aimangle = vec3_t( weapon->bullet_speed( ) > 1.0f ? -RAD2DEG( prediction_ctx.pitch ) : prediction_ctx.pitch, weapon->bullet_speed( ) > 1.0f ? RAD2DEG( prediction_ctx.yaw ) : prediction_ctx.yaw, 0.f );
	if ( settings::misc_norecoil && local_player->aimpunch( ).x != 0.f ) {
		aimangle -= local_player->aimpunch( );
		aimangle -= local_player->dynamic_angles( ) - local_player->aimpunch( ) - cmd->viewangles;
	}

	aimangle.clamp( );
		
	const auto smooth = [ & ]( vec3_t& src, vec3_t& dst, const float factor ) {
		auto delta = dst - src;
		delta.clamp( );
		dst = src + delta / factor;
	};

	const auto smooth_val = std::max( settings::aimbot_smooth, settings::aimbot_silent == 2 ? 0 : 1 );
	if ( smooth_val > 0 ) 
		smooth( local_player->viewangles( ), aimangle, smooth_val );

	aimangle.clamp( );

	settings::aimbot_silent == 0 ? local_player->viewangles( ) = aimangle : cmd->viewangles = aimangle;

	if ( settings::aimbot_autofire && weapon->fire_ready( ) ) 
		cmd->buttons |= in_attack;
}
