#include "movement.hpp"

void movement::move_fix( sdk::qangle angle )
{
	static auto cl_forwardspeed = g_interfaces->cvar->find_var( "cl_forwardspeed" );
	static auto cl_sidespeed    = g_interfaces->cvar->find_var( "cl_sidespeed" );
	static auto cl_upspeed      = g_interfaces->cvar->find_var( "cl_upspeed" );

	[[unlikely]] if ( !cl_upspeed || !cl_sidespeed || !cl_forwardspeed )
		return;

	const float max_forward_speed = cl_forwardspeed->get_float( );
	const float max_side_speed    = cl_sidespeed->get_float( );
	const float max_up_speed      = cl_upspeed->get_float( );

	sdk::vector forward = { }, right = { }, up = { };
	{
		math::angle_to_vector( angle, &forward, &right, &up );
		forward.z = right.z = up.x = up.y = 0.f;
		forward.normalize_in_place( );
		right.normalize_in_place( );
		up.normalize_in_place( );
	}

	sdk::vector old_forward = { }, old_right = { }, old_up = { };
	{
		math::angle_to_vector( g_cmd->view_angles, &old_forward, &old_right, &old_up );
		old_forward.z = old_right.z = old_up.x = old_up.y = 0.f;
		old_forward.normalize_in_place( );
		old_right.normalize_in_place( );
		old_up.normalize_in_place( );
	}

	const float pitch_forward = forward.x * g_cmd->forward_move;
	const float yaw_forward   = forward.y * g_cmd->forward_move;
	const float pitch_side    = right.x * g_cmd->side_move;
	const float yaw_side      = right.y * g_cmd->side_move;
	const float roll_up       = up.z * g_cmd->up_move;

	const float x =
		old_forward.x * pitch_side + old_forward.y * yaw_side + old_forward.x * pitch_forward + old_forward.y * yaw_forward + old_forward.z * roll_up;

	const float y =
		old_right.x * pitch_side + old_right.y * yaw_side + old_right.x * pitch_forward + old_right.y * yaw_forward + old_right.z * roll_up;

	const float z = old_up.x * yaw_side + old_up.y * pitch_side + old_up.x * yaw_forward + old_up.y * pitch_forward + old_up.z * roll_up;

	g_cmd->forward_move = std::clamp( x, -max_forward_speed, max_forward_speed );
	g_cmd->side_move    = std::clamp( y, -max_side_speed, max_side_speed );
	g_cmd->up_move      = std::clamp( z, -max_up_speed, max_up_speed );

	g_cmd->view_angles.normalize( );
}

void movement::auto_stop( )
{
	const auto velocity = g_local->velocity( ) * sdk::vector{ 1.f, 1.f, 0.f };
	const auto speed    = velocity.length_2d( );

	static auto accelerate_cvar = g_interfaces->cvar->find_var( "sv_accelerate" );
	static auto friction_cvar   = g_interfaces->cvar->find_var( "sv_friction" );

	const auto max_speed      = g_local->maxspeed( );
	const auto accelerate     = accelerate_cvar->get_float( );
	const auto friction       = friction_cvar->get_float( );
	const auto max_accelerate = accelerate * g_interfaces->globals->interval_per_tick * max_speed * friction;

	if ( speed > 1.f ) {
		float wish_speed;

		if ( speed - max_accelerate <= -1.f ) {
			wish_speed = speed / ( accelerate * g_interfaces->globals->interval_per_tick );
		} else {
			wish_speed = max_accelerate;
		}

		sdk::qangle speed_direction    = math::vector_to_angle( velocity * -1.f );
		speed_direction.yaw            = g_cmd->view_angles.yaw - speed_direction.yaw;
		const sdk::vector speed_vector = math::angle_to_vector( speed_direction );

		g_cmd->forward_move = speed_vector.x * wish_speed;
		g_cmd->side_move    = speed_vector.y * wish_speed;
	} else {
		g_cmd->forward_move = 0.f;
		g_cmd->side_move    = 0.f;
	}
}
