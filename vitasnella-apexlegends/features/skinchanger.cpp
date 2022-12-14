#include "skinchanger.hh"

#include <ranges>

#include "../settings.hh"
#include "../classes/entity.hh"
#include "../interfaces/interfaces.hh"

std::vector<std::string> skinchanger::skins_combo( ) {
	auto* local_player = entity_t::get_local_player( );
	if ( !local_player || !local_player->alive( ) )
		return {};

	auto* const weapon = local_player->get_active_weapon( );
	if ( !weapon )
		return {};

	std::unordered_map<int, std::vector<std::string>> skins {
		{ P2020, { _( "None" ), _( "common/rare mask" ), _( "blue" ), _( "red" ), _( "green" ), _( "aqua" ), _( "purple" ), _( "charm_preview_black" ), _( "s03e01_epic_01" ), _( "s06_rarep_01" ) } },
		{ MOZAMBIQUE, { _( "None" ), _( "ornate" ), _( "cyberpunk" ) , _( "mozambique_legendary_02_rc_01" ), _( "shop_legendary_05" ) } },
		{ EVA8_AUTO, { _( "None" ), _( "common/rare mask" ), _( "blue" ), _( "red" ), _( "green" ), _( "aqua" ), _( "purple" ), _( "season02_event01_epic_01" ), _( "s03e01_epic_01" ) } },
		{ MASTIFF, { _( "None" ), _( "common/rare mask" ), _( "blue" ), _( "red" ), _( "green" ), _( "aqua" ), _( "purple" ), _( "s06_rarep_01" ), _( "shotgun_mastiff_rarep_ascension" ) } },
		{ KRABER, { _( "None" ), _( "common/rare mask" ), _( "blue" ), _( "red" ), _( "green" ), _( "aqua" ), _( "purple" ), _( "twitch02_rare_01" ) } },
		{ PROWLER, { _( "None" ), _( "common/rare mask" ), _( "blue" ), _( "red" ), _( "green" ), _( "aqua" ), _( "purple" ), _( "wild frontier" ), _( "season02_event01_epic_01" ), _( "season02_event02_rare_01" ), _( "s04e02_epic_01" ),  } },
		{ PEACEKEEPER, { _( "None" ), _( "Pathefinder" ), _( "Pathefinder retheme" ), _( "shop_legendary_01" ), _( "legendary_03_rc_01" ), _( "The Demolisher - Recolor 02" ) } },
		{ LSTAR, { _( "None" ), _( "samurai" ), _( "samurai 2" ), _( "lstar_legendary_01_rc_01" ), _( "shop_legendary_04" ) } },
		{ HAVOC, { _( "None" ), _( "common/rare mask" ), _( "blue" ), _( "red" ), _( "green" ), _( "aqua" ), _( "purple" ), _( "season02_event01_epic_01" ), _( "s03e03_epic_01" ), _( "s03e03_epic_02" ) } },
		{ DEVOTION, { _( "None" ), _( "common/rare mask" ), _( "blue" ), _( "red" ), _( "green" ), _( "aqua" ), _( "purple" ), _( "season02_event01_epic_01" ), _( "s03e03_epic_01" ), _( "s03e03_epic_02" ) } },
		{ VOLT, { _( "None" ), _( "common/rare mask" ), _( "blue" ), _( "red" ), _( "green" ), _( "aqua" ), _( "purple" ), _( "rarep_01" ) } },
		{ SENTINEL, { _( "None" ), _( "common/rare mask" ), _( "blue" ), _( "red" ), _( "green" ), _( "aqua" ), _( "purple" ), _( "s06e02_epic_01" ) } },
		{ CHARGE_RIFLE, { _( "None" ), _( "common/rare mask" ), _( "blue" ), _( "red" ), _( "green" ), _( "aqua" ), _( "purple" ), _( "s04bp_epic_01" ) } },
		{ TRIPLE_TAKE, { _( "None" ), _( "ghillie (woodland)" ), _( "ghillie (snow)" ), _( "ghillie (blue)" ), _( "ghillie (brown\\yellow)" ), _( "s5_trshunter" ) } },
		{ WINGMAN, { _( "None" ), _( "common/rare mask" ), _( "blue" ), _( "red" ), _( "green" ), _( "aqua" ), _( "purple" ), _( "s04bp_epic_01" ), _( "s5_trshunter_rarep" ), _( "s05e01_epic_01" ) } },
		{ SPITFIRE, { _( "None" ), _( "common/rare mask" ), _( "blue" ), _( "red" ), _( "green" ), _( "aqua" ), _( "purple" ), _( "s03e01_epic_01" ), _( "s04e01_epic_01" ), _( "s05bp_epic_01" ), _( "s6_epicplus_01" ), _( "lmg_spitfire_epicp_ascension" ) } },
		{ FLATLINE, { _( "None" ), _( "base" ), _( "recolor 01" ), _( "shop_legendary_01" ), _( "retail01_legendary_01" ), _( "shop_legendary_02_rc" ), _( "The Spine Chiller - Recolor 02" ), _( "s04bp_epic_01" ), _( "s5_trshunter_rarep" ), _( "s05e01_epic_01" ) } },
		{ RE45, { _( "None" ), _( "common/rare mask" ), _( "blue" ), _( "red" ), _( "green" ), _( "aqua" ), _( "purple" ), _( "purple/blue fade" ), _( "season02_event02_rare_01" ), _( "s04e01_epic_01" ), _( "s05e01_rare_01" ), _( "s06bp_epic_01" ), _( "s06_epicp_01" ) } },
		{ R301, { _( "None" ), _( "common/rare mask" ), _( "blue" ), _( "red" ), _( "green" ), _( "aqua" ), _( "purple" ), _( "s03e01_rare_01" ), _( "s03e03_rare_01" ), _( "s5_trshunter_rarep" ), _( "assault_r301_epicp_ascension" ), _( "lmg_spitfire_epicp_ascension" ) } },
		{ R99, { _( "None" ), _( "season02_event01_legendary_01" ) } },
		{ G7_SCOUT, { _( "None" ), _( "common/rare mask" ), _( "blue" ), _( "red" ), _( "green" ), _( "aqua" ), _( "purple" ), _( "epic 06" ), _( "epic 07" ), _( "beasthunter_rare_01" ), _( "season02_event02_epic_01" ), _( "season02_event02_epic_02" ), _( "s03e03_rare_01" ), _( "s04e01_epic_01" ), _( "s06e02_epic_01" ), _( "assault_g2a6_rarep_ascension" ) } },
		{ HEMLOK, { _( "None" ) } }
	};
	
	return skins[weapon->weapon_name_index( )];
}

int skinchanger::weapon_id( ) {
	auto* local_player = entity_t::get_local_player( );
	if ( !local_player || !local_player->alive( ) )
		return 0;

	auto* const weapon = local_player->get_active_weapon( );
	if ( !weapon )
		return 0;

	return weapon->weapon_name_index( );
}

std::vector<std::string> skinchanger::charm_list( ) {
	std::unordered_map<int, std::string> charms {
		{ 755, _( "S05 Ranked Platinum" ) },
		{ 756, _( "S05 Ranked Diamond" ) },
		{ 757, _( "S05 Ranked Master" ) },
		{ 753, _( "Rampart Wrench" ) },
		{ 754, _( "S05 Ranked Gold" ) },
		{ 751, _( "Hover Craft" ) },
		{ 761, _( "Crow Bar" ) },
		{ 762, _( "Rampart Kicks" ) },
		{ 763, _( "Hot Rod Engine" ) },
		{ 759, _( "Golden Nessy" ) },
		{ 733, _( "C4" ) },
		{ 700, _( "Spider" ) },
		{ 707, _( "Molotov Cocktail" ) },
		{ 623, _( "S01 Predator" ) },
		{ 681, _( "Bobblehead Wraith" ) },
		{ 806, _( "Bobblehead Pathfinder" ) },
		{ 684, _( "Bangalore Missile" ) },
		{ 768, _( "Hallowen" ) },
		{ 702, _( "One to One" ) },
	};
	
	static std::vector<std::string> charms_names;
	for ( const auto& a2 : charms | std::views::values ) 
		charms_names.emplace_back( a2 );

	std::ranges::sort( charms_names );
	charms_names.erase( std::ranges::unique( charms_names ).begin(), charms_names.end( ) );
	
	return charms_names;
}

void skin_changer( ) {
	auto* local_player = entity_t::get_local_player( );
	if ( !settings::skinchanger_enabled || !local_player || !local_player->alive( ) )
		return;

	auto* const weapon = local_player->get_active_weapon( );
	if ( !weapon )
		return;

	static uint8_t* addr = nullptr;
	if ( !addr )
		addr = utils::find_pattern( _( "89 91 58 17 00 00 ? ? ? ? ? ?" ) );

	if ( !addr )
		return;

	reinterpret_cast<void( __fastcall* )( void*, int )>( addr )( weapon, settings::skinchanger_id[weapon->weapon_name_index( )] );
}

void charm_changer( ) {
	auto* local_player = entity_t::get_local_player( );
	if ( !settings::charmchanger_enabled || !local_player || !local_player->alive( ) )
		return;

	auto* const weapon = local_player->get_active_weapon( );
	if ( !weapon )
		return;

	if ( const auto* const model_loaded = weapon->get_charms_model( ); model_loaded == nullptr )
		weapon->set_charms_model( );

	const auto extract_id = []( const int val ) {
		switch ( val ) {
		case 0:
			return 684;
		case 1:
			return 806;
		case 2:
			return 681;
		case 3:
			return 733;
		case 4:
			return 761;
		case 5:
			return 759;
		case 6:
			return 768;
		case 7:
			return 763;
		case 8:
			return 751;
		case 9:
			return 707;
		case 10:
			return 702;
		case 11:
			return 762;
		case 12:
			return 753;
		case 13:
			return 623;
		case 14:
			return 756;
		case 15:
			return 754;
		case 16:
			return 757;
		case 17:
			return 755;
		case 18:
			return 700;
			
		default: return 684;
		}
	};

	*reinterpret_cast<int*>( weapon + 0x1744 ) = 2037;
}

void skinchanger::init( ) {
	skin_changer( );
	//charm_changer( );
}
