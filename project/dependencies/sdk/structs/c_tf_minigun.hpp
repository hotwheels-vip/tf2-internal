#ifndef WEDNESDAY_WTF_C_TF_MINIGUN_HPP
#define WEDNESDAY_WTF_C_TF_MINIGUN_HPP

#include "c_tf_weapon_base.hpp"

namespace sdk
{
	struct c_tf_minigun : public c_tf_weapon_base {
	public:
		NETVAR( weapon_state, int, "CTFMinigun", "m_iWeaponState" );
		NETVAR( crit_shot, bool, "CTFMinigun", "m_bCritShot" );
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_C_TF_MINIGUN_HPP
