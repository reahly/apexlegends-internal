#pragma once
#include <string>
#include <unordered_map>
#include "../utilities/netvar_manager.hh"
#include "../utilities/utils.hh"
#include "weapon_info.hh"

enum item_ids {
	R301 = 0,
	SENTINEL = 1,
	MELEE_SURVIVAL = 20,
	ALTERNATOR = 64,
	RE45,
	CHARGE_RIFLE,
	DEVOTION,
	LONGBOW,
	HAVOC,
	EVA8_AUTO,
	FLATLINE,
	G7_SCOUT,
	HEMLOK,
	KRABER,
	LSTAR,
	MASTIFF,
	MOZAMBIQUE,
	PROWLER,
	PEACEKEEPER,
	R99,
	P2020,
	SPITFIRE,
	TRIPLE_TAKE,
	WINGMAN,
	VOLT,
};

enum class rarity {
	common,
	rare,
	epic,
	legendary,
	heirloom
};

struct weapon_t {
	OFFSET( float, bullet_speed( ), 0x1e50 ) // xref Speed(%f) is greater than sv_maxvelocity(%f)
	OFFSET( float, bullet_gravity( ), 0x1e50  + 0x8 ) // bullet_speed + sizeof vec3
	OFFSET( void*, get_charms_model( ), 0x66A8 )
	NETVAR( int, weapon_name_index, "DT_WeaponX->m_weaponNameIndex" )
	NETVAR( float, zoom_fov, "DT_WeaponPlayerData->m_targetZoomFOV" )
	OFFSET( weapon_info_t*, weapon_info( ), 0x19B0 )

	template<class T>
	T read( const uintptr_t offset ) {
		return *reinterpret_cast<T*>( this + offset );
	}

	template<class T>
	void write( const uintptr_t offset, T val ) {
		*reinterpret_cast<T*>( this + offset ) = val;
	}
	
	std::string get_weapon_name( );
	bool fire_ready( );
	void set_charms_model( );
};