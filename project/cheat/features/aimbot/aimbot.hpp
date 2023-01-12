#pragma once

#include "../../helpers/include.hpp"
#include "../prediction/prediction.hpp"

#include <easing/easing.h>
#include <sdk/include.hpp>

class aimbot
{
public:
	bool projectile_choke{ };
	bool projectile_next_holding_tick{ };

	void run( );

	weapon_info get_weapon_info( );

	sdk::hitboxes closest_hitbox( sdk::c_tf_player* player, int hitboxes );
	sdk::c_tf_player* closest_player( float max_fov );
};

inline aimbot* g_aimbot = new aimbot( );
