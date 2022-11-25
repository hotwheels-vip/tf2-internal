#ifndef WEDNESDAY_WTF_C_BASE_PLAYER_HPP
#define WEDNESDAY_WTF_C_BASE_PLAYER_HPP

#include "../enums/life_state.hpp"
#include "c_base_combat_character.hpp"
#include "c_command_context.hpp"
#include "c_user_cmd.hpp"

namespace sdk
{
	struct c_base_player : public c_base_combat_character {
	public:
		NETVAR( local, void*, "CBasePlayer", "m_Local" );
		NETVAR( area_bits, void*, "CBasePlayer", "m_chAreaBits" );
		NETVAR( area_portal_bits, void*, "CBasePlayer", "m_chAreaPortalBits" );
		NETVAR( hide_hud, int, "CBasePlayer", "m_iHideHUD" );
		NETVAR( fov_rate, float, "CBasePlayer", "m_flFOVRate" );
		NETVAR( ducked, bool, "CBasePlayer", "m_bDucked" );
		NETVAR( ducking, bool, "CBasePlayer", "m_bDucking" );
		NETVAR( in_duck_jump, bool, "CBasePlayer", "m_bInDuckJump" );
		NETVAR( ducktime, float, "CBasePlayer", "m_flDucktime" );
		NETVAR( duck_jump_time, float, "CBasePlayer", "m_flDuckJumpTime" );
		NETVAR( jump_time, float, "CBasePlayer", "m_flJumpTime" );
		NETVAR( fall_velocity, float, "CBasePlayer", "m_flFallVelocity" );
		NETVAR( punch_angle, vector, "CBasePlayer", "m_vecPunchAngle" );
		NETVAR( punch_angle_vel, vector, "CBasePlayer", "m_vecPunchAngleVel" );
		NETVAR( draw_viewmodel, bool, "CBasePlayer", "m_bDrawViewmodel" );
		NETVAR( wearing_suit, bool, "CBasePlayer", "m_bWearingSuit" );
		NETVAR( poisoned, bool, "CBasePlayer", "m_bPoisoned" );
		NETVAR( step_size, float, "CBasePlayer", "m_flStepSize" );
		NETVAR( allow_auto_movement, bool, "CBasePlayer", "m_bAllowAutoMovement" );
		NETVAR( view_offset, vector, "CBasePlayer", "m_vecViewOffset[0]" );
		NETVAR( friction, float, "CBasePlayer", "m_flFriction" );
		NETVAR( ammo, void*, "CBasePlayer", "m_iAmmo" );
		NETVAR( on_target, int, "CBasePlayer", "m_fOnTarget" );
		NETVAR( tick_base, int, "CBasePlayer", "m_nTickBase" );
		NETVAR( next_think_tick, int, "CBasePlayer", "m_nNextThinkTick" );
		NETVAR( last_weapon, c_base_handle, "CBasePlayer", "m_hLastWeapon" );
		NETVAR( ground_entity, c_base_handle, "CBasePlayer", "m_hGroundEntity" );
		NETVAR( velocity, vector, "CBasePlayer", "m_vecVelocity[0]" );
		NETVAR( base_velocity, vector, "CBasePlayer", "m_vecBaseVelocity" );
		NETVAR( constraint_entity, c_base_handle, "CBasePlayer", "m_hConstraintEntity" );
		NETVAR( constraint_center, vector, "CBasePlayer", "m_vecConstraintCenter" );
		NETVAR( constraint_radius, float, "CBasePlayer", "m_flConstraintRadius" );
		NETVAR( constraint_width, float, "CBasePlayer", "m_flConstraintWidth" );
		NETVAR( constraint_speed_factor, float, "CBasePlayer", "m_flConstraintSpeedFactor" );
		NETVAR( death_time, float, "CBasePlayer", "m_flDeathTime" );
		NETVAR( water_level, int, "CBasePlayer", "m_nWaterLevel" );
		NETVAR( lagged_movement_value, float, "CBasePlayer", "m_flLaggedMovementValue" );
		NETVAR( attribute_list, void*, "CBasePlayer", "m_AttributeList" );
		NETVAR( pl, void*, "CBasePlayer", "pl" );
		NETVAR( deadflag, int, "CBasePlayer", "deadflag" );
		NETVAR( fov, int, "CBasePlayer", "m_iFOV" );
		NETVAR( fov_start, int, "CBasePlayer", "m_iFOVStart" );
		NETVAR( fov_time, float, "CBasePlayer", "m_flFOVTime" );
		NETVAR( default_fov, int, "CBasePlayer", "m_iDefaultFOV" );
		NETVAR( zoom_owner, c_base_handle, "CBasePlayer", "m_hZoomOwner" );
		NETVAR( vehicle, c_base_handle, "CBasePlayer", "m_hVehicle" );
		NETVAR( use_entity, c_base_handle, "CBasePlayer", "m_hUseEntity" );
		NETVAR( health, int, "CBasePlayer", "m_iHealth" );
		NETVAR( life_state, sdk::life_state, "CBasePlayer", "m_lifeState" );
		NETVAR( bonus_progress, int, "CBasePlayer", "m_iBonusProgress" );
		NETVAR( bonus_challenge, int, "CBasePlayer", "m_iBonusChallenge" );
		NETVAR( maxspeed, float, "CBasePlayer", "m_flMaxspeed" );
		NETVAR( flags, int, "CBasePlayer", "m_fFlags" );
		NETVAR( observer_mode, int, "CBasePlayer", "m_iObserverMode" );
		NETVAR( observer_target, c_base_handle, "CBasePlayer", "m_hObserverTarget" );
		NETVAR( view_model, c_base_handle, "CBasePlayer", "m_hViewModel[0]" );
		NETVAR( last_place_name, const char*, "CBasePlayer", "m_szLastPlaceName" );
		NETVAR( impulse, int, "CBasePlayer", "m_nImpulse" );
		NETVAR( f_button_last, int, "CBasePlayer", "m_afButtonLast" );
		NETVAR( buttons, int, "CBasePlayer", "m_nButtons" );
		NETVAR( f_button_pressed, int, "CBasePlayer", "m_afButtonPressed" );
		NETVAR( f_button_released, int, "CBasePlayer", "m_afButtonReleased" );

		std::string name( );

		vector get_hitbox_position( const std::uint32_t hitbox_index );

		vector get_hitbox_position( const std::uint32_t hitbox_index, matrix_3x4* matrix );

		bool is_alive( )
		{
			return !deadflag( ) && health( ) > 0;
		}

		c_user_cmd*& current_command( )
		{
			return *reinterpret_cast< sdk::c_user_cmd** >( reinterpret_cast< std::uintptr_t >( this ) + 0x107C );
		}

		vector eye_position( )
		{
			return origin( ) + view_offset( );
		}

		c_command_context* get_command_context( )
		{
			return *reinterpret_cast< c_command_context** >( reinterpret_cast< std::uintptr_t >( this ) + 0x1228 );
		}
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_C_BASE_PLAYER_HPP
