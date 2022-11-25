#ifndef WEDNESDAY_WTF_C_BASE_COMBAT_WEAPON_HPP
#define WEDNESDAY_WTF_C_BASE_COMBAT_WEAPON_HPP

#include "c_base_animating.hpp"

namespace sdk
{
	struct c_base_combat_weapon : public c_base_animating {
	public:
		NETVAR( clip1, int, "CBaseCombatWeapon", "m_iClip1" );
		NETVAR( clip2, int, "CBaseCombatWeapon", "m_iClip2" );
		NETVAR( primary_ammo_type, int, "CBaseCombatWeapon", "m_iPrimaryAmmoType" );
		NETVAR( secondary_ammo_type, int, "CBaseCombatWeapon", "m_iSecondaryAmmoType" );
		NETVAR( view_model_index, int, "CBaseCombatWeapon", "m_nViewModelIndex" );
		NETVAR( flip_view_model, bool, "CBaseCombatWeapon", "m_bFlipViewModel" );
		NETVAR( next_primary_attack, float, "CBaseCombatWeapon", "m_flNextPrimaryAttack" );
		NETVAR( next_secondary_attack, float, "CBaseCombatWeapon", "m_flNextSecondaryAttack" );
		NETVAR( next_think_tick, int, "CBaseCombatWeapon", "m_nNextThinkTick" );
		NETVAR( time_weapon_idle, float, "CBaseCombatWeapon", "m_flTimeWeaponIdle" );
		NETVAR( view_model_index_index, int, "CBaseCombatWeapon", "m_iViewModelIndex" );
		NETVAR( world_model_index, int, "CBaseCombatWeapon", "m_iWorldModelIndex" );
		NETVAR( state, int, "CBaseCombatWeapon", "m_iState" );
		NETVAR( owner, c_base_handle, "CBaseCombatWeapon", "m_hOwner" );

		int mag( )
		{
			return *reinterpret_cast< int* >( reinterpret_cast< std::uintptr_t >( this ) + 0x433 );
		}
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_C_BASE_COMBAT_WEAPON_HPP
