#ifndef WEDNESDAY_WTF_C_BASE_ANIMATING_HPP
#define WEDNESDAY_WTF_C_BASE_ANIMATING_HPP

#include "c_base_entity.hpp"

namespace sdk
{
	struct c_base_animating : public c_base_entity {
	public:
		NETVAR( sequence, int, "CBaseAnimating", "m_nSequence" );
		NETVAR( force_bone, int, "CBaseAnimating", "m_nForceBone" );
		NETVAR( force, vector, "CBaseAnimating", "m_vecForce" );
		NETVAR( skin, int, "CBaseAnimating", "m_nSkin" );
		NETVAR( body, int, "CBaseAnimating", "m_nBody" );
		NETVAR( hitbox_set, int, "CBaseAnimating", "m_nHitboxSet" );
		NETVAR( model_scale, float, "CBaseAnimating", "m_flModelScale" );
		NETVAR( model_width_scale, float, "CBaseAnimating", "m_flModelWidthScale" );
		NETVAR( pose_parameter, float, "CBaseAnimating", "m_flPoseParameter" );
		NETVAR( playback_rate, float, "CBaseAnimating", "m_flPlaybackRate" );
		NETVAR( encoded_controller, void*, "CBaseAnimating", "m_flEncodedController" );
		NETVAR( client_side_animation, bool, "CBaseAnimating", "m_bClientSideAnimation" );
		NETVAR( client_side_frame_reset, bool, "CBaseAnimating", "m_bClientSideFrameReset" );
		NETVAR( new_sequence_parity, int, "CBaseAnimating", "m_nNewSequenceParity" );
		NETVAR( reset_events_parity, int, "CBaseAnimating", "m_nResetEventsParity" );
		NETVAR( muzzle_flash_parity, int, "CBaseAnimating", "m_nMuzzleFlashParity" );
		NETVAR( lighting_origin, c_base_handle, "CBaseAnimating", "m_hLightingOrigin" );
		NETVAR( lighting_origin_relative, c_base_handle, "CBaseAnimating", "m_hLightingOriginRelative" );
		NETVAR( cycle, float, "CBaseAnimating", "m_flCycle" );
		NETVAR( fade_min_dist, float, "CBaseAnimating", "m_fadeMinDist" );
		NETVAR( fade_max_dist, float, "CBaseAnimating", "m_fadeMaxDist" );
		NETVAR( fade_scale, float, "CBaseAnimating", "m_flFadeScale" );
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_C_BASE_ANIMATING_HPP
