#include "packet_start.hpp"
#include "../create_move/create_move.hpp"

int __fastcall packet_start::detour( void* ecx, void* edx, int incoming_sequence, int outgoing_acknowledged )
{
	// for ( const int i : g_create_move->outgoing_commands ) {
	//	if ( i == outgoing_acknowledged ) {
	//		g_packet_start->_hook.call( ecx, edx, incoming_sequence, outgoing_acknowledged );
	//		break;
	//	}
	// }

	// for ( auto i = g_create_move->outgoing_commands.begin( ); i != g_create_move->outgoing_commands.end( ); ) {
	//	if ( *i < outgoing_acknowledged )
	//		i = g_create_move->outgoing_commands.erase( i );
	//	else
	//		i++;
	// }

	// return 0;

	return g_packet_start->_hook.call( ecx, edx, incoming_sequence, outgoing_acknowledged );
}
