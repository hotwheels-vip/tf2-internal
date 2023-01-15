#pragma once

#include "../../helpers/include.hpp"
#include "../prediction/prediction.hpp"

#include <sdk/include.hpp>

class aimbot
{
public:
	bool projectile_choke{ };
	bool projectile_next_holding_tick{ };

	void run( );

	weapon_info get_weapon_info( );
};

inline aimbot* g_aimbot = new aimbot( );
