#include "visuals.hh"
#include <chrono>
#include <unordered_map>
#include <vector>
#include <array>
#include "../settings.hh"
#include "../classes/entity.hh"
#include "../interfaces/interfaces.hh"
#include "../utilities/renderer.hh"

void glow( ) {
	const auto health_color = [ ]( const int health ) {
		static vec3_t color;

		if ( health >= 50 )
			color = vec3_t( 0.f, 1.f, 0.f );
		if ( health <= 50 && health >= 20 )
			color = vec3_t( 1.f, 1.f, 0.f );
		if ( health <= 20 )
			color = vec3_t( 1.f, 0, 0 );

		return color;
	};

	auto* const local_player = entity_t::get_local_player( );
	if ( !settings::visuals_glow || !local_player || !local_player->alive( ) )
		return;

	for ( auto i = 1; i < 100; i++ ) {
		auto* const entity = entity_t::get_client_entity( i );
		if ( !entity || !entity->alive( ) || entity->team_number( ) == local_player->team_number( ) )
			continue;

		entity->glow.enable( ) = true;
		entity->glow.enable2( ) = 1;
		entity->glow.colors( ) = settings::visuals_glow_healthbased ? health_color( entity->health( ) ) : vec3_t( settings::visuals_glow_color[0] / 255, settings::visuals_glow_color[1] / 255, settings::visuals_glow_color[2] / 255 );
		entity->glow.distance( ) = settings::visuals_distance;

		for ( auto i = 0x2F8; i <= 0x328; i += 0x4 ) // limit = Script_Highlight_HideInside first offset
			*reinterpret_cast<float*>( reinterpret_cast<uintptr_t>( entity ) + i ) = FLT_MAX;
	}
}

void glow_item( ) {
	auto* const local_player = entity_t::get_local_player( );
	if ( !settings::visuals_loot_glow || !local_player || !local_player->alive( ) )
		return;

	for ( auto i = 0; i < interfaces::client_entity_list->get_highest_entity_index( ); i++ ) {
		auto* const items = entity_t::get_client_entity( i );
		if ( !items )
			continue;

		const auto* const identifier = items->identifier( );
		if ( !identifier || !*identifier )
			continue;

		if ( !strcmp( identifier, _( "prop_survival" ) ) ) {
			items->glow.enable( ) = true;
			items->glow.distance( ) = FLT_MAX;
			items->glow.time( ) = FLT_MAX;
			items->glow.colors( ) = vec3_t( 1.f, 0.f, 0.f );
			items->glow.style( ) = 0x51408A89;
		}
	}
}

void item_esp( ) {
	const auto scale = [ ]( float input, const float min, const float max, const float omin, const float omax ) {
		if ( input < min )
			input = min;

		if ( input > max )
			input = max;

		return omin + ( input - min ) * ( omax - omin ) / ( max - min );
	};

	std::unordered_map<int, std::pair<rarity, std::string>> items {
		{ 2, { rarity::common, _( "Mastiff" ) } },
		{ 82, { rarity::common, _( "Eva-8" ) } },
		{ 88, { rarity::common, _( "Mozambique" ) } },
		{ 88, { rarity::common, _( "Mozambique" ) } },
		{ 87, { rarity::heirloom, _( "Peacekeeper" ) } },
		{ 52, { rarity::heirloom, _( "Prowler" ) } },
		{ 1, { rarity::heirloom, _( "Kraber" ) } },
		{ 7, { rarity::common, _( "L-Star" ) } },
		{ 12, { rarity::common, _( "Havoc" ) } },
		{ 17, { rarity::common, _( "Devotion" ) } },
		{ 57, { rarity::common, _( "Volt" ) } },
		{ 22, { rarity::common, _( "Triple Take" ) } },
		{ 62, { rarity::common, _( "Longbow" ) } },
		{ 67, { rarity::common, _( "Charge Rifle" ) } },
		{ 108, { rarity::common, _( "Sentinel" ) } },
		{ 93, { rarity::common, _( "Wingman" ) } },
		{ 72, { rarity::common, _( "Spitfire" ) } },
		{ 32, { rarity::common, _( "Hemlock" ) } },
		{ 27, { rarity::common, _( "Flatline" ) } },
		{ 37, { rarity::common, _( "G7 Scout" ) } },
		{ 42, { rarity::common, _( "Alternator" ) } },
		{ 47, { rarity::common, _( "R-99" ) } },
		{ 77, { rarity::common, _( "Carbine" ) } },
		{ 98, { rarity::common, _( "P2020" ) } },
		{ 103, { rarity::common, _( "Re-45" ) } },
		{ 123, { rarity::common, _( "Shield Cell" ) } },
		{ 122, { rarity::rare, _( "Shield Battery" ) } },
		{ 121, { rarity::common, _( "Syringe" ) } },
		{ 120, { rarity::rare, _( "Med Kit" ) } },
		{ 119, { rarity::epic, _( "Phoenix Kit" ) } },
		{ 131, { rarity::legendary, _( "Body Shield" ) } },
		{ 130, { rarity::epic, _( "Body Shield" ) } },
		{ 129, { rarity::rare, _( "Body Shield" ) } },
		{ 128, { rarity::common, _( "Body Shield" ) } },
		{ 136, { rarity::legendary, _( "Evo Body Shield" ) } },
		{ 135, { rarity::epic, _( "Evo Body Shield" ) } },
		{ 134, { rarity::rare, _( "Evo Body Shield" ) } },
		{ 133, { rarity::common, _( "Evo Body Shield" ) } },
		{ 127, { rarity::legendary, _( "Helmet" ) } },
		{ 126, { rarity::epic, _( "Helmet" ) } },
		{ 125, { rarity::rare, _( "Helmet" ) } },
		{ 124, { rarity::common, _( "Helmet" ) } },
		{ 144, { rarity::legendary, _( "Backpack" ) } },
		{ 143, { rarity::epic, _( "Backpack" ) } },
		{ 142, { rarity::rare, _( "Backpack" ) } },
		{ 141, { rarity::common, _( "Backpack" ) } },
		{ 140, { rarity::legendary, _( "Knockdown Shield" ) } },
		{ 139, { rarity::epic, _( "Knockdown Shield" ) } },
		{ 138, { rarity::rare, _( "Knockdown Shield" ) } },
		{ 137, { rarity::common, _( "Knockdown Shield" ) } },
		{ 179, { rarity::epic, _( "Standard Stock" ) } },
		{ 178, { rarity::rare, _( "Standard Stock" ) } },
		{ 177, { rarity::common, _( "Standard Stock" ) } },
		{ 177, { rarity::epic, _( "Quickdraw Holster" ) } },
		{ 186, { rarity::epic, _( "Double Tap Trigger" ) } },
		{ 185, { rarity::epic, _( "Hammerpoint Rounds" ) } },
		{ 164, { rarity::epic, _( "Extended Light Mag" ) } },
		{ 163, { rarity::rare, _( "Extended Light Mag" ) } },
		{ 162, { rarity::common, _( "Extended Light Mag" ) } },
		{ 161, { rarity::legendary, _( "Barrel Stabilizer" ) } },
		{ 160, { rarity::epic, _( "Barrel Stabilizer" ) } },
		{ 159, { rarity::rare, _( "Barrel Stabilizer" ) } },
		{ 158, { rarity::common, _( "Barrel Stabilizer" ) } },
		{ 113, { rarity::common, _( "Light Rounds" ) } },
		{ 147, { rarity::common, _( "Arc Star" ) } },
		{ 146, { rarity::common, _( "Frag Grenade" ) } },
		{ 145, { rarity::common, _( "Thermite Grenade" ) } },
		{ 116, { rarity::common, _( "Heavy Rounds" ) } },
		{ 117, { rarity::common, _( "Sniper Ammo" ) } },
		{ 114, { rarity::common, _( "Energy Ammo" ) } },
		{ 115, { rarity::common, _( "Shotgun Shells" ) } },
		{ 183, { rarity::legendary, _( "Turbocharger" ) } },
		{ 170, { rarity::epic, _( "Extended Energy Mag" ) } },
		{ 169, { rarity::rare, _( "Extended Energy Mag" ) } },
		{ 168, { rarity::common, _( "Extended Energy Mag" ) } },
		{ 152, { rarity::legendary, _( "1X Digital Threat" ) } },
		{ 151, { rarity::rare, _( "1X-2X Variable Hold" ) } },
		{ 150, { rarity::common, _( "1X Hold" ) } },
		{ 149, { rarity::rare, _( "2X Hcog Bruiser" ) } },
		{ 148, { rarity::common, _( "1X Hcog Classic" ) } },
		{ 154, { rarity::epic, _( "2X-4X Variable Aog" ) } },
		{ 153, { rarity::epic, _( "3X Hcog Ranger" ) } },
		{ 176, { rarity::epic, _( "Shotgun Bolt" ) } },
		{ 175, { rarity::rare, _( "Shotgun Bolt" ) } },
		{ 174, { rarity::common, _( "Shotgun Bolt" ) } },
		{ 118, { rarity::rare, _( "Ultimate Accelerant" ) } },
		{ 182, { rarity::epic, _( "Sniper Stock" ) } },
		{ 181, { rarity::rare, _( "Sniper Stock" ) } },
		{ 180, { rarity::common, _( "Sniper Stock" ) } },
		{ 173, { rarity::epic, _( "Extended Sniper Mag" ) } },
		{ 172, { rarity::rare, _( "Extended Sniper Mag" ) } },
		{ 171, { rarity::common, _( "Extended Sniper Mag" ) } },
		{ 157, { rarity::legendary, _( "4X-10X Digital Sniper Threat" ) } },
		{ 156, { rarity::epic, _( "4X-8X Variable Sniper" ) } },
		{ 155, { rarity::rare, _( "6X Sniper" ) } },
		{ 167, { rarity::epic, _( "Extended Heavy Mag" ) } },
		{ 166, { rarity::rare, _( "Extended Heavy Mag" ) } },
		{ 165, { rarity::common, _( "Extended Heavy Mag" ) } },
		{ 184, { rarity::legendary, _( "Skullpiercer Rifling" ) } },
		{ 192, { rarity::legendary, _( "Treasure Pack" ) } },
		{ 188, { rarity::epic, _( "Quickdraw Holster" ) } },
		{ 190, { rarity::legendary, _( "Vault Key" ) } },
	};
	
	struct item_info {
		float distance{ };
		vec3_t pos{ };
		std::chrono::system_clock::time_point last_update;
		float fov{ };
		int item_id{ };
	};

	auto* const local_player = entity_t::get_local_player( );
	if ( !settings::visuals_item_esp || !local_player || !local_player->alive( ) )
		return;

	std::vector<item_info> item_list;
	for ( auto i = 0; i < interfaces::client_entity_list->get_highest_entity_index( ); i++ ) {
		auto* const items = entity_t::get_client_entity( i );
		if ( !items )
			continue;

		const auto* const identifier = items->identifier( );
		if ( !identifier || !*identifier )
			continue;

		if ( !strcmp( identifier, _( "prop_survival" ) ) )
			item_list.emplace_back( item_info{ sqrtf( powf( local_player->origin( ).x - items->origin( ).x, 2 ) + powf( local_player->origin( ).y - items->origin( ).y, 2 ) + powf( local_player->origin( ).z - items->origin( ).z, 2 ) ) * 0.0254f, items->origin( ), std::chrono::system_clock::now( ), utils::get_fov( local_player->viewangles( ), utils::calc_angle( entity_t::camera_position( ), items->origin( ) ) ), items->custom_script_int( ) } );
	}

	for ( auto& item_it : item_list ) {
		auto time = std::chrono::system_clock::now( );
		auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>( time - item_it.last_update );

		if ( milliseconds.count( ) > 500 || item_it.distance > settings::visuals_item_esp_maxdistance )
			continue;

		auto screen = vec3_t( );
		if ( utils::world_to_screen( item_it.pos, screen ) ) {
			auto alpha = scale( item_it.distance, 0.f, 300.f, 255.f, 0.f );
			alpha = scale( item_it.fov, 6.f, 30.f, 0.f, alpha );
			const auto box_alpha = scale( item_it.fov, 6.f, 30.f, 0.f, alpha );

			auto [rarity, name] = items[item_it.item_id];
			if ( name.empty( ) )
				name = std::to_string( item_it.item_id );

			static auto color_to_use = ImVec4( );
			if ( rarity == rarity::heirloom )
				color_to_use = ImVec4( 255, 0, 0, 255 );
			else if ( rarity == rarity::legendary )
				color_to_use = ImVec4( 255, 215, 0, 255 );
			else if ( rarity == rarity::epic )
				color_to_use = ImVec4( 255, 0, 255, 255 );
			else if ( rarity == rarity::rare )
				color_to_use = ImVec4( 0, 191, 255, 255 );
			else
				color_to_use = ImVec4( 240, 248, 255, 255 );

			const auto text_size = ImGui::CalcTextSize( name.c_str( ) );
			ImGui::GetOverlayDrawList( )->AddRectFilled( ImVec2( screen.x - text_size.x / 2 - 5, screen.y ), ImVec2( screen.x + text_size.x / 2 + 5, screen.y + text_size.y ), IM_COL32( 0, 0, 0, box_alpha ), 5 );
			render::text( name.c_str( ), ImVec2( screen.x - text_size.x / 2, screen.y ), 13.f, IM_COL32( color_to_use.x, color_to_use.y, color_to_use.z, alpha ), false, false );
		}
	}
}

void players_behind( ) {
	const auto rotate_triangle = []( std::array<vec3_t, 3>& points, const float rotation ) {
		const auto points_center = ( points.at( 0 ) + points.at( 1 ) + points.at( 2 ) ) / 3;
		for ( auto& point : points ) {
			point -= points_center;

			const auto temp_x = point.x;
			const auto temp_y = point.y;

			const auto theta = DEG2RAD( rotation );
			const auto c = cosf( theta );
			const auto s = sinf( theta );

			point.x = temp_x * c - temp_y * s;
			point.y = temp_x * s + temp_y * c;

			point += points_center;
		}
	};

	auto* const local_player = entity_t::get_local_player( );
	if ( !settings::visuals_offscreen || !local_player || !local_player->alive( ) || local_player->origin( ).z > 11000.0 || local_player->origin( ).z == -3727 )
		return;

	for ( auto i = 1; i < 100; i++ ) {
		auto* const entity = entity_t::get_client_entity( i );
		if ( !entity || !entity->alive( ) || entity->team_number( ) == local_player->team_number( ) || entity->knocked( ) != 0 )
			continue;

		const auto distance = sqrt( pow( local_player->origin( ).x - entity->origin( ).x, 2 ) + pow( local_player->origin( ).y - entity->origin( ).y, 2 ) + pow( local_player->origin( ).z - entity->origin( ).z, 2 ) ) * 0.0254f;
		if ( distance >= 200 || distance <= 10 )
			continue;

		auto screen_point = vec3_t( );
		utils::world_to_screen( entity->origin( ), screen_point );
		if ( screen_point.x < 0 || screen_point.y < 0 || screen_point.x > ImGui::GetIO( ).DisplaySize.x || screen_point.y > ImGui::GetIO( ).DisplaySize.y ) {
			auto angle = vec3_t( );
			utils::vector_angles( vec3_t( ImGui::GetIO( ).DisplaySize.x / 2 - screen_point.x, ImGui::GetIO( ).DisplaySize.y / 2 - screen_point.y, 0.f ), angle );

			const auto angle_yaw_rad = DEG2RAD( local_player->viewangles( ).y - utils::calc_angle( local_player->origin( ), entity->origin( ) ).y - 90 );

			const auto radius = settings::visuals_offscreen_radius;
			const auto size = settings::visuals_offscreen_size;

			const auto new_point_x = ImGui::GetIO( ).DisplaySize.x / 2 + radius * cosf( angle_yaw_rad );
			const auto new_point_y = ImGui::GetIO( ).DisplaySize.y / 2 + radius * sinf( angle_yaw_rad );

			std::array<vec3_t, 3> points{
				vec3_t( new_point_x - size, new_point_y - size, 0.f ),
				vec3_t( new_point_x + size, new_point_y, 0.f ),
				vec3_t( new_point_x - size, new_point_y + size, 0.f )
			};

			rotate_triangle( points, local_player->viewangles( ).y - utils::calc_angle( local_player->origin( ), entity->origin( ) ).y - 90 );
			ImGui::GetOverlayDrawList( )->AddTriangleFilled( ImVec2( points.at( 0 ).x, points.at( 0 ).y ), ImVec2( points.at( 1 ).x, points.at( 1 ).y ), ImVec2( points.at( 2 ).x, points.at( 2 ).y ), ImGui::GetColorU32( ImVec4( settings::visuals_offscreen_color[0], settings::visuals_offscreen_color[1], settings::visuals_offscreen_color[2], settings::visuals_offscreen_color[3] ) ) );
		}
	}
}

void spectator_list( ) {
	const auto in_bounds = [ ]( const vec3_t& vec, const float x, const float y, const float x2, const float y2 ) {
		return vec.x > x && vec.y > y && vec.x < x2 && vec.y < y2;
	};

	auto* local_player = entity_t::get_local_player( );
	if ( !settings::misc_spectator_list || !local_player || !local_player->alive( ) )
		return;

	std::vector<std::string> spectators;
	for ( auto i = 1; i < 100; i++ ) {
		for ( auto i = 1; i < 100; i++ ) {
			auto* entity = entity_t::get_client_entity( i );
			if ( !entity || entity->alive( ) )
				continue;

			const auto* const observer = entity_t::get_client_entity( entity->observer_target( ) );
			if ( observer != local_player )
				continue;

			spectators.emplace_back( entity->get_name( ) );
		}
	}

	if ( spectators.empty( ) )
		return;

	static auto* pos = settings::misc_spectator_list_pos;
	if ( utils::global::menu_open ) {
		auto point = POINT( );
		if ( !LI_FN( GetCursorPos ).cached( )( &point ) )
			return;

		if ( in_bounds( vec3_t( point.x, point.y, 0 ), pos[0], pos[1], pos[0] + 200, pos[1] + 30 ) && LI_FN( GetAsyncKeyState ).cached( )( 1 ) ) {
			pos[0] = point.x - 100;
			pos[1] = point.y - 10;
		}
	}

	std::ranges::sort( spectators );
	spectators.erase( std::ranges::unique( spectators ).begin(), spectators.end( ) );

	const auto spectators_size = static_cast<int>( spectators.size( ) );

	render::rect( ImVec2( pos[0] - 1, pos[1] - 1 ), ImVec2( 202, 61 + 15 * ( spectators_size - 1 ) ), IM_COL32( 2, 2, 2, 100 ) );
	render::filled_rect( ImVec2( pos[0], pos[1] ), ImVec2( 200, 60 + 15 * ( spectators_size - 1 ) ), IM_COL32( 55, 55, 55, 200 ) );
	render::rect( ImVec2( pos[0] + 5, pos[1] + 5 ), ImVec2( 190, 50 + 15 * ( spectators_size - 1 ) ), IM_COL32( 2, 2, 2, 150 ) );
	render::filled_rect( ImVec2( pos[0] + 5, pos[1] + 5 ), ImVec2( 190, 50 + 15 * ( spectators_size - 1 ) ), IM_COL32( 0, 0, 0, 200 ) );
	render::filled_rect( ImVec2( pos[0] + 9, pos[1] + 25 ), ImVec2( 181, 3 ), ImGui::GetColorU32( ImVec4( settings::misc_spectator_list_color[0], settings::misc_spectator_list_color[1], settings::misc_spectator_list_color[2], settings::misc_spectator_list_color[3] ) ) );
	render::text( std::string( _( "spectators (" ) ).append( std::to_string( spectators_size ) ).append( _( ")" ) ).c_str( ), ImVec2( pos[0] + 100, pos[1] + 10 ), 14.f, IM_COL32( 255, 255, 255, 255 ) );

	for ( auto i = 0; i < spectators_size; i++ ) {
		render::text( spectators.at( i ).c_str( ), ImVec2( pos[0] + 100, pos[1] + 35 + 15 * i ), 14.f, IM_COL32( 255, 255, 255, 255 ) );
	}
}

void visuals::init( ) {
	glow( );
	glow_item( );
	item_esp( );
	players_behind( );
	spectator_list( );
}
