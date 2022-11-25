#pragma once

#include "../../helpers/include.hpp"

class tickbase
{
public:
	void* clock_drift{ };
	int last_tick{ };

	void run( );
};

inline tickbase* g_tickbase = new tickbase( );