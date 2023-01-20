#include "create_move.hpp"

#include "../../features/aimbot/aimbot.hpp"
#include "../../features/movement/movement.hpp"
#include "../../features/prediction/prediction.hpp"
#include "../cl_move/cl_move.hpp"

void create_move::detour( void* ecx, void* edx, int sequence_number, float input_sample_time, bool active )
{
	g_create_move->_hook.call( ecx, edx, sequence_number, input_sample_time, active );

	auto cmd          = g_interfaces->input->get_user_cmd( sequence_number );
	auto verified_cmd = g_interfaces->input->get_verified_cmd( sequence_number );

	if ( !cmd || !verified_cmd )
		return;

	std::uintptr_t* _ebp;
	__asm mov _ebp, ebp;
	bool& send_packet = *reinterpret_cast< bool* >( *_ebp - 0x1 );

	g_entity_list->run( cmd );

	if ( !g_entity_list->local )
		return;

	if ( g_cl_move->shifting && !g_cl_move->force_shift ) {
		const auto velocity = g_entity_list->local->velocity( ) * sdk::vector{ 1.f, 1.f, 0.f };
		const auto speed    = velocity.length_2d( );

		static auto accelerate_cvar = g_interfaces->cvar->find_var( "sv_accelerate" );
		static auto friction_cvar   = g_interfaces->cvar->find_var( "sv_friction" );

		const auto max_speed      = g_entity_list->local->maxspeed( );
		const auto accelerate     = accelerate_cvar->get_float( );
		const auto friction       = friction_cvar->get_float( );
		const auto max_accelerate = accelerate * g_interfaces->globals->interval_per_tick * max_speed * friction;

		if ( speed > 1.f ) {
			float wish_speed{ };

			if ( speed - max_accelerate <= -1.f ) {
				wish_speed = speed / ( accelerate * g_interfaces->globals->interval_per_tick );
			} else {
				wish_speed = max_accelerate;
			}

			sdk::qangle speed_direction = math::vector_to_angle( velocity * -1.f );
			speed_direction.yaw         = cmd->view_angles.yaw - speed_direction.yaw;
			sdk::vector speed_vector    = math::angle_to_vector( speed_direction );

			cmd->forward_move = speed_vector.x * wish_speed;
			cmd->side_move    = speed_vector.y * wish_speed;
		} else {
			cmd->forward_move = 0.f;
			cmd->side_move    = 0.f;
		}
	}

	auto backup_view = cmd->view_angles;

	g_prediction->run( cmd, g_entity_list->local );
	{
		g_aimbot->run( );
	}
	g_prediction->end( cmd, g_entity_list->local );

	g_movement->move_fix( cmd, backup_view );

	send_packet = g_cl_move->choke;

	if ( g_aimbot->projectile_choke ) {
		send_packet                = false;
		g_aimbot->projectile_choke = false;
	}

	verified_cmd->cmd = *cmd;
	verified_cmd->crc = cmd->get_checksum( );
}
