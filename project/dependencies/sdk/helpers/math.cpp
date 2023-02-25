#include "math.hpp"
#include <algorithm>

#include "../../../cheat/hooks/paint_traverse/paint_traverse.hpp"
#include "../cheat/helpers/include.hpp"

void math::angle_to_vector( const sdk::qangle& angle, sdk::vector* forward, sdk::vector* right, sdk::vector* up )
{
	float sp, sy, sr, cp, cy, cr;

	DirectX::XMScalarSinCos( &sp, &cp, DEG2RAD( angle.pitch ) );
	DirectX::XMScalarSinCos( &sy, &cy, DEG2RAD( angle.yaw ) );
	DirectX::XMScalarSinCos( &sr, &cr, DEG2RAD( angle.roll ) );

	if ( forward != nullptr ) {
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if ( right != nullptr ) {
		right->x = -1 * sr * sp * cy + -1 * cr * -sy;
		right->y = -1 * sr * sp * sy + -1 * cr * cy;
		right->z = -1 * sr * cp;
	}

	if ( up != nullptr ) {
		up->x = cr * sp * cy + -sr * -sy;
		up->y = cr * sp * sy + -sr * cy;
		up->z = cr * cp;
	}
}

sdk::vector math::angle_to_vector( const sdk::qangle& angle )
{
	const auto sy = std::sin( angle.yaw / 180.f * PI );
	const auto cy = std::cos( angle.yaw / 180.f * PI );

	const auto sp = std::sin( angle.pitch / 180.f * PI );
	const auto cp = std::cos( angle.pitch / 180.f * PI );

	return sdk::vector( cp * cy, cp * sy, -sp );
}

sdk::qangle math::vector_to_angle( const sdk::vector& forward )
{
	float pitch, yaw, buffer;

	if ( forward.y == 0 && forward.x == 0 ) {
		yaw = 0;

		if ( forward.z > 0 )
			pitch = 270;
		else
			pitch = 90;
	} else {
		yaw = RAD2DEG( atan2f( forward.y, forward.x ) );

		if ( yaw < 0 )
			yaw += 360;

		buffer = forward.length_2d( );

		pitch = RAD2DEG( atan2f( -forward.z, buffer ) );

		if ( pitch < 0 )
			pitch += 360;
	}

	return { pitch, yaw, 0 };
}

sdk::vector math::vector_transform( const sdk::vector& vector1, const sdk::matrix_3x4& matrix )
{
	sdk::vector output{ };

	for ( int i = 0; i < 3; i++ )
		output[ i ] = vector1.dot( matrix.data[ i ] ) + matrix.data[ i ][ 3 ];

	return output;
}

// added another due to: what the fuck is this?????????
float math::get_fov( const sdk::qangle& view_angles, const sdk::vector& start, const sdk::vector& end )
{
	sdk::vector forward, direction = ( end - start ).normalized( );

	forward = angle_to_vector( view_angles );

	return max( RAD2DEG( std::acos( forward.dot_product( direction ) ) ), 0.f );
}

float math::calculate_angle_fov( const sdk::qangle& ang1, const sdk::qangle& ang2 )
{
	sdk::vector ang, aim;

	aim = angle_to_vector( ang1 );
	ang = angle_to_vector( ang2 );

	return RAD2DEG( acos( aim.dot( ang ) / aim.length_sqr( ) ) );
}

sdk::vector math::solve_quadratic( sdk::vector a, sdk::vector v, sdk::vector p, sdk::vector p0 )
{
	auto t4 = std::powf( ( std::powf( a.x, 2.f ) + std::powf( a.y, 2.f ) + std::powf( a.z, 2.f ) ) / 4.f, 4.f ); // (num)t^4
	auto t3 = std::powf( a.x * v.x + a.y * v.y + a.z * v.z, 3.f );                                               // (num)t^3
	auto t2 = std::powf( std::powf( v.x, 2.f ) + std::powf( v.y, 2.f ) + std::powf( v.z, 2.f ) /*- s^2*/ + p0.x * a.x + p0.y * a.y + p0.z * a.z,
	                     2.f );                             // (num)t^2
	auto t  = 2 * ( p0.x * v.x + p0.y * v.y + p0.z * v.z ); // (num)t
	auto l  = std::powf( p.x, 2.f ) + std::powf( p.y, 2.f ) + std::powf( p.z, 2.f );

	auto ts = t4 + t3 + t2 + t;
	auto s  = l / ts;

	return { s, s, s };
}

float math::remap_val_clamped( float val, float a, float b, float c, float d )
{
	float v = ( val - a ) / ( b - a );
	v       = std::clamp( v, 0.f, 1.f );

	return c + ( d - c ) * v;
}

std::pair< ImVec2, bool > math::world_to_screen( sdk::vector position )
{
	auto on_screen = true;

	const auto matrix = g_paint_traverse->matrix;

	// not really needed but prevents useless math to be done
	if ( !matrix.data ) {
		on_screen = false;
		return std::make_pair( ImVec2{ }, on_screen );
	}

	float width = matrix[ 3 ][ 0 ] * position.x + matrix[ 3 ][ 1 ] * position.y + matrix[ 3 ][ 2 ] * position.z + matrix[ 3 ][ 3 ];

	if ( width < 0.001f ) {
		on_screen = false;

		return std::make_pair( ImVec2{ }, on_screen );
	}

	float inverse = 1.f / width;

	ImVec2 screen;

	screen.x = ( matrix[ 0 ][ 0 ] * position.x + matrix[ 0 ][ 1 ] * position.y + matrix[ 0 ][ 2 ] * position.z + matrix[ 0 ][ 3 ] ) * inverse;
	screen.y = ( matrix[ 1 ][ 0 ] * position.x + matrix[ 1 ][ 1 ] * position.y + matrix[ 1 ][ 2 ] * position.z + matrix[ 1 ][ 3 ] ) * inverse;

	auto screen_size = ImGui::GetIO( ).DisplaySize;

	screen.x = ( screen_size.x * 0.5f ) + ( screen.x * screen_size.x ) * 0.5f;
	screen.y = ( screen_size.y * 0.5f ) - ( screen.y * screen_size.y ) * 0.5f;

	return std::make_pair( screen, on_screen );
}
