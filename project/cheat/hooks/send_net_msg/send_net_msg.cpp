#include <algorithm>
#include <iostream>

#include "send_net_msg.hpp"

bool __fastcall send_net_msg::detour( sdk::i_net_channel* ecx, void* edx, sdk::i_net_message& message, bool unk1, bool unk2 )
{
	if ( _ReturnAddress( ) == g_signatures[ HASH( "8B 45 ? C7 45 ? ? ? ? ? 5F 5E 85 C0 74 ? 6A ? 50 E8 ? ? ? ? 83 C4 ? 8B E5 5D C3" ) ] ) {
		if ( const auto extra_commands = g_signatures[ HASH( "C7 05 ? ? ? ? ? ? ? ? C7 05 ? ? ? ? ? ? ? ? DD 1D" ) ].add( 0x2 ).get( 2 ).as< int >( );
		     extra_commands - std::clamp( extra_commands, 0, 16 ) > 0 )
			ecx->get_choked_packets( ) -= extra_commands - std::clamp( extra_commands, 0, 16 );
	}

	return g_send_net_msg->_hook.call( ecx, edx, message, unk1, unk2 );
}
