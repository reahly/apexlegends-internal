#include "esp.hh"
#include <iostream>
#include <lazy_importer.hh>
#include <string>
#include <xorstr.hh>
#include "../settings.hh"
#include "../classes/entity.hh"
#include "../imgui/imgui.h"
#include "../interfaces/interfaces.hh"
#include "../utilities/color.hh"
#include "../utilities/renderer.hh"

bool calculate_box( entity_t* e, box_data& box ) {
	vec3_t min, max;
	e->renderable( )->get_render_bounds( min, max );

	vec3_t pos;
	auto pos_3d = e->origin( ) - vec3_t( 0, 0, 10 );

	vec3_t top;

	if ( const auto top_3d = pos_3d + vec3_t( 0, 0, max.z + 10 ); !utils::world_to_screen( pos_3d, pos ) || !utils::world_to_screen( top_3d, top ) )
		return false;

	const auto height = pos.y - top.y;
	const auto width = height / 2;

	box.x = pos.x - width / 2;
	box.y = top.y;
	box.w = width;
	box.h = height;

	return true;
}

void esp::init( ) {
	auto* local_player = entity_t::get_local_player( );
	if ( !local_player || !local_player->alive( ) )
		return;

	if ( settings::misc_showfov )
		render::circle( ImGui::GetIO( ).DisplaySize.x / 2, ImGui::GetIO( ).DisplaySize.y / 2, settings::aimbot_fov * 9, settings::aimbot_fov * 8, ImColor( 255, 255, 255, 100 ) );

	for ( auto i = 1; i < 100; i++ ) {
		auto* const entity = entity_t::get_client_entity( i );
		if ( !entity || !entity->alive( ) || entity->team_number( ) == local_player->team_number( ) )
			continue;
		
		auto* const weapon = entity->get_active_weapon( );
		if ( !weapon )
			continue;

		const auto distance = sqrt( pow( local_player->origin( ).x - entity->origin( ).x, 2 ) + pow( local_player->origin( ).y - entity->origin( ).y, 2 ) + pow( local_player->origin( ).z - entity->origin( ).z, 2 ) ) * 0.0254f;
		if ( distance >= settings::esp_maxdistance )
			continue;

		auto data = box_data{ };
		if ( !calculate_box( entity, data ) )
			continue;

		if ( settings::visuals_box )
			render::rect( ImVec2( data.x, data.y ), ImVec2( data.w, data.h ), ImGui::GetColorU32( ImVec4( settings::visuals_box_color[0], settings::visuals_box_color[1], settings::visuals_box_color[2], settings::visuals_box_color[3] ) ) );

		const auto health_color = color( ).hsv_to_rgb( entity->health( ) + 25, 1, 1, 255 );
		if ( settings::visuals_healthbar ) {
			const auto health_calc = std::clamp( entity->health( ) * data.h / 100, 0, data.h );

			render::filled_rect( ImVec2( data.x - 5, data.y - 1 ), ImVec2( 3, data.h + 2 ), IM_COL32( 10, 10, 10, 255 ) );
			render::filled_rect( ImVec2( data.x - 4, data.y + data.h - health_calc ), ImVec2( 1, health_calc ), ImGui::GetColorU32( ImVec4( health_color.r, health_color.g, health_color.b, 255 ) ) );
		}

		if ( settings::visuals_name || settings::visuals_distance ) {
			const auto* const name = entity->get_name( );
			
			static ImVec4 color_use;
			color_use = utils::find_string( name, _( "ttv" ) ) != -1 || utils::find_string( name, _( "twitch" ) ) != -1 || utils::find_string( name, _( "tv" ) ) != -1 ? ImVec4( 255, 0, 0, 255 ) : ImVec4( settings::visuals_name_color[0], settings::visuals_name_color[1], settings::visuals_name_color[2], settings::visuals_name_color[3] );

			std::string string_to_draw_name;
			if ( settings::visuals_name && settings::visuals_distance )
				string_to_draw_name = std::string( name ).append( _( " [" ) ).append( std::to_string( static_cast<int>( distance ) ).append( _( "m" ) ).append( _( "]" ) ) );
			else if ( settings::visuals_name && !settings::visuals_distance )
				string_to_draw_name = std::string( name );
			else
				string_to_draw_name = std::to_string( static_cast<int>( distance ) ).append( _( "m" ) );

			render::text( string_to_draw_name.c_str( ), ImVec2( data.x + data.w / 2, data.y - 15 ), 13.f, ImGui::GetColorU32( color_use ), true );
		}
		
		const auto weapon_pos = settings::visuals_shieldbar ? 3 : -2;
		if ( settings::visuals_weapon )
			render::text( weapon->get_weapon_name( ).c_str( ), ImVec2( data.x + data.w / 2, data.y + data.h + 1 + weapon_pos ), 13.f, ImGui::GetColorU32( ImVec4( settings::visuals_weapon_color[0], settings::visuals_weapon_color[1], settings::visuals_weapon_color[2], settings::visuals_weapon_color[3] ) ), true );

		if ( settings::visuals_shieldbar && entity->shield_health( ) != 0 && entity->shield_max_health( ) != 0 ) {
			const auto width = entity->shield_health( ) * data.w / entity->shield_max_health( );

			render::rect( ImVec2( data.x - 1, data.y + data.h + 3 ), ImVec2( data.w + 2, 4 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 ) ) );
			render::filled_rect( ImVec2( data.x, data.y + data.h + 4 ), ImVec2( data.w, 2 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 * 0.85 ) ) );
			render::filled_rect( ImVec2( data.x, data.y + data.h + 4 ), ImVec2( width, 2 ), ImGui::GetColorU32( ImVec4( settings::visuals_shieldbar_color[0], settings::visuals_shieldbar_color[1], settings::visuals_shieldbar_color[2], settings::visuals_shieldbar_color[3] ) ) );	
		}
	}
}
