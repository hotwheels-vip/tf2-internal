#pragma once

#include "c_tf_weapon_base.hpp"

namespace sdk
{
	struct c_tf_minigun : public c_tf_weapon_base {
	public:
		NETVAR( weapon_state, int, "CTFMinigun", "m_iWeaponState" );
		NETVAR( crit_shot, bool, "CTFMinigun", "m_bCritShot" );
	};
} // namespace sdk
