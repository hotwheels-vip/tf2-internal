#pragma once

namespace sdk
{
	enum tf_cond {
		tf_cond_slowed                 = ( 1 << 0 ),
		tf_cond_zoomed                 = ( 1 << 1 ),
		tf_cond_disguising             = ( 1 << 2 ),
		tf_cond_disguised              = ( 1 << 3 ),
		tf_cond_cloaked                = ( 1 << 4 ),
		tf_cond_ubercharged            = ( 1 << 5 ),
		tf_cond_teleported_glow        = ( 1 << 6 ),
		tf_cond_taunting               = ( 1 << 7 ),
		tf_cond_ubercharge_fading      = ( 1 << 8 ),
		tf_cond_cloak_flicker          = ( 1 << 9 ),
		tf_cond_teleporting            = ( 1 << 10 ),
		tf_cond_kritzkrieged           = ( 1 << 11 ),
		tf_cond_tmp_damage_bonus       = ( 1 << 12 ),
		tf_cond_dead_ringered          = ( 1 << 13 ),
		tf_cond_bonked                 = ( 1 << 14 ),
		tf_cond_stunned                = ( 1 << 15 ),
		tf_cond_buffed                 = ( 1 << 16 ),
		tf_cond_charging               = ( 1 << 17 ),
		tf_cond_demo_buff              = ( 1 << 18 ),
		tf_cond_crit_cola              = ( 1 << 19 ),
		tf_cond_in_heal_radius         = ( 1 << 20 ),
		tf_cond_healing                = ( 1 << 21 ),
		tf_cond_on_fire                = ( 1 << 22 ),
		tf_cond_overhealed             = ( 1 << 23 ),
		tf_cond_jarated                = ( 1 << 24 ),
		tf_cond_bleeding               = ( 1 << 25 ),
		tf_cond_defense_buffed         = ( 1 << 26 ),
		tf_cond_milked                 = ( 1 << 27 ),
		tf_cond_mega_heal              = ( 1 << 28 ),
		tf_cond_regen_buffed           = ( 1 << 29 ),
		tf_cond_marked_for_death       = ( 1 << 30 ),
		tf_cond_no_healing_damage_buff = ( 1 << 31 ),

		tf_cond_ex_speed_buff_ally            = ( 1 << 0 ),
		tf_cond_ex_halloween_crit_candy       = ( 1 << 1 ),
		tf_cond_ex_crit_canteen               = ( 1 << 2 ),
		tf_cond_ex_crit_demo_charge           = ( 1 << 3 ),
		tf_cond_ex_crit_hype                  = ( 1 << 4 ),
		tf_cond_ex_crit_on_first_blood        = ( 1 << 5 ),
		tf_cond_ex_crit_on_win                = ( 1 << 6 ),
		tf_cond_ex_crit_on_flag_capture       = ( 1 << 7 ),
		tf_cond_ex_crit_on_kill               = ( 1 << 8 ),
		tf_cond_ex_restrict_to_melee          = ( 1 << 9 ),
		tf_cond_ex_defense_buff_no_crit_block = ( 1 << 10 ),
		tf_cond_ex_reprogrammed               = ( 1 << 11 ),
		tf_cond_ex_pyro_crits                 = ( 1 << 12 ),
		tf_cond_ex_pyro_heal                  = ( 1 << 13 ),
		tf_cond_ex_focus_buff                 = ( 1 << 14 ),
		tf_cond_ex_disguised_removed          = ( 1 << 15 ),
		tf_cond_ex_marked_for_death_silent    = ( 1 << 16 ),
		tf_cond_ex_disguised_as_dispenser     = ( 1 << 17 ),
		tf_cond_ex_in_kart                    = ( 1 << 18 ),
		tf_cond_ex_ubercharged_hidden         = ( 1 << 19 ),
		tf_cond_ex_ubercharged_canteen        = ( 1 << 20 ),
		tf_cond_ex_halloween_bomb_head        = ( 1 << 21 ),
		tf_cond_ex_halloween_thriller         = ( 1 << 22 ),
		tf_cond_ex_bullet_charge              = ( 1 << 26 ),
		tf_cond_ex_explosive_charge           = ( 1 << 27 ),
		tf_cond_ex_fire_charge                = ( 1 << 28 ),
		tf_cond_ex_bullet_resistance          = ( 1 << 29 ),
		tf_cond_ex_explosive_resistance       = ( 1 << 30 ),
		tf_cond_ex_fire_resistance            = ( 1 << 31 ),
		tf_cond_ex_phlog_uber                 = 1052672,

		tf_cond_ex2_stealthed                = ( 1 << 0 ),
		tf_cond_ex2_medigun_debuff           = ( 1 << 1 ),
		tf_cond_ex2_stealthed_user_buff_fade = ( 1 << 2 ),
		tf_cond_ex2_bullet_immune            = ( 1 << 3 ),
		tf_cond_ex2_blast_immune             = ( 1 << 4 ),
		tf_cond_ex2_fire_immune              = ( 1 << 5 ),
		tf_cond_ex2_prevent_death            = ( 1 << 6 ),
		tf_cond_ex2_mvm_bot_radiowave        = ( 1 << 7 ),
		tf_cond_ex2_halloween_speed_boost    = ( 1 << 8 ),
		tf_cond_ex2_halloween_quick_heal     = ( 1 << 9 ),
		tf_cond_ex2_halloween_giant          = ( 1 << 10 ),
		tf_cond_ex2_halloween_tiny           = ( 1 << 11 ),
		tf_cond_ex2_halloween_in_hell        = ( 1 << 12 ),
		tf_cond_ex2_halloween_ghost_mode     = ( 1 << 13 ),
		tf_cond_ex2_parachute                = ( 1 << 16 ),
		tf_cond_ex2_blast_jumping            = ( 1 << 17 ),

		tf_cond_mini_crits       = ( tf_cond_buffed | tf_cond_crit_cola ),
		tf_cond_ignore_states    = ( tf_cond_ubercharged | tf_cond_bonked ),
		tf_cond_ex_ignore_states = ( tf_cond_ex_pyro_heal )
	};
} // namespace sdk
