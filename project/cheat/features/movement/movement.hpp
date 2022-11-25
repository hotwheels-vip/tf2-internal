#pragma once

#include "../../helpers/include.hpp"

class movement
{
public:
	void run( );

	void move_fix( sdk::c_user_cmd* cmd, sdk::qangle angle );
};

inline movement* g_movement = new movement( );