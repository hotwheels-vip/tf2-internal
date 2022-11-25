#pragma once

#include "../../helpers/include.hpp"
#include "../hooks.hpp"

class get_time
{
private:
	hook< float( __fastcall )( void*, void* ), float > _hook{ };

public:
	static float __fastcall detour( void* ecx, void* edx );

	void run( )
	{
		_hook.create( g_signatures[ HASH( "55 8B EC 51 80 B9 14 4B 00 00" ) ], detour, "get_time" );
	}

	void end( )
	{
		_hook.remove( );
	}
};

inline get_time* g_get_time = new get_time( );