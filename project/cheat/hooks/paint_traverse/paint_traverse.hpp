//
// Created by liga on 11/12/2022.
//

#ifndef HOTWHEELS_TF2_INTERNAL_PAINT_TRAVERSE_HPP
#define HOTWHEELS_TF2_INTERNAL_PAINT_TRAVERSE_HPP

#include "../../features/menu/menu.hpp"
#include "../../helpers/include.hpp"
#include "../hooks.hpp"

class paint_traverse
{
private:
	hook< void( __fastcall )( void*, void*, unsigned int, bool, bool ), void > _hook{ };

public:
	static void __fastcall detour( void* ecx, void* edx, unsigned int panel, bool force_repaint, bool allow_force );

	void run( )
	{
		_hook.create( g_virtuals->get_virtual_function( g_interfaces->panel, 41 ), detour, "paint_traverse" );
	}

	void end( )
	{
		_hook.remove( );
	}
};

inline paint_traverse* g_paint_traverse = new paint_traverse( );

#endif // HOTWHEELS_TF2_INTERNAL_PAINT_TRAVERSE_HPP
