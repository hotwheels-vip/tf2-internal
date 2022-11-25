#include "movement.hpp"

void movement::move_fix( sdk::c_user_cmd* cmd, sdk::qangle angle )
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
		math::angle_to_vector( cmd->view_angles, &old_forward, &old_right, &old_up );
		old_forward.z = old_right.z = old_up.x = old_up.y = 0.f;
		old_forward.normalize_in_place( );
		old_right.normalize_in_place( );
		old_up.normalize_in_place( );
	}

	const float pitch_forward = forward.x * cmd->forward_move;
	const float yaw_forward   = forward.y * cmd->forward_move;
	const float pitch_side    = right.x * cmd->side_move;
	const float yaw_side      = right.y * cmd->side_move;
	const float roll_up       = up.z * cmd->up_move;

	const float x =
		old_forward.x * pitch_side + old_forward.y * yaw_side + old_forward.x * pitch_forward + old_forward.y * yaw_forward + old_forward.z * roll_up;

	const float y =
		old_right.x * pitch_side + old_right.y * yaw_side + old_right.x * pitch_forward + old_right.y * yaw_forward + old_right.z * roll_up;

	const float z = old_up.x * yaw_side + old_up.y * pitch_side + old_up.x * yaw_forward + old_up.y * pitch_forward + old_up.z * roll_up;

	cmd->forward_move = std::clamp( x, -max_forward_speed, max_forward_speed );
	cmd->side_move    = std::clamp( y, -max_side_speed, max_side_speed );
	cmd->up_move      = std::clamp( z, -max_up_speed, max_up_speed );

	cmd->view_angles.normalize( );
}
