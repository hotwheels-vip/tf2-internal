#pragma once

#include "../../features/menu/menu.hpp"
#include "../../helpers/include.hpp"
#include "../hooks.hpp"

class cl_move
{
private:
	hook< void( __cdecl )( float, bool ), void > _hook{ };

public:
	bool charge{ };
	bool shift{ };
	bool choke = true;
	int stored{ };

	int shifted{ };
	int max_shifted{ };

	static void __cdecl detour( float accumulated_extra_samples, bool final_tick );

	void run( )
	{
		// g_input->add_keybind( 'r', [ ]( bool down ) {
		//	if ( down )
		//		charge = true;
		//	else
		//		charge = false;
		// } );

		 //g_input->add_keybind( 'e', [ ]( bool down ) {
			//if ( down )
			//	g_cl_move->shift = true;
			//else
			//	shift = false;
		 //} );

		_hook.create( g_signatures[ HASH( "55 8B EC 83 EC 38 83 3D ? ? ? ? ?" ) ], detour, "cl_move" );
	}

	void end( )
	{
		_hook.remove( );
	}
};

inline cl_move* g_cl_move = new cl_move( );
