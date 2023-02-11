#pragma once

#include "../../helpers/include.hpp"

class movement
{
public:
	void run( );

	void move_fix( sdk::qangle angle );
	void auto_stop( );
};

inline movement* g_movement = new movement( );
