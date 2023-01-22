#pragma once

#include "../hooks.hpp"

#include "../../helpers/include.hpp"

class packet_start
{
private:
	hook< int( __fastcall )( void*, void*, int, int ), int > _hook{ };

public:
	static int __fastcall detour( void* ecx, void* edx, int incoming_sequence, int outgoing_acknowledged );

	void run( )
	{
		_hook.create( g_signatures[ HASH( "55 8B EC 8B 45 ? 89 81 ? ? ? ? 8B 45 ? 89 81 ? ? ? ? 5D C2 ? ? CC CC CC CC CC CC CC 55 8B EC 56" ) ],
		              detour, "packet_start" );
	}

	void end( )
	{
		_hook.remove( );
	}
};

inline packet_start* g_packet_start = new packet_start( );
