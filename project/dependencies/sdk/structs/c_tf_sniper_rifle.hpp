#pragma once

#include "c_tf_weapon_base.hpp"

namespace sdk
{
	struct c_tf_sniper_rifle : public c_tf_weapon_base {
	public:
		NETVAR( charged_damage, float, "CTFSniperRifle", "m_flChargedDamage" );
	};
} // namespace sdk
