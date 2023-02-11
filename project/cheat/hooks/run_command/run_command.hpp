#pragma once

#include "../hooks.hpp"

#include "../../features/menu/menu.hpp"
#include "../../helpers/include.hpp"

class run_command
{
private:
	hook< void( __fastcall )( void*, void*, sdk::c_base_player*, sdk::c_user_cmd*, void* ), void > _hook{ };

public:
	static void __fastcall detour( void* ecx, void* edx, sdk::c_base_player* player, sdk::c_user_cmd* command, void* move_helper );

	void run( )
	{
		_hook.create( g_database[ HASH( "55 8B EC 51 53 56 8B F1 57 89 75 ? E8 ? ? ? ? 8B 7D" ) ], detour, "run_command" );
	}

	void end( )
	{
		_hook.remove( );
	}
};

inline run_command* g_run_command = new run_command( );
