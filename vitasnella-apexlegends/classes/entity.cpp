#include "entity.hh"
#include "../interfaces/interfaces.hh"

entity_t* entity_t::get_local_player( ) {
	static auto local_player = uintptr_t( );
	if ( !local_player )
		local_player = RESOLVE_RVA( utils::find_pattern( _( "48 89 3D ? ? ? ? 44 88 3D ? ? ? ?" ) ) );

	if ( !local_player )
		return nullptr;

	return *reinterpret_cast<entity_t**>( local_player );
}

entity_t* entity_t::get_client_entity( const int index ) {
	static auto entity_list = uintptr_t( );
	if ( !entity_list )
		entity_list = RESOLVE_RVA( utils::find_pattern( _( "4C 8D 25 ? ? ? ? 45 33 FF 48 8B F1" ) ) );

	if ( !entity_list )
		return nullptr;

	return *reinterpret_cast<entity_t**>( entity_list + ( static_cast<uintptr_t>( index ) << 5 ) );
}

weapon_t* entity_t::get_active_weapon( ) {
	const auto weaponid = this->weapon( ) & 0xFFFF;
	if ( !weaponid )
		return nullptr;

	return reinterpret_cast<weapon_t*>( get_client_entity( weaponid ) );
}

weapon_t* entity_t::get_active_offweapon( ) {
	const auto weaponid = this->weapon2( ) & 0xFFFF;
	if ( !weaponid )
		return nullptr;

	return reinterpret_cast<weapon_t*>( get_client_entity( weaponid ) );
}

vec3_t entity_t::get_bone_position( const int bone ) {
	utils::matrix_t bone_matrix[256];
	if ( !this->renderable( )->setup_bones( bone_matrix, 256, 0x0100, 0.f ) )
		return vec3_t( );

	return this->origin( ) + vec3_t( bone_matrix[bone][0][3], bone_matrix[bone][1][3], bone_matrix[bone][2][3] );
}

bool entity_t::is_visible( const vec3_t& start, const vec3_t& end ) {
	ray_t ray;
	RtlZeroMemory( &ray, sizeof( ray_t ) );
	ray.init( start, end );

	trace_t trace;
	RtlZeroMemory( &trace, sizeof trace );
	interfaces::engine_trace_client->trace_ray( ray, 0x640400B, &trace );

	return trace.ent == this || trace.fraction > 0.97f;
}

const char* entity_t::get_name( ) {
	static uint8_t* name = nullptr;
	if ( !name )
		name = utils::find_pattern( _( "40 53 48 83 EC 20 48 8B D9 E8 ? ? ? ? 48 63 43 38" ) );

	if ( !name )
		return _( "unknown" );

	return reinterpret_cast<char*( __fastcall*)( uintptr_t )>( name )( reinterpret_cast<uintptr_t>( this ) );
}

bool entity_t::alive( ) {
	if ( !this->health( ) )
		return false;
	
	static uint8_t* alive_fn = nullptr;
	if ( !alive_fn )
		alive_fn = utils::find_pattern( _( "F6 41 58 01 74 03" ) );

	if ( !alive_fn )
		return false;
	
	return reinterpret_cast<bool( __fastcall* )( void* )>( alive_fn )( this );
}

datamap_t* entity_t::get_pred_desc_map( ) {
	return utils::get_vfunc<14, datamap_t*>( this );
}

vec3_t entity_t::camera_position( ) {
	static uint8_t* camera_position_fn = nullptr;
	if ( !camera_position_fn )
		camera_position_fn = utils::find_pattern( _( "8B 05 ? ? ? ? F2 0F 10 05 ? ? ? ? F2 0F 11 01 89 41 08 48 8B C1 C3" ) );

	if ( !camera_position_fn )
		return vec3_t( );

	auto ret = vec3_t( );
	reinterpret_cast<vec3_t*( __fastcall*)( vec3_t* )>( camera_position_fn )( &ret );
	return ret;
}

void* entity_t::get_viewmodel( ) {
	static uint8_t* get_viewmodel_fn = nullptr;
	if ( !get_viewmodel_fn )
		get_viewmodel_fn = utils::find_pattern( _( "8B 81 ? ? ? ? 83 F8 FF 74 1C 0F B7 C8 48 8D 15 ? ? ? ? 48 C1 E1 05 C1 E8 10 39 44 11 08 75 05 48 8B 04 11 C3 33 C0 C3 CC CC CC CC CC CC CC CC CC CC CC CC" ) );

	if ( !get_viewmodel_fn )
		return nullptr;
	
	return reinterpret_cast<void*( __fastcall*)( void* )>( get_viewmodel_fn )( this );
}

studiohdr_t* entity_t::get_studiohdr( ) {
	return static_cast<studiohdr_t*>( *reinterpret_cast<void**>( *reinterpret_cast<uintptr_t*>( reinterpret_cast<uintptr_t>( this ) + 0x1138 ) + 0x8 ) );
}
