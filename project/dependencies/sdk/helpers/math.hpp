#ifndef WEDNESDAY_WTF_MATH_HPP
#define WEDNESDAY_WTF_MATH_HPP

#include <cmath>
#include <directxmath.h>

#include "../../sdk/structs/matrix.hpp"
#include "../../sdk/structs/qangle.hpp"
#include "../../sdk/structs/vector.hpp"

#define PI           3.14159265358979323846f
#define RADPI        57.295779513082f
#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )

namespace math
{
	sdk::qangle vector_to_angle( const sdk::vector& forward );

	sdk::vector angle_to_vector( const sdk::qangle& angle );

	void angle_to_vector( const sdk::qangle& angle, sdk::vector* forward, sdk::vector* right, sdk::vector* up );

	sdk::vector vector_transform( const sdk::vector& vector1, const sdk::matrix_3x4& matrix );

	float get_fov( const sdk::qangle& view_angles, const sdk::vector& start, const sdk::vector& end );

	float calculate_angle_fov( const sdk::qangle& ang1, const sdk::qangle& ang2 );

	sdk::vector solve_quadratic( sdk::vector a, sdk::vector v, sdk::vector p, sdk::vector p0 );
} // namespace math

#endif // WEDNESDAY_WTF_MATH_HPP