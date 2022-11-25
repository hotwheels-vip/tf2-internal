#pragma once

#include "../../helpers/include.hpp"
#include "../hooks.hpp"

class frame_stage_notify
{
private:
	hook< void( __fastcall )( void*, void*, sdk::client_frame_stage ), void > _hook{ };

public:
	static void __fastcall detour( void* ecx, void* edx, sdk::client_frame_stage stage );

	void run( )
	{
		_hook.create( g_virtuals->get_virtual_function( g_interfaces->client, 35 ), detour, "frame_stage_notify" );
	}

	void end( )
	{
		_hook.remove( );
	}
};

inline frame_stage_notify* g_frame_stage_notify = new frame_stage_notify( );