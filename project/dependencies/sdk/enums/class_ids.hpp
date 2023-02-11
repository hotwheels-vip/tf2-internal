#pragma once

namespace sdk
{
	enum class class_ids : int {
		cai_base_npc,
		c_base_animating,
		c_base_animating_overlay,
		c_base_attributable_item,
		c_base_combat_character,
		c_base_combat_weapon,
		c_base_door,
		c_base_entity,
		c_base_flex,
		c_base_grenade,
		c_base_object,
		c_base_object_upgrade,
		c_base_particle_entity,
		c_base_player,
		c_base_projectile,
		c_base_prop_door,
		c_base_team_objective_resource,
		c_base_temp_entity,
		c_base_view_model,
		c_beam,
		c_bone_follower,
		c_bonus_duck_pickup,
		c_bonus_pack,
		c_bonus_round_logic,
		c_breakable_prop,
		c_breakable_surface,
		c_capture_flag,
		c_capture_flag_return_icon,
		c_capture_zone,
		c_color_correction,
		c_color_correction_volume,
		c_currency_pack,
		c_dynamic_light,
		c_dynamic_prop,
		c_econ_entity,
		c_econ_wearable,
		c_embers,
		c_entity_dissolve,
		c_entity_flame,
		c_entity_particle_trail,
		c_env_detail_controller,
		c_env_particle_script,
		c_env_projected_texture,
		c_env_quadratic_beam,
		c_env_screen_effect,
		c_env_screen_overlay,
		c_env_tonemap_controller,
		c_env_wind,
		c_eyeball_boss,
		c_fire_smoke,
		c_fire_trail,
		c_fish,
		c_fog_controller,
		c_func_dust,
		c_func_lod,
		c_func_area_portal_window,
		c_func_conveyor,
		c_func_force_field,
		c_func_ladder,
		c_func_monitor,
		c_func_occluder,
		c_func_passtime_goal,
		c_func_reflective_glass,
		c_func_respawn_room,
		c_func_respawn_room_visualizer,
		c_func_rotating,
		c_func_smoke_volume,
		c_func_track_train,
		c_game_rules_proxy,
		c_halloween_gift_pickup,
		c_halloween_pickup,
		c_halloween_soul_pack,
		c_handle_test,
		c_headless_hatman,
		c_hightower_teleport_vortex,
		c_info_ladder_dismount,
		c_info_lighting_relative,
		c_info_overlay_accessor,
		c_laser_dot,
		c_light_glow,
		c_mann_vs_machine_stats,
		c_material_modify_control,
		c_merasmus,
		c_merasmus_dancer,
		c_monster_resource,
		c_object_cart_dispenser,
		c_object_dispenser,
		c_object_sapper,
		c_object_sentrygun,
		c_object_teleporter,
		c_particle_fire,
		c_particle_performance_monitor,
		c_particle_system,
		c_passtime_ball,
		c_passtime_gun,
		c_phys_box,
		c_phys_box_multiplayer,
		c_physics_prop,
		c_physics_prop_multiplayer,
		c_phys_magnet,
		c_plasma,
		c_player_destruction_dispenser,
		c_player_resource,
		c_point_camera,
		c_point_commentary_node,
		c_point_world_text,
		c_pose_controller,
		c_precipitation,
		c_prop_vehicle_driveable,
		c_ragdoll_manager,
		c_ragdoll_prop,
		c_ragdoll_prop_attached,
		c_robot_dispenser,
		c_rope_keyframe,
		c_scene_entity,
		c_shadow_control,
		c_slideshow_display,
		c_smoke_stack,
		c_sniper_dot,
		c_spotlight_end,
		c_sprite,
		c_sprite_oriented,
		c_sprite_trail,
		c_steam_jet,
		c_sun,
		c_team,
		c_teamplay_round_based_rules_proxy,
		c_team_round_timer,
		c_team_train_watcher,
		cte_armor_ricochet,
		cte_base_beam,
		cte_beam_ent_point,
		cte_beam_ents,
		cte_beam_follow,
		cte_beam_laser,
		cte_beam_points,
		cte_beam_ring,
		cte_beam_ring_point,
		cte_beam_spline,
		cte_blood_sprite,
		cte_blood_stream,
		cte_break_model,
		ctebsp_decal,
		cte_bubbles,
		cte_bubble_trail,
		cte_client_projectile,
		cte_decal,
		cte_dust,
		cte_dynamic_light,
		cte_effect_dispatch,
		cte_energy_splash,
		cte_explosion,
		cte_fire_bullets,
		cte_fizz,
		cte_footprint_decal,
		cte_gauss_explosion,
		cte_glow_sprite,
		cte_impact,
		cte_kill_player_attachments,
		cte_large_funnel,
		c_teleport_vortex,
		cte_metal_sparks,
		cte_muzzle_flash,
		cte_particle_system,
		cte_physics_prop,
		cte_player_anim_event,
		cte_player_decal,
		cte_projected_decal,
		cte_shatter_surface,
		cte_show_line,
		c_tesla,
		cte_smoke,
		cte_sparks,
		cte_sprite,
		cte_sprite_spray,
		c_test_proxy_toggle_networkable,
		c_test_traceline,
		ctetf_blood,
		ctetf_explosion,
		ctetf_particle_effect,
		cte_world_decal,
		ctf_ammo_pack,
		ctf_ball_ornament,
		ctf_base_boss,
		ctf_base_projectile,
		ctf_base_rocket,
		ctf_bat,
		ctf_bat_fish,
		ctf_bat_giftwrap,
		ctf_bat_wood,
		ctf_bonesaw,
		ctf_bot_hint_engineer_nest,
		ctf_bottle,
		ctf_breakable_melee,
		ctf_breakable_sign,
		ctf_buff_item,
		ctf_cannon,
		ctf_charged_smg,
		ctf_cleaver,
		ctf_club,
		ctf_compound_bow,
		ctf_crossbow,
		ctfdrg_pomson,
		ctf_dropped_weapon,
		ctf_fire_axe,
		ctf_fists,
		ctf_flame_manager,
		ctf_flame_rocket,
		ctf_flame_thrower,
		ctf_flare_gun,
		ctf_flare_gun_revenge,
		ctf_game_rules_proxy,
		ctf_gas_manager,
		ctf_generic_bomb,
		ctf_glow,
		ctf_grappling_hook,
		ctf_grenade_launcher,
		ctf_grenade_pipebomb_projectile,
		ctf_halloween_minigame,
		ctf_halloween_minigame_falling_platforms,
		ctf_hell_zap,
		ctf_item,
		ctf_jar,
		ctf_jar_gas,
		ctf_jar_milk,
		ctf_katana,
		ctf_knife,
		ctf_laser_pointer,
		ctf_lunch_box,
		ctf_lunch_box_drink,
		ctf_mechanical_arm,
		ctf_medigun_shield,
		ctf_mini_game,
		ctf_minigame_logic,
		ctf_minigun,
		ctf_objective_resource,
		ctf_parachute,
		ctf_parachute_primary,
		ctf_parachute_secondary,
		ctf_particle_cannon,
		ctf_passtime_logic,
		ctfpep_brawler_blaster,
		ctf_pipebomb_launcher,
		ctf_pistol,
		ctf_pistol_scout,
		ctf_pistol_scout_primary,
		ctf_pistol_scout_secondary,
		ctf_player,
		ctf_player_destruction_logic,
		ctf_player_resource,
		ctf_point_manager,
		ctf_powerup_bottle,
		ctf_projectile_arrow,
		ctf_projectile_ball_of_fire,
		ctf_projectile_cleaver,
		ctf_projectile_energy_ball,
		ctf_projectile_energy_ring,
		ctf_projectile_flare,
		ctf_projectile_grappling_hook,
		ctf_projectile_healing_bolt,
		ctf_projectile_jar,
		ctf_projectile_jar_gas,
		ctf_projectile_jar_milk,
		ctf_projectile_mechanical_arm_orb,
		ctf_projectile_rocket,
		ctf_projectile_sentry_rocket,
		ctf_projectile_spell_bats,
		ctf_projectile_spell_fireball,
		ctf_projectile_spell_kart_bats,
		ctf_projectile_spell_kart_orb,
		ctf_projectile_spell_lightning_orb,
		ctf_projectile_spell_meteor_shower,
		ctf_projectile_spell_mirv,
		ctf_projectile_spell_pumpkin,
		ctf_projectile_spell_spawn_boss,
		ctf_projectile_spell_spawn_horde,
		ctf_projectile_spell_spawn_zombie,
		ctf_projectile_spell_transpose_teleport,
		ctf_projectile_throwable,
		ctf_projectile_throwable_bread_monster,
		ctf_projectile_throwable_brick,
		ctf_projectile_throwable_repel,
		ctf_pumpkin_bomb,
		ctf_ragdoll,
		ctf_raygun,
		ctf_revive_marker,
		ctf_revolver,
		ctf_robot_arm,
		ctf_robot_destruction_robot,
		ctf_robot_destruction_robot_group,
		ctf_robot_destruction_robot_spawn,
		ctf_robot_destruction_logic,
		ctf_rocket_launcher,
		ctf_rocket_launcher_air_strike,
		ctf_rocket_launcher_direct_hit,
		ctf_rocket_launcher_mortar,
		ctf_rocket_pack,
		ctf_scatter_gun,
		ctf_shotgun,
		ctf_shotgun_hwg,
		ctf_shotgun_pyro,
		ctf_shotgun_revenge,
		ctf_shotgun_soldier,
		ctf_shotgun_building_rescue,
		ctf_shovel,
		ctf_slap,
		ctfsmg,
		ctf_sniper_rifle,
		ctf_sniper_rifle_classic,
		ctf_sniper_rifle_decap,
		ctf_soda_popper,
		ctf_spell_book,
		ctf_stick_bomb,
		ctf_stun_ball,
		ctf_sword,
		ctf_syringe_gun,
		ctf_tank_boss,
		ctf_taunt_prop,
		ctf_team,
		ctf_throwable,
		ctf_view_model,
		ctf_weapon_base,
		ctf_weapon_base_grenade_proj,
		ctf_weapon_base_gun,
		ctf_weapon_base_melee,
		ctf_weapon_base_merasmus_grenade,
		ctf_weapon_builder,
		ctf_weapon_flame_ball,
		ctf_weapon_invis,
		ctf_weapon_pda,
		ctf_weapon_pda_engineer_build,
		ctf_weapon_pda_engineer_destroy,
		ctf_weapon_pda_spy,
		ctf_weapon_pda_expansion_dispenser,
		ctf_weapon_pda_expansion_teleporter,
		ctf_weapon_sapper,
		ctf_wearable,
		ctf_wearable_campaign_item,
		ctf_wearable_demo_shield,
		ctf_wearable_item,
		ctf_wearable_levelable_item,
		ctf_wearable_razorback,
		ctf_wearable_robot_arm,
		ctf_wearable_vm,
		ctf_wrench,
		cv_gui_screen,
		c_vote_controller,
		c_water_bullet,
		c_water_lod_control,
		c_weapon_ifm_base,
		c_weapon_ifm_base_camera,
		c_weapon_ifm_steady_cam,
		c_weapon_medigun,
		c_world,
		c_zombie,
		dust_trail,
		movie_explosion,
		next_bot_combat_character,
		particle_smoke_grenade,
		rocket_trail,
		smoke_trail,
		spore_explosion,
		spore_trail
	};
} // namespace sdk
