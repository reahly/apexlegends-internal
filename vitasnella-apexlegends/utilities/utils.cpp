#include "utils.hh"
#include <lazy_importer.hh>
#include <random>
#include <sstream>
#include <vector>
#include <Windows.h>
#include "../imgui/imgui.h"
#include "../interfaces/interfaces.hh"

uint8_t* utils::find_pattern( const char* signature, const char* module_name ) {
	static auto pattern_to_byte = [ ]( const char* pattern ) {
		auto bytes = std::vector<int>{ };
		auto* const start = const_cast<char*>( pattern );
		const auto* const end = const_cast<char*>( pattern ) + strlen( pattern );

		for ( auto* current = start; current < end; ++current ) {
			if ( *current == '?' ) {
				++current;
				if ( *current == '?' )
					++current;
				bytes.push_back( -1 );
			} else {
				bytes.push_back( strtoul( current, &current, 16 ) );
			}
		}
		return bytes;
	};

	auto* const module = LI_FN( GetModuleHandleA ).cached( )( module_name );
	auto* const dos_headers = reinterpret_cast<PIMAGE_DOS_HEADER>( module );
	if ( !dos_headers )
		return nullptr;

	auto* const nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>( reinterpret_cast<std::uint8_t*>( module ) + dos_headers->e_lfanew );

	auto pattern_bytes = pattern_to_byte( signature );
	auto* const scan_bytes = reinterpret_cast<std::uint8_t*>( module );

	const auto s = pattern_bytes.size( );
	auto* const d = pattern_bytes.data( );

	for ( auto i = 0ul; i < nt_headers->OptionalHeader.SizeOfImage - s; ++i ) {
		auto found = true;
		for ( auto j = 0ul; j < s; ++j ) {
			if ( scan_bytes[i + j] != d[j] && d[j] != -1 ) {
				found = false;
				break;
			}
		}
		if ( found ) {
			return &scan_bytes[i];
		}
	}
	return nullptr;
}

void utils::angle_vectors( const vec3_t& ang, vec3_t* out_forward, vec3_t* out_right, vec3_t* out_up ) {
	const auto sincos = [ ]( const float radians, float* sine, float* cosine ) {
		*sine = sin( radians );
		*cosine = cos( radians );
	};

	float sr, sp, sy, cr, cp, cy;

	sincos( DEG2RAD( ang.x ), &sp, &cp );
	sincos( DEG2RAD( ang.y ), &sy, &cy );
	sincos( DEG2RAD( ang.z ), &sr, &cr );

	if ( out_forward ) {
		out_forward->x = cp * cy;
		out_forward->y = cp * sy;
		out_forward->z = -sp;
	}

	if ( out_right ) {
		out_right->x = -1 * sr * sp * cy + -1 * cr * -sy;
		out_right->y = -1 * sr * sp * sy + -1 * cr * cy;
		out_right->z = -1 * sr * cp;
	}

	if ( out_up ) {
		out_up->x = cr * sp * cy + -sr * -sy;
		out_up->y = cr * sp * sy + -sr * cy;
		out_up->z = cr * cp;
	}
}

void utils::vector_angles( const vec3_t& forward, vec3_t& angles ) {
	if ( forward.x == 0.f && forward.y == 0.f ) {
		angles.x = forward.z > 0.f ? -90.f : 90.f;
		angles.y = 0.f;
	} else {
		angles.x = RAD2DEG( atan2( -forward.z, forward.length_2d( ) ) );
		angles.y = RAD2DEG( atan2( forward.y, forward.x ) );
	}
}

vec3_t utils::calc_angle( const vec3_t& src, const vec3_t& dst ) {
	const auto delta = src - dst;
	if ( delta.length( ) <= 0.0f )
		return vec3_t( 0.0f, 0.0f, 0.0f );

	if ( delta.z == 0.0f && delta.length( ) == 0.0f )
		return vec3_t( 0.0f, 0.0f, 0.0f );

	if ( delta.y == 0.0f && delta.x == 0.0f )
		return vec3_t( 0.0f, 0.0f, 0.0f );

	vec3_t angles;
	angles.x = asinf( delta.z / delta.length( ) ) * 57.295779513082f;
	angles.y = atanf( delta.y / delta.x ) * 57.295779513082f;
	angles.z = 0.0f;

	if ( delta.x >= 0.0f )
		angles.y += 180.0f;

	angles.normalize( );
	return angles;
}

bool utils::world_to_screen( vec3_t source, vec3_t& destination ) {
	const auto get_view_matrix = []( ) -> float(*)[4] {
		static auto view_render = uintptr_t( );
		if ( !view_render )
			view_render = *reinterpret_cast<uintptr_t*>( RESOLVE_RVA( utils::find_pattern( _( "48 8B 0D ? ? ? ? 4C 8D 05 ? ? ? ? 48 8B 01 48 8B 90 ? ? ? ? 49 3B C0 75 4F 48 8B 05 ? ? ? ?" ) ) ) );

		if ( !view_render )
			return nullptr;
		
		auto* const view_matrix = **reinterpret_cast<matrix_t**>( view_render + 0x1b3bd0 );
		return view_matrix;
	};

	const auto* const matrix = get_view_matrix( );
	auto w = 0.0f;

	destination[0] = matrix[0][0] * source[0] + matrix[0][1] * source[1] + matrix[0][2] * source[2]
		+ matrix[0][3];
	destination[1] = matrix[1][0] * source[0] + matrix[1][1] * source[1] + matrix[1][2] * source[2]
		+ matrix[1][3];
	w = matrix[3][0] * source[0] + matrix[3][1] * source[1] + matrix[3][2] * source[2] + matrix[3][
		3];

	if ( w < 0.01f )
		return false;

	const auto invw = 1.f / w;
	destination[0] *= invw;
	destination[1] *= invw;

	auto x = ImGui::GetIO( ).DisplaySize.x / 2.f;
	auto y = ImGui::GetIO( ).DisplaySize.y / 2.f;
	x += .5f * destination[0] * ImGui::GetIO( ).DisplaySize.x + .5f;
	y -= .5f * destination[1] * ImGui::GetIO( ).DisplaySize.y + .5f;

	destination[0] = x;
	destination[1] = y;

	return true;
}

float utils::normalized_angle( float angle ) {
	const auto normalize_angle = [ ]( float& angle ) {
		if ( !std::isfinite( angle ) ) {
			angle = 0.f;
			return;
		}

		if ( angle >= -180.f && angle <= 180.f )
			return;

		const auto rot = std::round( std::abs( angle / 360.f ) );
		angle = angle < 0.f ? angle + 360.f * rot : angle - 360.f * rot;
	};

	normalize_angle( angle );
	return angle;
}

void utils::vector_transform( const vec3_t& in1, const matrix_t& in2, vec3_t& out ) {
	const auto dot_product = [ ] ( const vec3_t& a, const vec3_t& b ) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	};
	
	out[ 0 ] = dot_product( in1, vec3_t( in2[ 0 ][ 0 ], in2[ 0 ][ 1 ], in2[ 0 ][ 2 ] ) ) + in2[ 0 ][ 3 ];
	out[ 1 ] = dot_product( in1, vec3_t( in2[ 1 ][ 0 ], in2[ 1 ][ 1 ], in2[ 1 ][ 2 ] ) ) + in2[ 1 ][ 3 ];
	out[ 2 ] = dot_product( in1, vec3_t( in2[ 2 ][ 0 ], in2[ 2 ][ 1 ], in2[ 2 ][ 2 ] ) ) + in2[ 2 ][ 3 ];
}

float utils::get_fov( const vec3_t& va, const vec3_t& aimpos ) {
	auto ang = aimpos - va;
	while ( ang.y <= -180.0f ) ang.y += 360.0f;
	while ( ang.y > 180.0f ) ang.y -= 360.0f;

	return sqrtf( ang.x * ang.x + ang.y * ang.y );
}

int utils::random_int( const int min, const int max ) {
	std::random_device rd;
	std::mt19937 rng( rd( ) );
	const std::uniform_int_distribution<int> uni( min, max );

	return static_cast<int>( uni( rng ) );
}

template <typename charT>
struct my_equal {
	explicit my_equal( const std::locale& loc ) : loc_( loc ) {
	}

	bool operator()( charT ch1, charT ch2 ) {
		return std::toupper( ch1 ) == std::toupper( ch2 );
	}

private:
	const std::locale& loc_;
};

int utils::find_string( const std::string& str1, const std::string&& str2 ) {
	const auto loc = std::locale( );

	const auto it = std::ranges::search( str1, str2, my_equal<std::string::value_type>( loc ) ).begin();
	if ( it != str1.end( ) )
		return it - str1.begin( );

	return -1;
}

std::string utils::base64_decode( const std::string& encoded_string ) {
	const std::string base64_chars =
		_( "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz"
			"0123456789+/" );

	std::string out;
	std::vector<int> T( 256, -1 );
	for ( auto i = 0u; i < 64; i++ ) T[base64_chars[i]] = i;

	auto val = 0, valb = -8;
	for ( const unsigned char c : encoded_string ) {
		if ( T[c] == -1 ) break;
		val = ( val << 6 ) + T[c];
		valb += 6;
		if ( valb >= 0 ) {
			out.push_back( static_cast<char>( val >> valb & 0xFF ) );
			valb -= 8;
		}
	}

	return out;
}

std::string utils::base64_encode( const std::string& decoded_string ) {
	std::string out;

	auto val = 0, valb = -6;
	for ( const auto c : decoded_string ) {
		val = ( val << 8 ) + c;
		valb += 8;
		while ( valb >= 0 ) {
			out.push_back( _( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" )[val >> valb & 0x3F] );
			valb -= 6;
		}
	}
	if ( valb > -6 ) out.push_back( _( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" )[val << 8 >> valb + 8 & 0x3F] );
	while ( out.size( ) % 4 ) out.push_back( '=' );

	return out;
}

int utils::viewangles_offset( ) {
	/*static uint8_t* addr = nullptr;
	if ( !addr )
		addr = find_pattern( _( "F3 0F 11 83 28 25 00 00 F3 0F 10 0D ? ? ? ?" ) ) + 4;
	
	if ( !addr )
		return 0;

	return *reinterpret_cast<int*>( addr );*/
	return 0x2470;
}

int utils::aimpunch_offset( ) {
	/*static auto* addr = find_pattern( _( "C7 05 71 BC 12 0A 50 24 00 00 ? ? ? ? ? ? ? ? ? ?" ) ) + 6;
	if ( !addr )
		return 0;

	return *reinterpret_cast<int*>( addr );*/
	return 0x2390;
}