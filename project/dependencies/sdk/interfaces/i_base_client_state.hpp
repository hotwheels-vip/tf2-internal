#pragma once

#include "../../helpers/memory/memory.hpp"
#include "i_net_channel.hpp"

namespace sdk
{
	struct i_base_client_state {
		static int delta_tick( )
		{
			return g_signatures[ HASH( "8B 15 ? ? ? ? 85 D2 8B 35" ) ].add( 0x2 ).get( 2 ).as< int >( );
		}
		static int last_command_ack( )
		{
			return g_signatures[ HASH( "FF 35 ? ? ? ? 8B 3E" ) ].add( 0x2 ).get( 2 ).as< int >( );
		}
		static int last_outgoing_command( )
		{
			return g_signatures[ HASH( "A1 ? ? ? ? 03 05" ) ].add( 0x2 ).get( 2 ).as< int >( );
		}
		static int choked_commands( )
		{
			return g_signatures[ HASH( "03 05 ? ? ? ? 8B 15" ) ].add( 0x2 ).get( 2 ).as< int >( );
		}
		static int relative_choked_commands( )
		{
			return choked_commands( ) - last_command_ack( );
		}
	};
} // namespace sdk
