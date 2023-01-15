#pragma once

#include "c_tf_weapon_base.hpp"

namespace sdk
{
	struct c_tf_knife : public c_tf_weapon_base {
	public:
		NETVAR( ready_to_backstab, bool, "CTFKnife", "m_bReadyToBackstab" );
		NETVAR( knife_exists, bool, "CTFKnife", "m_bKnifeExists" );
		NETVAR( knife_regenerate_duration, float, "CTFKnife", "m_flKnifeRegenerateDuration" );
		NETVAR( knife_melt_timestamp, float, "CTFKnife", "m_flKnifeMeltTimestamp" );
	};
} // namespace sdk
