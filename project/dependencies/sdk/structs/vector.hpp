#ifndef WEDNESDAY_WTF_VECTOR_HPP
#define WEDNESDAY_WTF_VECTOR_HPP

#include <cmath>
#include <iostream>

namespace sdk
{
	struct vector {
	public:
		float x{ }, y{ }, z{ };

		vector( ) = default;
		vector( float x, float y, float z = 0 ) : x( x ), y( y ), z( z ){ };

		vector( float* v )
		{
			x = v[ 0 ];
			y = v[ 1 ];
			z = v[ 2 ];
		}

		vector( const float* v )
		{
			x = v[ 0 ];
			y = v[ 1 ];
			z = v[ 2 ];
		}
		bool is_equal( const vector& vector_2 ) const
		{
			return vector_2.x == this->x && vector_2.y == this->y && vector_2.z == this->z;
		}

		float dot_product( const sdk::vector& dot ) const
		{
			return ( this->x * dot.x + this->y * dot.y + this->z * dot.z );
		}

		float length( ) const
		{
			return sqrtf( x * x + y * y + z * z );
		}

		float length_2d( ) const
		{
			return sqrtf( x * x + y * y );
		}

		float length_sqr( ) const
		{
			return x * x + y * y + z * z;
		}

		float length_sqr_2d( ) const
		{
			return x * x + y * y;
		}

		float dist_to( const vector& end ) const
		{
			return ( *this - end ).length( );
		}

		float dist_to_sqr( const vector& end ) const
		{
			return ( *this - end ).length_sqr( );
		}

		float dot( const vector other ) const noexcept
		{
			return ( x * other.x + y * other.y + z * other.z );
		}

		float normalize_in_place( )
		{
			const float length = this->length( ), radius = 1.0f / ( length + std::numeric_limits< float >::epsilon( ) );

			this->x *= radius;
			this->y *= radius;
			this->z *= radius;

			return length;
		}

		vector normalized( ) const
		{
			vector out = *this;
			out.normalize_in_place( );
			return out;
		}

		bool operator==( const vector& base ) const
		{
			return this->is_equal( base );
		}

		bool operator!=( const vector& base ) const
		{
			return !is_equal( base );
		}

		constexpr vector& operator=( const vector& base )
		{
			this->x = base.x;
			this->y = base.y;
			this->z = base.z;
			return *this;
		}

		constexpr vector& operator+=( const vector& base )
		{
			this->x += base.x;
			this->y += base.y;
			this->z += base.z;
			return *this;
		}

		constexpr vector& operator-=( const vector& base )
		{
			this->x -= base.x;
			this->y -= base.y;
			this->z -= base.z;
			return *this;
		}

		constexpr vector& operator*=( const vector& base )
		{
			this->x *= base.x;
			this->y *= base.y;
			this->z *= base.z;
			return *this;
		}

		constexpr vector& operator/=( const vector& base )
		{
			this->x /= base.x;
			this->y /= base.y;
			this->z /= base.z;
			return *this;
		}

		constexpr vector& operator+=( const float add )
		{
			this->x += add;
			this->y += add;
			this->z += add;
			return *this;
		}

		constexpr vector& operator-=( const float sub )
		{
			this->x -= sub;
			this->y -= sub;
			this->z -= sub;
			return *this;
		}

		constexpr vector& operator*=( const float mult )
		{
			this->x *= mult;
			this->y *= mult;
			this->z *= mult;
			return *this;
		}

		constexpr vector& operator/=( const float div )
		{
			this->x /= div;
			this->y /= div;
			this->z /= div;
			return *this;
		}

		vector operator+( const vector& add ) const
		{
			return vector( this->x + add.x, this->y + add.y, this->z + add.z );
		}

		vector operator-( const vector& sub ) const
		{
			return vector( this->x - sub.x, this->y - sub.y, this->z - sub.z );
		}

		vector operator*( const vector& mult ) const
		{
			return vector( this->x * mult.x, this->y * mult.y, this->z * mult.z );
		}

		vector operator/( const vector& div ) const
		{
			return vector( this->x / div.x, this->y / div.y, this->z / div.z );
		}

		vector operator+( const float add ) const
		{
			return vector( this->x + add, this->y + add, this->z + add );
		}

		vector operator-( const float sub ) const
		{
			return vector( this->x - sub, this->y - sub, this->z - sub );
		}

		vector operator*( const float mult ) const
		{
			return vector( this->x * mult, this->y * mult, this->z * mult );
		}

		vector operator/( const float div ) const
		{
			return vector( this->x / div, this->y / div, this->z / div );
		}

		float& operator[]( int i )
		{
			return ( ( float* )this )[ i ];
		}

		float operator[]( int i ) const
		{
			return ( ( float* )this )[ i ];
		}
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_VECTOR_HPP
