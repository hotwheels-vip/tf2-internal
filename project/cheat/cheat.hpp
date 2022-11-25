//
// Created by liga on 11/13/2022.
//

#ifndef HOTWHEELS_TF2_INTERNAL_CHEAT_HPP
#define HOTWHEELS_TF2_INTERNAL_CHEAT_HPP

#include <windows.h>

#include "hooks/hooks.hpp"
#include "helpers/include.hpp"

class cheat
{
public:
	HINSTANCE instance{ };

	void run( );
	void end( );
};

inline cheat* g_cheat = new cheat( );

#endif // HOTWHEELS_TF2_INTERNAL_CHEAT_HPP
