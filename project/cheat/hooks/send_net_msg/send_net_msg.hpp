#pragma once

#include "../../features/menu/menu.hpp"
#include "../../helpers/include.hpp"
#include "../hooks.hpp"

class send_net_msg
{
private:
	hook< bool( __fastcall )( void*, void*, sdk::i_net_message&, bool, bool ), bool > _hook{ };

public:
	static bool __fastcall detour( void* ecx, void* edx, sdk::i_net_message& message, bool unk1, bool unk2 );

	void run( )
	{
		_hook.create( g_signatures[ HASH( "55 8B EC 57 8B F9 8D 8F ? ? ? ? E8 ? ? ? ? 85 C0 75 ? B0 ? 5F 5D C2 ? ? 53" ) ], detour, "send_net_msg" );
	}

	void end( )
	{
		_hook.remove( );
	}
};

inline send_net_msg* g_send_net_msg = new send_net_msg( );
