#include "weapon.hh"
#include <xorstr.hh>

bool weapon_t::fire_ready() {
	static uint8_t* is_fire_ready_fn = nullptr;
	if ( !is_fire_ready_fn )
		is_fire_ready_fn = utils::find_pattern( _( "48 8B 05 ? ? ? ? F3 0F 10 91 88 16 00 00" ) );

	if ( !is_fire_ready_fn )
		return false;
	
	return reinterpret_cast<bool( __fastcall* )( void* )>( is_fire_ready_fn )( this );
}

void weapon_t::set_charms_model( ) {
	static uint8_t* set_charms_model_fn = nullptr;
	if ( !set_charms_model_fn )
		set_charms_model_fn = utils::find_pattern( _( "48 8B C4 56 57 41 54 48 81 EC ? ? ? ?" ) );

	if ( !set_charms_model_fn )
		return;

	reinterpret_cast<void( __fastcall* )( void*, const char*, const char* )>( set_charms_model_fn )( this, _( "mdl/props/charm/charm_halloween_2020.rmdl" ), _( "CHARM" ) );
}

std::string weapon_t::get_weapon_name( ) {
	switch ( this->weapon_name_index( ) ) {
	case P2020:
		return _( "p2020" );
	case HAVOC:
		return _( "havoc" );
	case LSTAR:
		return _( "l-star" );
	case DEVOTION:
		return _( "devotion" );
	case MASTIFF:
		return _( "mastiff" );
	case KRABER:
		return _( "kraber" );
	case SENTINEL:
		return _( "sentinel" );
	case CHARGE_RIFLE:
		return _( "charge-rifle" );
	case LONGBOW:
		return _( "long-bow" );
	case TRIPLE_TAKE:
		return _( "triple-take" );
	case WINGMAN:
		return _( "wingman" );
	case SPITFIRE:
		return _( "spitfire" );
	case PROWLER:
		return _( "prowler" );
	case HEMLOK:
		return _( "hemlok" );
	case FLATLINE:
		return _( "flatline" );
	case RE45:
		return _( "re-45" );
	case R301:
		return _( "r-301" );
	case R99:
		return _( "r-99" );
	case ALTERNATOR:
		return _( "alternator" );
	case G7_SCOUT:
		return _( "g7-scout" );
	case EVA8_AUTO:
		return _( "eva-8" );
	case PEACEKEEPER:
		return _( "peacekeeper" );
	case VOLT:
		return _( "volt" );
	case MOZAMBIQUE:
		return _( "mozambique" );

	default:
		return _( "" );
	}
}
