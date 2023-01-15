#pragma once

#include "c_tf_weapon_base.hpp"

namespace sdk
{
	struct c_tf_pipebomb_launcher : public c_tf_weapon_base {
	public:
		NETVAR( pipebomb_count, int, "CTFPipebombLauncher", "m_iPipebombCount" );
		NETVAR( charge_begin_time, float, "CTFPipebombLauncher", "m_flChargeBeginTime" );
	};
} // namespace sdk
