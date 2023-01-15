#pragma once

#include "../macros.hpp"

#include "i_client_entity.hpp"
#include "matrix.hpp"
#include "var_mapping.hpp"
#include "vector.hpp"

namespace sdk
{
	struct c_base_handle;

	struct c_base_entity : public i_client_entity {
		NETVAR( anim_time, float, "CBaseEntity", "m_flAnimTime" );
		NETVAR( simulation_time, float, "CBaseEntity", "m_flSimulationTime" );
		NETVAR( interpolation_frame, int, "CBaseEntity", "m_ubInterpolationFrame" );
		NETVAR( origin, vector, "CBaseEntity", "m_vecOrigin" );
		NETVAR( rotation, vector, "CBaseEntity", "m_angRotation" );
		NETVAR( model_index, int, "CBaseEntity", "m_nModelIndex" );
		NETVAR( effects, int, "CBaseEntity", "m_fEffects" );
		NETVAR( render_mode, int, "CBaseEntity", "m_nRenderMode" );
		NETVAR( render_fx, int, "CBaseEntity", "m_nRenderFX" );
		NETVAR( render, int, "CBaseEntity", "m_clrRender" );
		NETVAR( team_num, int, "CBaseEntity", "m_iTeamNum" );
		NETVAR( collision_group, int, "CBaseEntity", "m_CollisionGroup" );
		NETVAR( elasticity, float, "CBaseEntity", "m_flElasticity" );
		NETVAR( shadow_cast_distance, float, "CBaseEntity", "m_flShadowCastDistance" );
		NETVAR( owner_entity, c_base_handle, "CBaseEntity", "m_hOwnerEntity" );
		NETVAR( effect_entity, c_base_handle, "CBaseEntity", "m_hEffectEntity" );
		NETVAR( moveparent, int, "CBaseEntity", "moveparent" );
		NETVAR( parent_attachment, int, "CBaseEntity", "m_iParentAttachment" );
		NETVAR( collision, void*, "CBaseEntity", "m_Collision" );
		NETVAR( mins_pre_scaled, vector, "CBaseEntity", "m_vecMinsPreScaled" );
		NETVAR( maxs_pre_scaled, vector, "CBaseEntity", "m_vecMaxsPreScaled" );
		NETVAR( mins, vector, "CBaseEntity", "m_vecMins" );
		NETVAR( maxs, vector, "CBaseEntity", "m_vecMaxs" );
		NETVAR( solid_type, int, "CBaseEntity", "m_nSolidType" );
		NETVAR( solid_flags, int, "CBaseEntity", "m_usSolidFlags" );
		NETVAR( surround_type, int, "CBaseEntity", "m_nSurroundType" );
		NETVAR( trigger_bloat, int, "CBaseEntity", "m_triggerBloat" );
		NETVAR( uniform_trigger_bloat, bool, "CBaseEntity", "m_bUniformTriggerBloat" );
		NETVAR( specified_surrounding_mins_pre_scaled, vector, "CBaseEntity", "m_vecSpecifiedSurroundingMinsPreScaled" );
		NETVAR( specified_surrounding_maxs_pre_scaled, vector, "CBaseEntity", "m_vecSpecifiedSurroundingMaxsPreScaled" );
		NETVAR( specified_surrounding_mins, vector, "CBaseEntity", "m_vecSpecifiedSurroundingMins" );
		NETVAR( specified_surrounding_maxs, vector, "CBaseEntity", "m_vecSpecifiedSurroundingMaxs" );
		NETVAR( texture_frame_index, int, "CBaseEntity", "m_iTextureFrameIndex" );
		NETVAR( predictable_id, int, "CBaseEntity", "m_PredictableID" );
		NETVAR( is_player_simulated, bool, "CBaseEntity", "m_bIsPlayerSimulated" );
		NETVAR( simulated_every_tick, bool, "CBaseEntity", "m_bSimulatedEveryTick" );
		NETVAR( animated_every_tick, bool, "CBaseEntity", "m_bAnimatedEveryTick" );
		NETVAR( alternate_sorting, bool, "CBaseEntity", "m_bAlternateSorting" );
		NETVAR( model_index_overrides, void*, "CBaseEntity", "m_nModelIndexOverrides" );
		NETVAR( movetype, int, "CBaseEntity", "movetype" );

		sdk::vector get_bone_position( std::uint32_t bone_index )
		{
			if ( sdk::matrix_3x4 matrix[ 128 ]; setup_bones( matrix, 128, 256, 0.f ) ) {
				auto bone_matrix = matrix[ bone_index ];

				return {
					bone_matrix[ 0 ][ 3 ],
					bone_matrix[ 1 ][ 3 ],
					bone_matrix[ 2 ][ 3 ],
				};
			}

			return { };
		};

		sdk::vector get_bone_position( std::uint32_t bone_index, matrix_3x4* matrix )
		{
			auto bone_matrix = matrix[ bone_index ];

			return {
				bone_matrix[ 0 ][ 3 ],
				bone_matrix[ 1 ][ 3 ],
				bone_matrix[ 2 ][ 3 ],
			};
		};

		bool is_player( )
		{
			static auto is_player_address = g_signatures[ HASH( "55 8B EC 56 8B 75 ? 85 F6 74 ? 8B 16 8B CE" ) ].as< std::uintptr_t >( );
			using is_player_type          = void*( __cdecl* )( void* );

			return reinterpret_cast< is_player_type >( is_player_address )( this );
		}

		bool is_enemy( c_base_entity* entity )
		{
			return entity->team_num( ) != team_num( );
		}

		var_mapping* get_var_mapping( )
		{
			return reinterpret_cast< var_mapping* >( reinterpret_cast< std::uintptr_t >( this ) + 0x14 );
		}

		int max_health( );

		matrix_3x4& rgfl_coordinate_frame( );

		void set_abs_origin( sdk::vector& position );

		void invalidate_bone_cache( );

		float get_old_simulation_time( )
		{
			// im doing this from memory so excuse errors also, code is long for readability sake. itll be optimized by compiler

			/* get sim time address */
			const std::uint32_t simulation_time_address = ( std::uint32_t )&simulation_time( );

			/* old sim time is offset + 4, most cheats get the netvar offset but that is gay. */
			float* old_sim_time = ( float* )( simulation_time_address + 0x4 );

			[[unlikely]] if ( !old_sim_time )
				return -1.f;

			/* return actual sim time */
			return *old_sim_time;
		}

		sdk::vector estimate_abs_velocity( )
		{
			sdk::vector buffer;

			static auto estimate_abs_velocity_address = g_signatures[ HASH( "55 8B EC 83 EC ? 56 8B F1 E8 ? ? ? ? 3B F0" ) ].as< std::uintptr_t >( );
			using estimate_abs_velocity_type          = void( __thiscall* )( void*, sdk::vector* );

			reinterpret_cast< estimate_abs_velocity_type >( estimate_abs_velocity_address )( this, &buffer );

			return buffer;
		}
	};
} // namespace sdk
