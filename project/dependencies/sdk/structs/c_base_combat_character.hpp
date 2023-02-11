#pragma once

#include "c_base_flex.hpp"

namespace sdk
{
	struct c_base_combat_character : public c_base_flex {
	public:
		NETVAR( next_attack, float, "CBaseCombatCharacter", "m_flNextAttack" );
		NETVAR( active_weapon, c_base_handle, "CBaseCombatCharacter", "m_hActiveWeapon" );
		NETVAR( my_weapons, c_base_handle, "CBaseCombatCharacter", "m_hMyWeapons" );
		NETVAR( glow_enabled, bool, "CBaseCombatCharacter", "m_bGlowEnabled" );
		NETVAR( old_glow_enabled, bool, "CBaseCombatCharacter", "m_bOldGlowEnabled" );
	};
} // namespace sdk
