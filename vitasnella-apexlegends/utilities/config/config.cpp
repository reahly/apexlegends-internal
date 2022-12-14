#include "config.hh"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <xorstr.hh>
#include "../color.hh"
#include "../../settings.hh"

nlohmann::json json;
c_config config;

void assign_item( item& item ) {
	if ( json[item.name.c_str( )].empty( ) )
		return;

	if ( item.type == _( "float" ) )
		*static_cast<float*>( item.value ) = json[item.name.c_str( )].get<float>( );
	if ( item.type == _( "int" ) )
		*static_cast<int*>( item.value ) = json[item.name.c_str( )].get<int>( );
	if ( item.type == _( "bool" ) )
		*static_cast<bool*>( item.value ) = json[item.name.c_str( )].get<bool>( );
	if ( item.type == _( "float [4]" ) )
		for ( auto i = 0; i < 4; i++ )
			static_cast<float*>( item.value )[i] = json[item.name.c_str( )][std::to_string( i ).c_str( )].get<float>( );
	if ( item.type == _( "int [80]" ) )
		for ( auto i = 0; i < 80; i++ )
			static_cast<int*>( item.value )[i] = json[item.name.c_str( )][std::to_string( i ).c_str( )].get<int>( );
	if ( item.type == _( "char [100]" ) )
		for ( auto i = 0; i < 100; i++ )
			static_cast<char*>( item.value )[i] = json[item.name.c_str( )][std::to_string( i ).c_str( )].get<char>( );
	if ( item.type == _( "struct color" ) ) {
		static_cast<color*>( item.value )->r = json[item.name.c_str( )][std::to_string( 0 )].get<float>( );
		static_cast<color*>( item.value )->g = json[item.name.c_str( )][std::to_string( 1 )].get<float>( );
		static_cast<color*>( item.value )->b = json[item.name.c_str( )][std::to_string( 2 )].get<float>( );
	}
	if ( item.type == _( "bool [2]" ) )
		for ( auto i = 0; i < 2; i++ )
			static_cast<bool*>( item.value )[i] = json[item.name.c_str( )][std::to_string( i ).c_str( )].get<bool>( );

}

void save_item( item& item ) {
	if ( item.type == _( "float" ) )
		json[item.name.c_str( )] = *static_cast<float*>( item.value );
	if ( item.type == _( "int" ) )
		json[item.name.c_str( )] = *static_cast<int*>( item.value );
	if ( item.type == _( "bool" ) )
		json[item.name.c_str( )] = *static_cast<bool*>( item.value );
	if ( item.type == _( "float [4]" ) )
		for ( auto i = 0; i < 4; i++ )
			json[item.name.c_str( )][std::to_string( i ).c_str( )] = static_cast<float*>( item.value )[i];
	if ( item.type == _( "int [80]" ) )
		for ( auto i = 0; i < 80; i++ )
			json[item.name.c_str( )][std::to_string( i ).c_str( )] = static_cast<int*>( item.value )[i];
	if ( item.type == _( "struct color" ) ) {
		auto r = static_cast<color*>( item.value )->r;
		auto g = static_cast<color*>( item.value )->g;
		auto b = static_cast<color*>( item.value )->b;

		json[item.name.c_str( )][std::to_string( 0 )] = r;
		json[item.name.c_str( )][std::to_string( 1 )] = g;
		json[item.name.c_str( )][std::to_string( 2 )] = b;
	}
	if ( item.type == _( "char [100]" ) ) {
		for ( auto i = 0; i < 100; i++ )
			json[item.name.c_str( )][std::to_string( i ).c_str( )] = static_cast<char*>( item.value )[i];
	}
	if ( item.type == _( "bool [2]" ) )
		for ( auto i = 0; i < 2; i++ )
			json[item.name.c_str( )][std::to_string( i ).c_str( )] = static_cast<bool*>( item.value )[i];
}

#pragma warning(disable : 4996)
bool c_config::init( ) {
	if ( !std::filesystem::exists( _( "videos" ) ) ) 
		if ( !std::filesystem::create_directory( _( "videos" ) ) ) 
			return false;

	item( settings::aimbot_enabled, _( "aimbot.enable" ), m_items );
	item( settings::aimbot_bind, _( "aimbot.bind" ), m_items );
	item( settings::aimbot_silent, _( "aimbot.silent" ), m_items );
	item( settings::aimbot_fov, _( "aimbot.fov" ), m_items );
	item( settings::aimbot_visible, _( "aimbot.visible" ), m_items );
	item( settings::aimbot_autofire, _( "aimbot.autofire" ), m_items );
	item( settings::aimbot_downed, _( "aimbot.downed" ), m_items );
	item( settings::aimbot_smooth, _( "aimbot.smooth" ), m_items );

	item( settings::antiaim_enabled, _( "antiaim.enable" ), m_items );
	item( settings::antiaim_pitch_type, _( "antiaim.pitch_type" ), m_items );
	item( settings::antiaim_yaw_type, _( "antiaim.yaw_type" ), m_items );

	item( settings::visuals_box, _( "visuals.box" ), m_items );
	item( settings::visuals_skeleton, _( "visuals.skeleton" ), m_items );
	item( settings::visuals_name, _( "visuals.name" ), m_items );
	item( settings::visuals_weapon, _( "visuals.weapon" ), m_items );
	item( settings::visuals_healthbar, _( "visuals.healthbar" ), m_items );
	item( settings::visuals_distance, _( "visuals.distance" ), m_items );
	item( settings::visuals_glow, _( "visuals.glow" ), m_items );
	item( settings::visuals_glow_color, _( "visuals.glow_color" ), m_items );
	item( settings::visuals_glow_healthbased, _( "visuals.glow_healthbased" ), m_items );
	item( settings::esp_maxdistance, _( "visuals.maxdistance" ), m_items );
	item( settings::visuals_name_color, _( "visuals.namecolor" ), m_items );
	item( settings::visuals_box_color, _( "visuals.boxcolor" ), m_items );
	item( settings::visuals_skeleton_color, _( "visuals.skeleton_color" ), m_items );
	item( settings::visuals_weapon_color, _( "visuals.weaponcolor" ), m_items );
	item( settings::visuals_loot_glow, _( "visuals.loot_glow" ), m_items );
	item( settings::visuals_item_esp, _( "visuals.item_esp" ), m_items );
	item( settings::visuals_item_esp_maxdistance, _( "visuals.item_esp_maxdistance" ), m_items );
	item( settings::visuals_shieldbar, _( "visuals.visuals_shieldbar" ), m_items );
	item( settings::visuals_shieldbar_color, _( "visuals.shieldbar_color" ), m_items );
	item( settings::visuals_offscreen, _( "visuals.offscreen" ), m_items );
	item( settings::visuals_offscreen_radius, _( "visuals.offscreen_radius" ), m_items );
	item( settings::visuals_offscreen_size, _( "visuals.offscreen_size" ), m_items );
	item( settings::visuals_offscreen_color, _( "visuals.offscreen_color" ), m_items );

	item( settings::misc_hide_names, _( "misc.hide_names" ), m_items );
	item( settings::misc_norecoil, _( "misc.norecoil" ), m_items );
	item( settings::misc_remove_fog, _( "misc.remove_fog" ), m_items );
	item( settings::misc_darkmode, _( "misc.darkmode" ), m_items );
	item( settings::misc_showfov, _( "misc.showfov" ), m_items );
	item( settings::misc_bhop, _( "misc.bhop" ), m_items );
	item( settings::misc_autostrafe, _( "misc.autostrafe" ), m_items );
	item( settings::misc_fakelag, _( "misc.fakelag" ), m_items );
	item( settings::misc_fakelagticks, _( "misc.fakelagticks" ), m_items );
	item( settings::misc_fakelagmode, _( "misc.fakelagmode" ), m_items );
	item( settings::misc_spectator_list, _( "misc.spectator_list" ), m_items );
	item( settings::misc_spectator_list_color, _( "misc.spectator_list_color" ), m_items );
	item( settings::misc_spectator_list_pos, _( "misc.spectator_list_pos" ), m_items );
	item( settings::misc_thirdperson, _( "misc.thirdperson" ), m_items );
	item( settings::misc_thirdperson_key, _( "misc.thirdperson_key" ), m_items );
	item( settings::misc_speedhack, _( "misc.speedhack" ), m_items );
	item( settings::misc_speedhack_key, _( "misc.speedhack_key" ), m_items );
	item( settings::misc_customfov, _( "misc.customfov" ), m_items );
	item( settings::misc_customfov_value, _( "misc.customfov_value" ), m_items );
	item( settings::misc_chatspam, _( "misc.chatspam" ), m_items );
	item( settings::misc_chatspam_text, _( "misc.chatspam_text" ), m_items );
	item( settings::misc_chatspam_delay, _( "misc.chatspam_delay" ), m_items );
	item( settings::misc_spoof_game_type, _( "misc.spoof_game_type" ), m_items );
	item( settings::misc_spoof_game_type_text, _( "misc.spoof_game_type_text" ), m_items );

	item( settings::skinchanger_enabled, _( "skinchanger.enabled" ), m_items );
	item( settings::skinchanger_id, _( "skinchanger.id" ), m_items );

	item( settings::charmchanger_enabled, _( "charmchanger.enabled" ), m_items );
	item( settings::charmchanger_id, _( "charmchanger.id" ), m_items );
	
	return true;
}

bool c_config::save( ) {
	const std::string m_directory = _( "videos" );

	auto output_file = std::ofstream( m_directory + "/" + _( "vid.mp4" ) );

	if ( !output_file.good( ) )
		return false;

	for ( auto& item : m_items )
		save_item( item );

	output_file << std::setw( 4 ) << json << std::endl;
	output_file.close( );

	return true;
}

bool c_config::load( const std::string& content ) {
	if ( !nlohmann::json::accept( content ) )
		return false;
	
	json = nlohmann::json::parse( content );
	for ( auto& item : m_items )
		assign_item( item );

	return true;
}
