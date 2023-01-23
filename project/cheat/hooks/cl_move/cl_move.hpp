#pragma once

#include "../hooks.hpp"

#include "../../features/menu/menu.hpp"
#include "../../helpers/include.hpp"

class cl_move
{
private:
	hook< void( __cdecl )( float, bool ), void > _hook{ };

public:
	bool force_charge{ };
	bool force_shift{ };
	bool force_update{ };

	bool choke = true;

	int stored{ };

	int shifted{ };
	int max_shifted{ };

	bool shifting{ };
	bool charging{ };

	static void __cdecl detour( float accumulated_extra_samples, bool final_tick );

	void run( )
	{
		g_input->add_keybind( 'R', [ & ]( bool down ) {
			if ( down )
				force_charge = true;
			else
				force_charge = false;
		} );

		g_input->add_keybind( 'E', [ & ]( bool down ) {
			if ( down )
				force_shift = true;
			else
				force_shift = false;
		} );

		_hook.create( g_database[ HASH( "55 8B EC 83 EC 38 83 3D ? ? ? ? ?" ) ], detour, "cl_move" );
	}

	void end( )
	{
		_hook.remove( );
	}
};

inline cl_move* g_cl_move = new cl_move( );
