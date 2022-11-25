#ifndef WEDNESDAY_WTF_C_TF_WEAPON_BASE_HPP
#define WEDNESDAY_WTF_C_TF_WEAPON_BASE_HPP

#include "../enums/weapon_stat_trak_module_type.hpp"
#include "../enums/weapon_strange_type.hpp"
#include "../macros.hpp"
#include "c_base_combat_weapon.hpp"
#include "c_econ_entity.hpp"
#include "c_game_event_listener.hpp"
#include "c_tf_player.hpp"
#include "c_tf_weapon_info.hpp"
#include "i_has_owner.hpp"

namespace sdk
{
	struct c_tf_weapon_base : public c_econ_entity, public c_base_combat_weapon, public i_has_owner, public c_game_event_listener {
	public:
		NETVAR( lowered, bool, "CTFWeaponBase", "m_bLowered" );
		NETVAR( reload_mode, int, "CTFWeaponBase", "m_iReloadMode" );
		NETVAR( reset_parity, bool, "CTFWeaponBase", "m_bResetParity" );
		NETVAR( reloaded_through_anim_event, bool, "CTFWeaponBase", "m_bReloadedThroughAnimEvent" );
		NETVAR( disguise_weapon, bool, "CTFWeaponBase", "m_bDisguiseWeapon" );
		NETVAR( last_crit_check_time, float, "CTFWeaponBase", "m_flLastCritCheckTime" );
		NETVAR( reload_prior_next_fire, float, "CTFWeaponBase", "m_flReloadPriorNextFire" );
		NETVAR( last_fire_time, float, "CTFWeaponBase", "m_flLastFireTime" );
		NETVAR( effect_bar_regen_time, float, "CTFWeaponBase", "m_flEffectBarRegenTime" );
		NETVAR( observed_crit_chance, float, "CTFWeaponBase", "m_flObservedCritChance" );
		NETVAR( energy, float, "CTFWeaponBase", "m_flEnergy" );
		NETVAR( extra_wearable, c_base_handle, "CTFWeaponBase", "m_hExtraWearable" );
		NETVAR( extra_wearable_view_model, c_base_handle, "CTFWeaponBase", "m_hExtraWearableViewModel" );
		NETVAR( being_repurposed_for_taunt, bool, "CTFWeaponBase", "m_bBeingRepurposedForTaunt" );
		NETVAR( kill_combo_class, int, "CTFWeaponBase", "m_nKillComboClass" );
		NETVAR( kill_combo_count, int, "CTFWeaponBase", "m_nKillComboCount" );
		NETVAR( inspect_anim_end_time, float, "CTFWeaponBase", "m_flInspectAnimEndTime" );
		NETVAR( inspect_stage, int, "CTFWeaponBase", "m_nInspectStage" );
		NETVAR( consecutive_shots, int, "CTFWeaponBase", "m_iConsecutiveShots" );

		c_tf_weapon_info& get_weapon_info( )
		{
			auto get_tf_weapon_data_address = g_signatures[ HASH( "0F B7 81 ? ? ? ? 50 E8 ? ? ? ? 83 C4 ? C3" ) ];
			using get_tf_weapon_data_type   = c_tf_weapon_info&( __thiscall* )( void* );

			return get_tf_weapon_data_address.as< get_tf_weapon_data_type >( )( this );
		}

		weapon_data get_weapon_data( )
		{
			return get_weapon_info( ).weapon_data[ 0 ];
		}

		int get_slot( )
		{
			return reinterpret_cast< int( __thiscall* )( void* ) >( g_virtuals->get_virtual_function( this, 329 ) )( this );
		}

		int get_weapon_id( )
		{
			return reinterpret_cast< int( __thiscall* )( void* ) >( g_virtuals->get_virtual_function( this, 379 ) )( this );
		}

		//char* get_name( )
		//{
		//	return reinterpret_cast< char*( __thiscall* )( void* ) >( g_virtuals->get_virtual_function( this, 331 ) )( this );
		//}

		bool can_attack_primary( sdk::c_tf_player* owner );
		bool can_attack_secondary( sdk::c_tf_player* owner );
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_C_TF_WEAPON_BASE_HPP
