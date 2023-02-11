#include "create_move.hpp"

#include "../../features/aimbot/aimbot.hpp"
#include "../../features/lagcomp/lagcomp.hpp"
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

	if ( !g_local )
		return;

	if ( !g_cl_move->shifting )
		g_lagcomp->update( );

	auto backup_view = cmd->view_angles;

	g_prediction->run( );
	{
		g_aimbot->run( );
	}
	g_prediction->end( );

	g_movement->move_fix( backup_view );

	send_packet = g_cl_move->choke;

	if ( g_aimbot->projectile_choke ) {
		send_packet                = false;
		g_aimbot->projectile_choke = false;
	}

	if ( g_cl_move->shifting && !g_cl_move->force_shift )
		g_movement->auto_stop( );

	// if ( const auto net_channel = reinterpret_cast< sdk::i_net_channel* >( g_interfaces->engine_client->get_net_channel_info( ) ) ) {
	//	send_packet = net_channel->get_choked_packets( ) < 19 ? false : true;
	// }

	verified_cmd->cmd = *cmd;
	verified_cmd->crc = cmd->get_checksum( );

	// if ( send_packet ) {
	//	g_create_move->outgoing_commands.emplace_front( cmd->command_number );
	// } else {
	//	if ( const auto net_channel = reinterpret_cast< sdk::i_net_channel* >( g_interfaces->engine_client->get_net_channel_info( ) ) ) {
	//		const int backup_choked = net_channel->get_choked_packets( );

	//		net_channel->get_choked_packets( ) = 0;
	//		net_channel->send_datagram( nullptr );

	//		*reinterpret_cast< int* >( reinterpret_cast< std::uintptr_t >( net_channel ) + 0x8 ) -= 1;

	//		net_channel->get_choked_packets( ) = backup_choked;
	//	}
	//}
}
