#pragma once
#include <algorithm>
#include <cmath>

class vec3_t {
public:
	vec3_t( ) {
		x = y = z = 0.0f;
	}
	
	vec3_t( const float fx, const float fy, const float fz ) {
		x = fx;
		y = fy;
		z = fz;
	}

	float x, y, z;

	vec3_t& operator+=( const vec3_t& v ) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec3_t& operator-=( const vec3_t& v ) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	vec3_t& operator*=( const float v ) {
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	vec3_t operator+( const vec3_t& v ) {
		return vec3_t{ x + v.x, y + v.y, z + v.z };
	}

	vec3_t operator-( const vec3_t& v ) {
		return vec3_t{ x - v.x, y - v.y, z - v.z };
	}

	vec3_t& operator+( const float& v ) {
		x = x + v;
		y = y + v;
		z = z + v;
		return *this;
	}

	vec3_t& operator-( const float& v ) {
		x = x - v;
		y = y - v;
		z = z - v;
		return *this;
	}

	vec3_t operator*( const float v ) {
		return vec3_t{ x * v, y * v, z * v };
	}

	vec3_t operator/( const float fl ) const {
		return vec3_t( x / fl, y / fl, z / fl );
	}

	vec3_t operator+( const vec3_t& v ) const {
		return vec3_t( x + v.x, y + v.y, z + v.z );
	}

	bool operator==( const vec3_t& v ) const {
		return x == v.x && y == v.y && z == v.z;
	}

	bool operator!=( const vec3_t& v ) const {
		return x != v.x || y != v.y || z != v.z;
	}

	vec3_t operator*( const float fl ) const {
		return vec3_t( x * fl, y * fl, z * fl );
	}

	vec3_t operator*( const vec3_t& v ) const {
		return vec3_t( x * v.x, y * v.y, z * v.z );
	}

	vec3_t operator-( const vec3_t& v ) const {
		return vec3_t( x - v.x, y - v.y, z - v.z );
	}

	vec3_t& operator/=( const float fl ) {
		x /= fl;
		y /= fl;
		z /= fl;
		return *this;
	}

	float& operator[]( const int i ) {
		return reinterpret_cast<float*>( this )[i];
	}

	[[nodiscard]] float length( ) const {
		return sqrtf( x * x + y * y + z * z );
	}

	[[nodiscard]] float length_sqr( ) const {
		return x * x + y * y + z * z;
	}
	
	[[nodiscard]] float length_2d( ) const {
		return sqrtf( x * x + y * y );
	}

	[[nodiscard]] float dist_to( const vec3_t& other ) const {
		vec3_t delta;

		delta.x = x - other.x;
		delta.y = y - other.y;
		delta.z = z - other.z;

		return delta.length( );
	}

	void normalize( );
	vec3_t normalized( ) const {
		auto vec = *this;
		vec.normalize( );
		return vec;
	}

	void clamp( ) {
		normalize( );

		x = std::clamp( x, -89.0f, 89.0f );
		y = std::clamp( y, -180.0f, 180.0f );
		z = 0.0f;
	}

	vec3_t clamped( ) const {
		auto vec = *this;
		vec.clamp( );
		return vec;
	}

	float normalize_float( ) {
		const auto len = length( );

		*this /= length( ) + std::numeric_limits< float >::epsilon( );

		return len;
	}

	[[nodiscard]] float dot( const vec3_t& other ) const {
		return x * other.x + y * other.y + z * other.z;
	}

	[[nodiscard]] vec3_t cross( const vec3_t &v ) const {
		return {
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		};
	}

	bool empty( ) const {
		return x == 0 && y == 0 && z == 0;
	}
	
	void init( const float ix = 0.0f, const float iy = 0.0f, const float iz = 0.0f ) {
		x = ix;
		y = iy;
		z = iz;
	}
};

struct vec4_t {
	float x, y, z, w;
};