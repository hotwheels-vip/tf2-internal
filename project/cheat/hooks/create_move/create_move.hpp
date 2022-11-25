//
// Created by liga on 11/13/2022.
//

#ifndef HOTWHEELS_TF2_INTERNAL_CREATE_MOVE_HPP
#define HOTWHEELS_TF2_INTERNAL_CREATE_MOVE_HPP

#include "../../helpers/include.hpp"
#include "../hooks.hpp"

class create_move
{
private:
	hook< void( __fastcall )( void*, void*, int, float, bool ), void > _hook{ };

public:
	static void __fastcall detour( void* ecx, void* edx, int sequence_number, float input_sample_time, bool active );

	void run( )
	{
		_hook.create( g_virtuals->get_virtual_function( g_interfaces->client, 21 ), detour, "create_move" );
	}

	void end( )
	{
		_hook.remove( );
	}
};

inline create_move* g_create_move = new create_move( );

#endif // HOTWHEELS_TF2_INTERNAL_CREATE_MOVE_HPP
