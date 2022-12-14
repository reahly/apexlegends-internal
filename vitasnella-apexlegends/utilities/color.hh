#pragma once
#include <cstdint>

struct color {
	int a, r, g, b;
	color( ) = default;

	color( const int r, const int g, const int b, const int a = 255 ): _color{ } {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	explicit color( const uint32_t color ): _color{ } {
		this->a = color >> 24 & 0xff;
		this->r = color >> 16 & 0xff;
		this->g = color >> 8 & 0xff;
		this->b = color & 0xff;
	}

	static color from_uint( const uint32_t uint ) {
		return color( uint );
	}

	unsigned char& operator[ ]( const int index ) {
		return _color[index];
	}

	template <typename T>
	[[nodiscard]] color hsv_to_rgb( T h, T s, T v, const float alpha ) const {
		int _r, _g, _b;

		if ( s != 0 ) {

			h == 360 ? h = 0 : h = h / 60;
			auto i = static_cast<int>( trunc( h ) );
			int f = h - i;

			const int p = v * ( 1 - s );
			const int q = v * ( 1 - s * f );
			const int t = v * ( 1 - s * ( 1 - f ) );

			switch ( i ) {
			case 0:
				_r = v;
				_g = t;
				_b = p;
				break;

			case 1:
				_r = q;
				_g = v;
				_b = p;
				break;

			case 2:
				_r = p;
				_g = v;
				_b = t;
				break;

			case 3:
				_r = p;
				_g = q;
				_b = v;
				break;

			case 4:
				_r = t;
				_g = p;
				_b = v;
				break;

			default:
				_r = v;
				_g = p;
				_b = q;
				break;
			}
		} else {
			_r = v;
			_g = v;
			_b = v;
		}

		return color( static_cast<uint8_t>( _r * 255 ), static_cast<uint8_t>( _g * 255 ),
			static_cast<uint8_t>( _b * 255 ), alpha );
	}

	unsigned char _color[4];
};