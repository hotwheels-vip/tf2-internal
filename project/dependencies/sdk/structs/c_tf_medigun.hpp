#ifndef WEDNESDAY_WTF_C_TF_MEDIGUN_HPP
#define WEDNESDAY_WTF_C_TF_MEDIGUN_HPP

#include "c_tf_weapon_base.hpp"

namespace sdk
{
	struct c_tf_medigun : public c_tf_weapon_base {
	public:
		NETVAR( healing_target, c_base_handle, "CWeaponMedigun", "m_hHealingTarget" );
		NETVAR( healing, bool, "CWeaponMedigun", "m_bHealing" );
		NETVAR( attacking, bool, "CWeaponMedigun", "m_bAttacking" );
		NETVAR( charge_release, bool, "CWeaponMedigun", "m_bChargeRelease" );
		NETVAR( holstered, bool, "CWeaponMedigun", "m_bHolstered" );
		NETVAR( charge_resist_type, int, "CWeaponMedigun", "m_nChargeResistType" );
		NETVAR( last_healing_target, c_base_handle, "CWeaponMedigun", "m_hLastHealingTarget" );
		NETVAR( charge_level, float, "CWeaponMedigun", "m_flChargeLevel" );
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_C_TF_MEDIGUN_HPP
