#include "cl_send_move.hpp"

void cl_send_move::detour( )
{
	// char data[ 4000 ];

	// int next_command = g_interfaces->client_state->last_out_going_command + g_interfaces->client_state->choked_commands + 1;

	// sdk::clc_move move{ };

	// move.data.start_writing( data, sizeof( data ) );

	// move.backup_commands = 2;
	// move.new_commands    = 1 + g_interfaces->client_state->choked_commands;
	//// add limit here, fuck that though lol;

	// int num_cmds = move.new_commands + move.backup_commands;

	// int from = -1;

	// bool ok = true;

	// for ( int to = next_command - num_cmds + 1; to <= next_command; to++ ) {
	//	bool new_cmd = to >= ( next_command - move.new_commands + 1 );

	//	ok = ok && g_interfaces->client->write_usercmd_delta_to_buffer( &move.data, from, to, new_cmd );

	//	from = to;
	//}

	// if ( ok ) {
	//	reinterpret_cast< sdk::i_net_channel* >( g_interfaces->engine_client->get_net_channel_info( ) )->send_net_msg( move );
	// }

	// static bool ran = false;

	// if ( !ran ) {
	//	static auto location = g_database[ HASH( "C7 45 ? ? ? ? ? 79" ) ].add( 14 ).as< void* >( );
	//	DWORD old{ };

	//	VirtualProtect( location, sizeof( char ), PAGE_EXECUTE_READWRITE, &old );

	//	memset( location, 22, sizeof( char ) );

	//	VirtualProtect( location, sizeof( char ), old, &old );

	//	ran = true;
	//}

	// if ( const auto extra_commands = g_database[ HASH( "C7 05 ? ? ? ? ? ? ? ? C7 05 ? ? ? ? ? ? ? ? DD 1D" ) ].add( 0x2 ).get( 2 ).as< int >( );
	//      extra_commands - std::clamp( extra_commands, 0, 16 ) > 0 )
	//	reinterpret_cast< sdk::i_net_channel* >( g_interfaces->engine_client->get_net_channel_info( ) )->get_choked_packets( ) -=
	//		extra_commands - std::clamp( extra_commands, 0, 16 );

	return g_cl_send_move->_hook.call( );
}
