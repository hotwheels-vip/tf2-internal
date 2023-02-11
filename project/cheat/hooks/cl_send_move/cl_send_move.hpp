#pragma once

#include "../hooks.hpp"

#include "../../helpers/include.hpp"

class cl_send_move
{
private:
	hook< void( __cdecl )( ), void > _hook{ };

public:
	static void __cdecl detour( );

	void run( )
	{
		_hook.create( g_database[ HASH( "55 8B EC 81 EC ? ? ? ? A1 ? ? ? ? 8D 4D" ) ], detour, "cl_send_move" );
	}

	void end( )
	{
		_hook.remove( );
	}
};

inline cl_send_move* g_cl_send_move = new cl_send_move( );
