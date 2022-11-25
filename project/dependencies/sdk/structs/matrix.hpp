//
// Created by blanket on 2/24/2022.
//

#ifndef WEDNESDAY_WTF_MATRIX_HPP
#define WEDNESDAY_WTF_MATRIX_HPP
#include "qangle.hpp"
#include "vector.hpp"
#include <iostream>

namespace sdk
{
	struct matrix_3x4 {
	public:
		float data[ 3 ][ 4 ]{ };

		matrix_3x4( ) = default;

		float* operator[]( const std::int32_t idx )
		{
			return data[ idx ];
		}

		const float* operator[]( const std::int32_t idx ) const
		{
			return data[ idx ];
		}

		static void copy( const matrix_3x4& src, matrix_3x4& dst )
		{
			for ( std::int32_t i = 0; i < 3; i++ )
				for ( std::int32_t j = 0; j < 4; j++ )
					dst[ i ][ j ] = src[ i ][ j ];
		}

		static void multiply( const matrix_3x4& in1, const matrix_3x4& in2, matrix_3x4& out )
		{
			if ( &in1 == &out ) {
				matrix_3x4 in1b;
				copy( in1, in1b );
				multiply( in1b, in2, out );
				return;
			}

			if ( &in2 == &out ) {
				matrix_3x4 in2b;
				copy( in2, in2b );
				multiply( in1, in2b, out );
				return;
			}

			out[ 0 ][ 0 ] = in1[ 0 ][ 0 ] * in2[ 0 ][ 0 ] + in1[ 0 ][ 1 ] * in2[ 1 ][ 0 ] + in1[ 0 ][ 2 ] * in2[ 2 ][ 0 ];
			out[ 0 ][ 1 ] = in1[ 0 ][ 0 ] * in2[ 0 ][ 1 ] + in1[ 0 ][ 1 ] * in2[ 1 ][ 1 ] + in1[ 0 ][ 2 ] * in2[ 2 ][ 1 ];
			out[ 0 ][ 2 ] = in1[ 0 ][ 0 ] * in2[ 0 ][ 2 ] + in1[ 0 ][ 1 ] * in2[ 1 ][ 2 ] + in1[ 0 ][ 2 ] * in2[ 2 ][ 2 ];
			out[ 0 ][ 3 ] = in1[ 0 ][ 0 ] * in2[ 0 ][ 3 ] + in1[ 0 ][ 1 ] * in2[ 1 ][ 3 ] + in1[ 0 ][ 2 ] * in2[ 2 ][ 3 ] + in1[ 0 ][ 3 ];

			out[ 1 ][ 0 ] = in1[ 1 ][ 0 ] * in2[ 0 ][ 0 ] + in1[ 1 ][ 1 ] * in2[ 1 ][ 0 ] + in1[ 1 ][ 2 ] * in2[ 2 ][ 0 ];
			out[ 1 ][ 1 ] = in1[ 1 ][ 0 ] * in2[ 0 ][ 1 ] + in1[ 1 ][ 1 ] * in2[ 1 ][ 1 ] + in1[ 1 ][ 2 ] * in2[ 2 ][ 1 ];
			out[ 1 ][ 2 ] = in1[ 1 ][ 0 ] * in2[ 0 ][ 2 ] + in1[ 1 ][ 1 ] * in2[ 1 ][ 2 ] + in1[ 1 ][ 2 ] * in2[ 2 ][ 2 ];
			out[ 1 ][ 3 ] = in1[ 1 ][ 0 ] * in2[ 0 ][ 3 ] + in1[ 1 ][ 1 ] * in2[ 1 ][ 3 ] + in1[ 1 ][ 2 ] * in2[ 2 ][ 3 ] + in1[ 1 ][ 3 ];

			out[ 2 ][ 0 ] = in1[ 2 ][ 0 ] * in2[ 0 ][ 0 ] + in1[ 2 ][ 1 ] * in2[ 1 ][ 0 ] + in1[ 2 ][ 2 ] * in2[ 2 ][ 0 ];
			out[ 2 ][ 1 ] = in1[ 2 ][ 0 ] * in2[ 0 ][ 1 ] + in1[ 2 ][ 1 ] * in2[ 1 ][ 1 ] + in1[ 2 ][ 2 ] * in2[ 2 ][ 1 ];
			out[ 2 ][ 2 ] = in1[ 2 ][ 0 ] * in2[ 0 ][ 2 ] + in1[ 2 ][ 1 ] * in2[ 1 ][ 2 ] + in1[ 2 ][ 2 ] * in2[ 2 ][ 2 ];
			out[ 2 ][ 3 ] = in1[ 2 ][ 0 ] * in2[ 0 ][ 3 ] + in1[ 2 ][ 1 ] * in2[ 1 ][ 3 ] + in1[ 2 ][ 2 ] * in2[ 2 ][ 3 ] + in1[ 2 ][ 3 ];
		}

		qangle to_angle( )
		{
			qangle angles;

			float forward[ 3 ];
			float left[ 3 ];
			float up[ 3 ];

			forward[ 0 ] = data[ 0 ][ 0 ];
			forward[ 1 ] = data[ 1 ][ 0 ];
			forward[ 2 ] = data[ 2 ][ 0 ];
			left[ 0 ]    = data[ 0 ][ 1 ];
			left[ 1 ]    = data[ 1 ][ 1 ];
			left[ 2 ]    = data[ 2 ][ 1 ];
			up[ 2 ]      = data[ 2 ][ 2 ];

			float xyDist = sqrtf( forward[ 0 ] * forward[ 0 ] + forward[ 1 ] * forward[ 1 ] );

			// enough here to get angles?
			if ( xyDist > 0.001f ) {
				// (yaw)	y = ATAN( forward.y, forward.x );		-- in our space, forward is the X axis
				angles.yaw = ( ( float )( ( atan2f( forward[ 1 ], forward[ 0 ] ) ) ) * ( float )( 180.0f / ( float )( 3.14159265358979323846f ) ) );

				// (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
				angles.pitch = ( ( float )( ( atan2f( -forward[ 2 ], xyDist ) ) ) *
				                 ( float )( 180.0f / ( float )( 3.14159265358979323846f ) ) ); // RAD2DEG( atan2f( -forward[ 2 ], xyDist ) );

				// (roll)	z = ATAN( left.z, up.z );
				angles.roll = ( ( float )( ( atan2f( left[ 2 ], up[ 2 ] ) ) ) * ( float )( 180.0f / ( float )( 3.14159265358979323846f ) ) );
				// RAD2DEG( atan2f( left[ 2 ], up[ 2 ] ) );
			} else // forward is mostly Z, gimbal lock-
			{
				// (yaw)	y = ATAN( -left.x, left.y );			-- forward is mostly z, so use right for yaw
				angles.yaw = ( ( float )( ( atan2f( -left[ 0 ], left[ 1 ] ) ) ) * ( float )( 180.0f / ( float )( 3.14159265358979323846f ) ) );

				// RAD2DEG( atan2f( -left[ 0 ], left[ 1 ] ) );

				// (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
				angles.pitch = ( ( float )( ( atan2f( -forward[ 2 ], xyDist ) ) ) * ( float )( 180.0f / ( float )( 3.14159265358979323846f ) ) );
				// RAD2DEG( atan2f( -forward[ 2 ], xyDist ) );

				// Assume no roll in this case as one degree of freedom has been lost (i.e. yaw == roll)
				angles.roll = 0;
			}

			return angles;
		}

		vector to_vector( int i )
		{
			return { data[ 0 ][ i ], data[ 1 ][ i ], data[ 2 ][ i ] };
		}
	};

	struct matrix_4x4 {
	public:
		float data[ 4 ][ 4 ]{ };

		matrix_4x4( ) = default;

		float* operator[]( const std::int32_t idx )
		{
			return data[ idx ];
		}

		const float* operator[]( const std::int32_t idx ) const
		{
			return data[ idx ];
		}
	};

	struct view_matrix : matrix_4x4 {
	public:
		view_matrix( ) = default;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_MATRIX_HPP
