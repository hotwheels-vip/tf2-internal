#pragma once

#include "../hooks.hpp"

#include "../../helpers/include.hpp"

class draw_model_execute
{
private:
	hook< void( __fastcall )( void*, void*, void*, sdk::model_render_info&, sdk::matrix_3x4* ), void > _hook{ };

public:
	static void __fastcall detour( void* ecx, void* edx, void* state, sdk::model_render_info& info, sdk::matrix_3x4* matrix );

	void run( )
	{
		_hook.create( g_virtuals->get_virtual_function( g_interfaces->model_render, 19 ), detour, "draw_model_execute" );
	}

	void end( )
	{
		_hook.remove( );
	}
};

inline draw_model_execute* g_draw_model_execute = new draw_model_execute( );
