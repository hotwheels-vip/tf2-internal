#pragma once

#include "c_base_animating_overlay.hpp"

namespace sdk
{
	struct c_base_flex : public c_base_animating_overlay {
	public:
		NETVAR( flex_weight, void*, "CBaseFlex", "m_flexWeight" );
		NETVAR( blink_toggle, int, "CBaseFlex", "m_blinktoggle" );
		NETVAR( view_target, vector, "CBaseFlex", "m_viewtarget" );
	};
} // namespace sdk
