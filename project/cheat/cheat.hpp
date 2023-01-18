#pragma once

#include <windows.h>

#include "helpers/include.hpp"
#include "hooks/hooks.hpp"

class cheat
{
public:
	HINSTANCE instance{ };

	static void run( );
	static void end( );
};

inline cheat* g_cheat = new cheat( );
