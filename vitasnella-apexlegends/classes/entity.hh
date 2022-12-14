#pragma once
#include "renderable.hh"
#include "studiohdr.hh"
#include "weapon.hh"
#include "../utilities/datamap_manager.hh"
#include "../utilities/netvar_manager.hh"
#include "../utilities/utils.hh"
#include "../utilities/vec3.hh"

struct entity_t {
	struct {
		OFFSET( bool, enable( ), 0x3E0 )
		OFFSET( int, enable2( ), 0x3C8 ) // Script_Highlight_GetCurrentContext
		OFFSET( float, distance( ), 0x3B4 ) // Script_Highlight_SetFarFadeDist
		OFFSET( vec3_t, colors( ), 0x1D0 )
		OFFSET( float, time( ), 0x38C ) // Script_Highlight_HideOutline
		OFFSET( uint32_t, style( ), 0x2C0 ) // Script_Highlight_GetInsideFunction
	} glow;

	NETVAR( int, health, "DT_Player->m_iHealth" )
	NETVAR( int, flags, "DT_Player->m_fFlags" )
	NETVAR( uintptr_t, weapon, "DT_BaseCombatCharacter->m_latestPrimaryWeapons->m_latestPrimaryWeapons" )
	NETVAR( uintptr_t, weapon2, "DT_BaseCombatCharacter->m_latestNonOffhandWeapons->m_latestNonOffhandWeapons" )
	NETVAR( vec3_t, velocity, "DT_Projectile->m_vecVelocity" )
	NETVAR( int, team_number, "DT_BaseEntity->m_iTeamNum" )
	NETVAR( int, knocked, "DT_Player->m_bleedoutState" )
	NETVAR( uint16_t, observer_target, "DT_Player->m_hObserverTarget" )
	NETVAR( char*, identifier, "DT_BaseEntity->m_iSignifierName" )
	NETVAR( int, custom_script_int, "DT_PropSurvival->m_customScriptInt" )
	NETVAR( int, usable_type, "DT_PropSurvival->m_usableType" )
	NETVAR( float, shield_health, "DT_BaseEntity->m_shieldHealth" )
	NETVAR( float, shield_max_health, "DT_BaseEntity->m_shieldHealthMax" )
	NETVAR( bool, zooming, "DT_Player->m_bZooming" )
	OFFSET( vec3_t, aimpunch( ), utils::aimpunch_offset( ) ) 
	OFFSET( vec3_t, viewangles( ), utils::viewangles_offset( ) ) 
	OFFSET( vec3_t, dynamic_angles( ), utils::viewangles_offset( ) - 0x10 )
	OFFSET( vec3_t, origin( ), 0x14c )

	template <class T>
	T read( const uintptr_t offset ) {
		return *reinterpret_cast<T*>( this + offset );
	}

	template <class T>
	void write( const uintptr_t offset, T val ) {
		*reinterpret_cast<T*>( this + offset ) = val;
	}

	static entity_t* get_local_player( );
	static entity_t* get_client_entity( int );
	weapon_t* get_active_weapon( );
	weapon_t* get_active_offweapon( );
	vec3_t get_bone_position( int );
	bool is_visible( const vec3_t&, const vec3_t& );
	const char* get_name( );
	bool alive( );
	datamap_t* get_pred_desc_map( );
	static vec3_t camera_position( );
	void* get_viewmodel( );
	studiohdr_t* get_studiohdr( );

	renderable_t* renderable( ) {
		return reinterpret_cast<renderable_t*>( reinterpret_cast<uintptr_t>( this ) + 0x10 );
	}
};
