#pragma once

#include "../hooks.hpp"

#include "../../helpers/include.hpp"

class is_playing_back
{
private:
	hook< bool( __fastcall )( void*, void* ), bool > _hook{ };

public:
	static bool __fastcall detour( void* ecx, void* edx );

	void run( )
	{
		_hook.create( g_signatures[ HASH( "8A 81 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC 80 B9" ) ], detour, "is_playing_back" );
	}

	void end( )
	{
		_hook.remove( );
	}
};

inline is_playing_back* g_is_playing_back = new is_playing_back( );
