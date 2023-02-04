#pragma once

#include "c_base_player.hpp"

namespace sdk
{
	struct c_tf_player : public c_base_player {
	public:
		NETVAR( save_me_parity, bool, "CTFPlayer", "m_bSaveMeParity" );
		NETVAR( is_mini_boss, bool, "CTFPlayer", "m_bIsMiniBoss" );
		NETVAR( is_a_bot, bool, "CTFPlayer", "m_bIsABot" );
		NETVAR( bot_skill, int, "CTFPlayer", "m_nBotSkill" );
		NETVAR( water_level, int, "CTFPlayer", "m_nWaterLevel" );
		NETVAR( ragdoll, c_base_handle, "CTFPlayer", "m_hRagdoll" );
		NETVAR( player_class, void*, "CTFPlayer", "m_PlayerClass" );
		NETVAR( class_id, int, "CTFPlayer", "m_iClass" );
		NETVAR( sz_class_icon, const char*, "CTFPlayer", "m_iszClassIcon" );
		NETVAR( sz_custom_model, const char*, "CTFPlayer", "m_iszCustomModel" );
		NETVAR( custom_model_offset, vector, "CTFPlayer", "m_vecCustomModelOffset" );
		NETVAR( custom_model_rotation, vector, "CTFPlayer", "m_angCustomModelRotation" );
		NETVAR( custom_model_rotates, bool, "CTFPlayer", "m_bCustomModelRotates" );
		NETVAR( custom_model_rotation_set, bool, "CTFPlayer", "m_bCustomModelRotationSet" );
		NETVAR( custom_model_visible_to_self, bool, "CTFPlayer", "m_bCustomModelVisibleToSelf" );
		NETVAR( use_class_animations, bool, "CTFPlayer", "m_bUseClassAnimations" );
		NETVAR( class_model_parity, int, "CTFPlayer", "m_iClassModelParity" );
		NETVAR( shared, void*, "CTFPlayer", "m_Shared" );
		NETVAR( player_cond, int, "CTFPlayer", "m_nPlayerCond" );
		NETVAR( jumping, bool, "CTFPlayer", "m_bJumping" );
		NETVAR( num_healers, int, "CTFPlayer", "m_nNumHealers" );
		NETVAR( crit_mult, int, "CTFPlayer", "m_iCritMult" );
		NETVAR( air_dash, int, "CTFPlayer", "m_iAirDash" );
		NETVAR( air_ducked, int, "CTFPlayer", "m_nAirDucked" );
		NETVAR( duck_timer, float, "CTFPlayer", "m_flDuckTimer" );
		NETVAR( player_state, int, "CTFPlayer", "m_nPlayerState" );
		NETVAR( desired_player_class, int, "CTFPlayer", "m_iDesiredPlayerClass" );
		NETVAR( movement_stun_time, float, "CTFPlayer", "m_flMovementStunTime" );
		NETVAR( movement_stun_amount, int, "CTFPlayer", "m_iMovementStunAmount" );
		NETVAR( movement_stun_parity, int, "CTFPlayer", "m_iMovementStunParity" );
		NETVAR( stunner, c_base_handle, "CTFPlayer", "m_hStunner" );
		NETVAR( stun_flags, int, "CTFPlayer", "m_iStunFlags" );
		NETVAR( arena_num_changes, int, "CTFPlayer", "m_nArenaNumChanges" );
		NETVAR( arena_first_blood_boost, bool, "CTFPlayer", "m_bArenaFirstBloodBoost" );
		NETVAR( weapon_knockback_id, int, "CTFPlayer", "m_iWeaponKnockbackID" );
		NETVAR( loadout_unavailable, bool, "CTFPlayer", "m_bLoadoutUnavailable" );
		NETVAR( item_find_bonus, int, "CTFPlayer", "m_iItemFindBonus" );
		NETVAR( shield_equipped, bool, "CTFPlayer", "m_bShieldEquipped" );
		NETVAR( parachute_equipped, bool, "CTFPlayer", "m_bParachuteEquipped" );
		NETVAR( next_melee_crit, int, "CTFPlayer", "m_iNextMeleeCrit" );
		NETVAR( decapitations, int, "CTFPlayer", "m_iDecapitations" );
		NETVAR( revenge_crits, int, "CTFPlayer", "m_iRevengeCrits" );
		NETVAR( disguise_body, int, "CTFPlayer", "m_iDisguiseBody" );
		NETVAR( carried_object, c_base_handle, "CTFPlayer", "m_hCarriedObject" );
		NETVAR( carrying_object, bool, "CTFPlayer", "m_bCarryingObject" );
		NETVAR( next_noise_maker_time, float, "CTFPlayer", "m_flNextNoiseMakerTime" );
		NETVAR( spawn_room_touch_count, int, "CTFPlayer", "m_iSpawnRoomTouchCount" );
		NETVAR( kill_count_since_last_deploy, int, "CTFPlayer", "m_iKillCountSinceLastDeploy" );
		NETVAR( first_primary_attack, float, "CTFPlayer", "m_flFirstPrimaryAttack" );
		NETVAR( energy_drink_meter, float, "CTFPlayer", "m_flEnergyDrinkMeter" );
		NETVAR( hype_meter, float, "CTFPlayer", "m_flHypeMeter" );
		NETVAR( charge_meter, float, "CTFPlayer", "m_flChargeMeter" );
		NETVAR( invis_change_complete_time, float, "CTFPlayer", "m_flInvisChangeCompleteTime" );
		NETVAR( disguise_team, int, "CTFPlayer", "m_nDisguiseTeam" );
		NETVAR( disguise_class, int, "CTFPlayer", "m_nDisguiseClass" );
		NETVAR( disguise_skin_override, int, "CTFPlayer", "m_nDisguiseSkinOverride" );
		NETVAR( mask_class, int, "CTFPlayer", "m_nMaskClass" );
		NETVAR( disguise_target_index, int, "CTFPlayer", "m_iDisguiseTargetIndex" );
		NETVAR( disguise_health, int, "CTFPlayer", "m_iDisguiseHealth" );
		NETVAR( feign_death_ready, bool, "CTFPlayer", "m_bFeignDeathReady" );
		NETVAR( disguise_weapon, c_base_handle, "CTFPlayer", "m_hDisguiseWeapon" );
		NETVAR( team_teleporter_used, int, "CTFPlayer", "m_nTeamTeleporterUsed" );
		NETVAR( cloak_meter, float, "CTFPlayer", "m_flCloakMeter" );
		NETVAR( spy_tranq_buff_duration, float, "CTFPlayer", "m_flSpyTranqBuffDuration" );
		NETVAR( desired_disguise_team, int, "CTFPlayer", "m_nDesiredDisguiseTeam" );
		NETVAR( desired_disguise_class, int, "CTFPlayer", "m_nDesiredDisguiseClass" );
		NETVAR( stealth_no_attack_expire, float, "CTFPlayer", "m_flStealthNoAttackExpire" );
		NETVAR( stealth_next_change_time, float, "CTFPlayer", "m_flStealthNextChangeTime" );
		NETVAR( last_disguised_as_own_team, bool, "CTFPlayer", "m_bLastDisguisedAsOwnTeam" );
		NETVAR( rage_meter, float, "CTFPlayer", "m_flRageMeter" );
		NETVAR( rage_draining, bool, "CTFPlayer", "m_bRageDraining" );
		NETVAR( next_rage_earn_time, float, "CTFPlayer", "m_flNextRageEarnTime" );
		NETVAR( in_upgrade_zone, bool, "CTFPlayer", "m_bInUpgradeZone" );
		NETVAR( item_charge_meter, void*, "CTFPlayer", "m_flItemChargeMeter" );
		NETVAR( player_dominated, void*, "CTFPlayer", "m_bPlayerDominated" );
		NETVAR( player_dominating_me, void*, "CTFPlayer", "m_bPlayerDominatingMe" );
		NETVAR( score_data, void*, "CTFPlayer", "m_ScoreData" );
		NETVAR( captures, int, "CTFPlayer", "m_iCaptures" );
		NETVAR( defenses, int, "CTFPlayer", "m_iDefenses" );
		NETVAR( kills, int, "CTFPlayer", "m_iKills" );
		NETVAR( deaths, int, "CTFPlayer", "m_iDeaths" );
		NETVAR( suicides, int, "CTFPlayer", "m_iSuicides" );
		NETVAR( dominations, int, "CTFPlayer", "m_iDominations" );
		NETVAR( revenge, int, "CTFPlayer", "m_iRevenge" );
		NETVAR( buildings_built, int, "CTFPlayer", "m_iBuildingsBuilt" );
		NETVAR( buildings_destroyed, int, "CTFPlayer", "m_iBuildingsDestroyed" );
		NETVAR( headshots, int, "CTFPlayer", "m_iHeadshots" );
		NETVAR( backstabs, int, "CTFPlayer", "m_iBackstabs" );
		NETVAR( heal_points, int, "CTFPlayer", "m_iHealPoints" );
		NETVAR( invulns, int, "CTFPlayer", "m_iInvulns" );
		NETVAR( teleports, int, "CTFPlayer", "m_iTeleports" );
		NETVAR( resupply_points, int, "CTFPlayer", "m_iResupplyPoints" );
		NETVAR( kill_assists, int, "CTFPlayer", "m_iKillAssists" );
		NETVAR( points, int, "CTFPlayer", "m_iPoints" );
		NETVAR( bonus_points, int, "CTFPlayer", "m_iBonusPoints" );
		NETVAR( damage_done, int, "CTFPlayer", "m_iDamageDone" );
		NETVAR( crits, int, "CTFPlayer", "m_iCrits" );
		NETVAR( round_score_data, void*, "CTFPlayer", "m_RoundScoreData" );
		NETVAR( condition_list, void*, "CTFPlayer", "m_ConditionList" );
		NETVAR( _condition_bits, int, "CTFPlayer", "_condition_bits" );
		NETVAR( taunt_index, int, "CTFPlayer", "m_iTauntIndex" );
		NETVAR( taunt_concept, int, "CTFPlayer", "m_iTauntConcept" );
		NETVAR( player_cond_ex, int, "CTFPlayer", "m_nPlayerCondEx" );
		NETVAR( stun_index, int, "CTFPlayer", "m_iStunIndex" );
		NETVAR( halloween_bomb_head_stage, int, "CTFPlayer", "m_nHalloweenBombHeadStage" );
		NETVAR( player_cond_ex2, int, "CTFPlayer", "m_nPlayerCondEx2" );
		NETVAR( player_cond_ex3, int, "CTFPlayer", "m_nPlayerCondEx3" );
		NETVAR( streaks, void*, "CTFPlayer", "m_nStreaks" );
		NETVAR( un_taunt_source_item_id_low, int, "CTFPlayer", "m_unTauntSourceItemID_Low" );
		NETVAR( un_taunt_source_item_id_high, int, "CTFPlayer", "m_unTauntSourceItemID_High" );
		NETVAR( rune_charge, float, "CTFPlayer", "m_flRuneCharge" );
		NETVAR( has_passtime_ball, bool, "CTFPlayer", "m_bHasPasstimeBall" );
		NETVAR( is_targeted_for_passtime_pass, bool, "CTFPlayer", "m_bIsTargetedForPasstimePass" );
		NETVAR( passtime_pass_target, c_base_handle, "CTFPlayer", "m_hPasstimePassTarget" );
		NETVAR( ask_for_ball_time, float, "CTFPlayer", "m_askForBallTime" );
		NETVAR( king_rune_buff_active, bool, "CTFPlayer", "m_bKingRuneBuffActive" );
		NETVAR( player_cond_ex4, int, "CTFPlayer", "m_nPlayerCondEx4" );
		NETVAR( holster_anim_time, float, "CTFPlayer", "m_flHolsterAnimTime" );
		NETVAR( switch_to, c_base_handle, "CTFPlayer", "m_hSwitchTo" );
		NETVAR( item, c_base_handle, "CTFPlayer", "m_hItem" );
		NETVAR( is_coaching, bool, "CTFPlayer", "m_bIsCoaching" );
		NETVAR( coach, c_base_handle, "CTFPlayer", "m_hCoach" );
		NETVAR( student, c_base_handle, "CTFPlayer", "m_hStudent" );
		NETVAR( currency, int, "CTFPlayer", "m_nCurrency" );
		NETVAR( experience_level, int, "CTFPlayer", "m_nExperienceLevel" );
		NETVAR( experience_level_progress, int, "CTFPlayer", "m_nExperienceLevelProgress" );
		NETVAR( match_safe_to_leave, bool, "CTFPlayer", "m_bMatchSafeToLeave" );
		NETVAR( origin, vector, "CTFPlayer", "m_vecOrigin" );
		NETVAR( eye_angles_x, float, "CTFPlayer", "m_angEyeAngles[0]" );
		NETVAR( eye_angles_y, float, "CTFPlayer", "m_angEyeAngles[1]" );
		NETVAR( allow_move_during_taunt, bool, "CTFPlayer", "m_bAllowMoveDuringTaunt" );
		NETVAR( is_ready_to_high_five, bool, "CTFPlayer", "m_bIsReadyToHighFive" );
		NETVAR( high_five_partner, c_base_handle, "CTFPlayer", "m_hHighFivePartner" );
		NETVAR( force_taunt_cam, int, "CTFPlayer", "m_nForceTauntCam" );
		NETVAR( taunt_yaw, float, "CTFPlayer", "m_flTauntYaw" );
		NETVAR( active_taunt_slot, int, "CTFPlayer", "m_nActiveTauntSlot" );
		NETVAR( taunt_item_def_index, int, "CTFPlayer", "m_iTauntItemDefIndex" );
		NETVAR( current_taunt_move_speed, float, "CTFPlayer", "m_flCurrentTauntMoveSpeed" );
		NETVAR( vehicle_reverse_time, float, "CTFPlayer", "m_flVehicleReverseTime" );
		NETVAR( mv_m_last_damage_time, float, "CTFPlayer", "m_flMvMLastDamageTime" );
		NETVAR( last_damage_time, float, "CTFPlayer", "m_flLastDamageTime" );
		NETVAR( in_power_play, bool, "CTFPlayer", "m_bInPowerPlay" );
		NETVAR( spawn_counter, int, "CTFPlayer", "m_iSpawnCounter" );
		NETVAR( arena_spectator, bool, "CTFPlayer", "m_bArenaSpectator" );
		NETVAR( attribute_manager, void*, "CTFPlayer", "m_AttributeManager" );
		NETVAR( outer, c_base_handle, "CTFPlayer", "m_hOuter" );
		NETVAR( provider_type, int, "CTFPlayer", "m_ProviderType" );
		NETVAR( reapply_provision_parity, int, "CTFPlayer", "m_iReapplyProvisionParity" );
		NETVAR( head_scale, float, "CTFPlayer", "m_flHeadScale" );
		NETVAR( torso_scale, float, "CTFPlayer", "m_flTorsoScale" );
		NETVAR( hand_scale, float, "CTFPlayer", "m_flHandScale" );
		NETVAR( use_boss_health_bar, bool, "CTFPlayer", "m_bUseBossHealthBar" );
		NETVAR( using_vr_headset, bool, "CTFPlayer", "m_bUsingVRHeadset" );
		NETVAR( forced_skin, bool, "CTFPlayer", "m_bForcedSkin" );
		NETVAR( forced_skin_index, int, "CTFPlayer", "m_nForcedSkin" );
		NETVAR( glow_enabled_alternative, bool, "CTFPlayer", "m_bGlowEnabled" );
		NETVAR( active_wpn_clip, int, "CTFPlayer", "m_nActiveWpnClip" );
		NETVAR( kart_next_available_boost, float, "CTFPlayer", "m_flKartNextAvailableBoost" );
		NETVAR( kart_health, int, "CTFPlayer", "m_iKartHealth" );
		NETVAR( kart_state, int, "CTFPlayer", "m_iKartState" );
		NETVAR( grappling_hook_target, c_base_handle, "CTFPlayer", "m_hGrapplingHookTarget" );
		NETVAR( secondary_last_weapon, c_base_handle, "CTFPlayer", "m_hSecondaryLastWeapon" );
		NETVAR( using_action_slot, bool, "CTFPlayer", "m_bUsingActionSlot" );
		NETVAR( inspect_time, float, "CTFPlayer", "m_flInspectTime" );
		NETVAR( helpme_button_press_time, float, "CTFPlayer", "m_flHelpmeButtonPressTime" );
		NETVAR( campaign_medals, int, "CTFPlayer", "m_iCampaignMedals" );
		NETVAR( player_skin_override, int, "CTFPlayer", "m_iPlayerSkinOverride" );
		NETVAR( viewing_cyoapda, bool, "CTFPlayer", "m_bViewingCYOAPDA" );

		const char* class_name( );

		c_base_animating* get_server_base_animating( ); // im sad to say credit for this goes to fedorahack
		void draw_client_hitbox( const float& duration = 0.f );

		bool can_hit( const vector pos, c_base_entity* ent = nullptr );
		bool could_hit( vector pos );
		void post_think( );
		void pre_think( );
	};
} // namespace sdk
