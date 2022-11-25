//
// Created by Liga on 2/24/2022.
//

#ifndef WEDNESDAY_WTF_COLOR_HPP
#define WEDNESDAY_WTF_COLOR_HPP

#include <d3dx9.h>
#include <iostream>

namespace sdk
{
	struct color;

	struct hsv {
		int h{ }, s{ }, v{ }, a{ };

		hsv( int hu, int sa, int vi, int al = 255 ) : h{ hu }, s{ sa }, v{ vi }, a{ al } { };

		color to_color( );
	};

	struct color {
		int r{ }, g{ }, b{ }, a{ };

		// ctors
		color( ) : r{ 0 }, g{ 0 }, b{ 0 }, a{ 255 } { };

		color( int re, int gr, int bl, int al = 255 ) : r{ re }, g{ gr }, b{ bl }, a{ al } { };

		color( std::uint32_t hex ) : r( ( hex >> 24 ) & 0xFF ), g( ( hex >> 16 ) & 0xFF ), b( ( hex >> 8 ) & 0xFF ), a( hex & 0xFF ){ };

		constexpr static auto MAX_ALPHA = ( int )255;

		std::uint32_t to_u32( ) const
		{
			return ( ( r & 0xff ) << 24 ) + ( ( g & 0xff ) << 16 ) + ( ( b & 0xff ) << 8 ) + ( a & 0xff );
		}
		color from_u32( unsigned int col )
		{
			return color( static_cast< int >( ( col >> 0 ) & 0xFF ), static_cast< int >( ( col >> 8 ) & 0xFF ),
			              static_cast< int >( ( col >> 16 ) & 0xFF ), static_cast< int >( ( col >> 24 ) & 0xFF ) );
		}
		color set_alpha( int new_alpha )
		{
			return color( r, g, b, static_cast< int >( new_alpha ) );
		}
		D3DCOLOR to_d3d( ) const
		{
			return D3DCOLOR_ARGB( a, r, g, b );
		}
		hsv to_hsv( )
		{
			auto max_lambda = []( float a, float b, float c ) -> float { return ( ( a > b ) ? ( a > c ? a : c ) : ( b > c ? b : c ) ); };

			auto min_lambda = []( float a, float b, float c ) -> float { return ( ( a < b ) ? ( a < c ? a : c ) : ( b < c ? b : c ) ); };

			float hue, saturation, vibrance;
			float red   = r / 255.f;
			float green = g / 255.f;
			float blue  = b / 255.f;

			float cmax = max_lambda( red, green, blue );
			float cmin = min_lambda( red, green, blue );
			float diff = cmax - cmin;
			if ( cmax == cmin )
				hue = 0;
			else if ( cmax == red )
				hue = fmod( ( 60.f * ( ( green - blue ) / diff ) + 360.f ), 360.f );
			else if ( cmax == green )
				hue = fmod( ( 60.f * ( ( blue - red ) / diff ) + 120.f ), 360.f );
			else if ( cmax == blue )
				hue = fmod( ( 60.f * ( ( red - green ) / diff ) + 240.f ), 360.f );

			if ( cmax == 0.f )
				saturation = 0.f;
			else
				saturation = ( diff / cmax ) * 100.f;

			vibrance = cmax * 100.f;

			return { static_cast< int >( std::round( hue ) ), static_cast< int >( std::round( saturation ) ),
				     static_cast< int >( std::round( vibrance ) ), a };
		}
		color lerp( const color col, const float t )
		{
			constexpr auto lerp = []( const int rom, const int to, const float t ) { return ( int )( ( 1.f - t ) * rom + t * to ); };

			color lerped = *this;

			lerped.r = lerp( r, col.r, t );
			lerped.g = lerp( g, col.g, t );
			lerped.b = lerp( b, col.b, t );
			lerped.a = lerp( a, col.a, t );

			return lerped;
		}
		bool operator==( const color& other ) const
		{
			return other.r == r && other.g == g && other.b == b && other.a == a;
		}
		bool operator!=( const color& other ) const
		{
			return other.r != r || other.g != g || other.b != b || other.a != a;
		}
		color& operator*=( const float f )
		{
			r = static_cast< int >( r * f );
			g = static_cast< int >( g * f );
			b = static_cast< int >( b * f );
			return *this;
		}
		// color operator( )( const int al ) const
		//{
		//	return color( r, g, b, al );
		// }
		color& operator/=( const float d )
		{
			const auto float_division = 1.f / d;
			*this *= float_division;

			return *this;
		}
		color& operator*( const float coeff ) const
		{
			auto color = *this;
			return color *= coeff;
		}
		// color& operator=( color col ) const
		//{
		//	color cf{ *this };
		//	cf.r = col.r;
		//	cf.g = col.g;
		//	cf.b = col.b;
		//	return cf;
		// }
		color operator+( color col ) const
		{
			color cf = { *this };
			cf.r += col.r;
			cf.g += col.g;
			cf.b += col.b;
			cf.a += col.a;

			return cf;
		}

		color operator-( color col ) const
		{
			color cf = { *this };
			cf.r -= col.r;
			cf.g -= col.g;
			cf.b -= col.b;
			cf.a -= col.a;

			return cf;
		}
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_COLOR_HPP
