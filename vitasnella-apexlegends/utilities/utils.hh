#pragma once
#include <Windows.h>
#include <cstdint>
#include <string_view>
#include "vec3.hh"

#define OFFSET( type, func, offset ) type& func { return *reinterpret_cast<type*>( reinterpret_cast<uintptr_t>( this ) + offset ); }  // NOLINT
#define RESOLVE_RVA( Instr ) (((DWORD64)(Instr)) + (7) + *(LONG*)(((DWORD64)(Instr)) + ((7) - sizeof(LONG))))
#define PI 3.14159265358979323846f
#define RAD2DEG( x  )  ( ( float )( x ) * ( float )( 180.f / PI ) )
#define DEG2RAD( x  )  ( ( float )( x ) * ( float )( ( float )PI / 180.f ) )

namespace utils {
	namespace global {
		inline bool send_packet, menu_open;
	}
	
	typedef float matrix_t[3][4];
	uint8_t* find_pattern( const char*, const char* module_name = nullptr );
	void angle_vectors( const vec3_t&, vec3_t*, vec3_t*, vec3_t* );
	void vector_angles( const vec3_t&, vec3_t& );
	vec3_t calc_angle( const vec3_t& src, const vec3_t& );
	bool world_to_screen( vec3_t, vec3_t& );
	float normalized_angle( float );
	void vector_transform( const vec3_t&, const matrix_t&, vec3_t& );
	float get_fov( const vec3_t&, const vec3_t& );
	int random_int( int, int );
	int find_string( const std::string&, const std::string&& );
	std::string base64_decode( const std::string& );
	std::string base64_encode( const std::string& );
	int viewangles_offset( );
	int aimpunch_offset( );

	template <size_t index, typename ret, class ... args_>
	__forceinline ret get_vfunc( void* thisptr, args_... args ) {
		using fn = ret( __thiscall* )( void*, args_... );

		auto fn_ptr = reinterpret_cast<fn>( ( *static_cast<uintptr_t**>( thisptr ) )[index] );
		return fn_ptr( thisptr, args... );
	}
}