#pragma once

#include "../hooks.hpp"

#include "../../features/menu/menu.hpp"
#include "../../features/prediction/prediction.hpp"
#include "../../helpers/include.hpp"

class item_post_frame
{
private:
	hook< void( __fastcall )( void*, void* ), void > _hook{ };

public:
	static void __fastcall detour( void* ecx, void* edx );

	void run( )
	{
		_hook.create( g_signatures[ HASH( "55 8B EC 83 EC ? 56 57 8B F9 8B 37" ) ], detour, "item_post_frame" );
	}

	void end( )
	{
		_hook.remove( );
	}
};

inline item_post_frame* g_item_post_frame = new item_post_frame( );
