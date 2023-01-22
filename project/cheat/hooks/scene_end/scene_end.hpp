#pragma once

#include "../hooks.hpp"

#include "../../helpers/include.hpp"

class scene_end
{
private:
	hook< void( __fastcall )( void*, void* ), void > _hook{ };

public:
	static void __fastcall detour( void* ecx, void* edx );

	void run( )
	{
		_hook.create( g_virtuals->get_virtual_function( g_interfaces->render_view, 9 ), detour, "scene_end" );
	}

	void end( )
	{
		_hook.remove( );
	}
};

inline scene_end* g_scene_end = new scene_end( );
