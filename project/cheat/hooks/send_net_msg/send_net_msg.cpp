#include <algorithm>
#include <iostream>

#include "send_net_msg.hpp"

bool __fastcall send_net_msg::detour( sdk::i_net_channel* ecx, void* edx, sdk::i_net_message& message, bool unk1, bool unk2 )
{
	if ( _ReturnAddress( ) == g_database[ HASH( "8B 45 ? C7 45 ? ? ? ? ? 5F 5E 85 C0 74 ? 6A ? 50 E8 ? ? ? ? 83 C4 ? 8B E5 5D C3" ) ] )
		if ( g_interfaces->client_state->choked_commands > 15 )
			ecx->get_choked_packets( ) -= g_interfaces->client_state->choked_commands % 15;

	return g_send_net_msg->_hook.call( ecx, edx, message, unk1, unk2 );
}
