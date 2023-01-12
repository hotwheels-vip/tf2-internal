#pragma once

#include "../hooks.hpp"

#include "../../features/menu/menu.hpp"
#include "../../helpers/include.hpp"

class process_tick
{
private:
	hook< bool( __fastcall )( void*, void*, void* ), bool > _hook{ };

public:
	static bool __fastcall detour( void* ecx, void* edx, void* msg );

	void run( )
	{
		_hook.create( g_signatures[ HASH( "55 8B EC 8B 45 ? 56 57 8B F9 83 EC" ) ], detour, "process_tick" );
	}

	void end( )
	{
		_hook.remove( );
	}
};

inline process_tick* g_process_tick = new process_tick( );
