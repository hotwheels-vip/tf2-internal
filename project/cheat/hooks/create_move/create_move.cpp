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
	bool& send_packet = *( bool* )( *_ebp - 0x1 );

	g_entity_list->run( cmd );

	if ( !g_entity_list->local )
		return;

	if ( g_cl_move->max_shifted ) {
		cmd->forward_move = -cmd->forward_move;
		cmd->side_move    = -cmd->side_move;
	}

	auto backup_viewangles = cmd->view_angles;

	g_prediction->run( cmd, g_entity_list->local );
	{
		g_aimbot->run( );
	}
	g_prediction->end( cmd, g_entity_list->local );

	g_movement->move_fix( cmd, backup_viewangles );

	send_packet = g_cl_move->choke;

	if ( g_aimbot->projectile_choke ) {
		send_packet                = false;
		g_aimbot->projectile_choke = false;
	}

	verified_cmd->cmd = *cmd;
	verified_cmd->crc = cmd->get_checksum( );
}
