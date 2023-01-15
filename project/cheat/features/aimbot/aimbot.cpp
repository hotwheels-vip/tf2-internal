#include "aimbot.hpp"

#include "../../hooks/cl_move/cl_move.hpp"

#include <imgui/imgui.h>

weapon_info aimbot::get_weapon_info( )
{
	switch ( g_entity_list->weapon->get_client_class( )->class_id ) {
	case sdk::e_class_ids::ctf_rocket_launcher: {
		static auto flip_viewmodel = g_interfaces->cvar->find_var( "cl_flipviewmodels" );

		sdk::vector forward{ }, right{ }, up{ };

		math::angle_to_vector( g_entity_list->cmd->view_angles, &forward, &right, &up );

		sdk::vector offset = forward * 23.5f + right * 12.f + up * -3.f;

		return { 1100.f, offset };
	}
	case sdk::e_class_ids::ctf_rocket_launcher_direct_hit: {
		static auto flip_viewmodel = g_interfaces->cvar->find_var( "cl_flipviewmodels" );

		sdk::vector forward{ }, right{ }, up{ };

		math::angle_to_vector( g_entity_list->cmd->view_angles, &forward, &right, &up );

		sdk::vector offset = forward * 23.5f + right * 12.f + up * -3.f;

		return { 1980.f, offset };
	}
	case sdk::e_class_ids::ctf_compound_bow: {
		static auto flip_viewmodel = g_interfaces->cvar->find_var( "cl_flipviewmodels" );

		sdk::vector forward{ }, right{ }, up{ };

		math::angle_to_vector( g_entity_list->cmd->view_angles, &forward, &right, &up );

		sdk::vector offset = forward * 23.5f + right * -8.f + up * -3.f;

		auto weapon = ( sdk::c_tf_pipebomb_launcher* )g_entity_list->weapon;
		auto charge = g_interfaces->globals->cur_time - weapon->charge_begin_time( );

		return { math::remap_val_clamped( charge, 0.f, 1.f, 1800.f, 2600.f ), offset, true, math::remap_val_clamped( charge, 0.f, 1.f, 0.5f, 0.1f ),
			     true };
	}
	default:
		return { 0.f, {} };
	}

	return { };
}

sdk::hitboxes aimbot::closest_hitbox( sdk::c_tf_player* player, int hitboxes )
{
	float current_fov            = 360.f;
	sdk::hitboxes current_hitbox = sdk::hitboxes::hitbox_head;

	for ( int i = 0; i < sdk::hitbox_max; i++ ) {
		if ( !( hitboxes & ( 1 << i ) ) )
			continue;

		auto view_angles = math::vector_to_angle( player->get_hitbox_position( i ) - g_entity_list->local->eye_position( ) );
		auto fov         = math::calculate_angle_fov( g_entity_list->cmd->view_angles, view_angles );

		if ( fov <= current_fov ) {
			current_fov    = fov;
			current_hitbox = static_cast< sdk::hitboxes >( i );
		}
	}

	return current_hitbox;
}

sdk::c_tf_player* aimbot::closest_player( float max_fov )
{
	float fov                 = max_fov;
	sdk::c_tf_player* closest = nullptr;

	for ( auto player : g_entity_list->enemy ) {
		if ( !player )
			continue;

		if ( !g_entity_list->local->can_hit( player->get_hitbox_position( sdk::hitbox_pelvis ), player ) )
			continue;

		auto view_angles = math::vector_to_angle( player->get_hitbox_position( sdk::hitbox_pelvis ) - g_entity_list->local->eye_position( ) );
		auto temp_fov    = math::calculate_angle_fov( g_entity_list->cmd->view_angles, view_angles );

		if ( temp_fov <= fov ) {
			fov     = temp_fov;
			closest = player;
		}
	}

	return closest;
}

bool should_run_aimbot( )
{
	return g_entity_list->weapon->can_attack_primary( g_entity_list->local ) || g_cl_move->shifted;
}

sdk::vector best_projectile_position( sdk::c_tf_player* target, bool can_headshot = false )
{
	CONFIG( aimbot_projectile_feet, bool );

	sdk::vector ideal_foot_offset{ 0, 0, 2 };
	sdk::vector head_offset{ 0, 0, ( target->get_hitbox_position( sdk::hitbox_head ) - target->get_abs_origin( ) ).z };
	sdk::vector pelvis_offset{ 0, 0, ( target->get_hitbox_position( sdk::hitbox_pelvis ) - target->get_abs_origin( ) ).z };

	if ( can_headshot )
		return head_offset;

	return *aimbot_projectile_feet ? ideal_foot_offset : pelvis_offset;
}

void aimbot::run( )
{
	if ( !g_entity_list->cmd )
		return;

	if ( !g_entity_list->weapon )
		return;

	CONFIG( aimbot_mouse_enabled, bool );
	CONFIG( aimbot_mouse_fov, float );
	CONFIG( aimbot_mouse_smoothing, float );
	CONFIG( aimbot_mouse_hitboxes, int );
	CONFIG( aimbot_mouse_curve_a, ImVec2 );
	CONFIG( aimbot_mouse_curve_b, ImVec2 );

	CONFIG( aimbot_silent_enabled, bool );
	CONFIG( aimbot_silent_fov, float );
	CONFIG( aimbot_silent_hitboxes, int );

	CONFIG( aimbot_projectile_enabled, bool );
	CONFIG( aimbot_projectile_invisible, bool );
	CONFIG( aimbot_projectile_feet, bool );

	if ( *aimbot_mouse_enabled ) {
		auto target = closest_player( *aimbot_mouse_fov );

		if ( !target )
			return;

		auto target_hitbox = closest_hitbox( target, *aimbot_mouse_hitboxes );

		sdk::qangle local_angles{ };

		g_interfaces->engine_client->get_view_angles( local_angles );

		sdk::vector position{ };

		auto weapon_info = get_weapon_info( );

		position = target->get_hitbox_position( target_hitbox );

		auto view_angles       = math::vector_to_angle( position - g_entity_list->local->eye_position( ) );
		auto fov_distance      = view_angles - local_angles;
		auto distance          = fov_distance.normalize( ).length( );
		int curve_index        = 49 * ( -( std::clamp( distance / *aimbot_mouse_fov, 0.f, 1.f ) ) + 1.f );
		float distance_percent = g_menu->mouse_curve[ curve_index ].y * *aimbot_mouse_smoothing;
		auto smoothed          = local_angles + ( fov_distance * distance_percent );
		auto normal            = smoothed.normalize( );

		g_interfaces->engine_client->set_view_angles( normal );
	}

	if ( *aimbot_silent_enabled ) {
		auto target = closest_player( *aimbot_silent_fov );

		if ( !target )
			return;

		auto weapon_info = get_weapon_info( );

		if ( weapon_info.next_tick && ( g_entity_list->cmd->buttons & sdk::in_attack ) )
			projectile_next_holding_tick = true;

		if ( weapon_info.speed && *aimbot_projectile_enabled ) {
			if ( g_entity_list->cmd->buttons & sdk::in_attack && should_run_aimbot( ) && !weapon_info.next_tick ) {
				auto offset = g_entity_list->local->eye_position( ) + weapon_info.offset;

				if ( weapon_info.gravity == 0.f ) {
					auto position =
						g_prediction->linear( offset, target, best_projectile_position( target ), weapon_info, *aimbot_projectile_invisible );

					auto view_angles = math::vector_to_angle( position - offset );

					g_entity_list->cmd->view_angles = view_angles;
				} else {
					auto view_angles = g_prediction->quadratic( offset, target, best_projectile_position( target, weapon_info.can_headshot ),
					                                            weapon_info, *aimbot_projectile_invisible );

					g_entity_list->cmd->view_angles = view_angles;
				}

				projectile_choke = *aimbot_projectile_invisible && !g_cl_move->shifted;
			} else if ( !( g_entity_list->cmd->buttons & sdk::in_attack ) && projectile_next_holding_tick ) {
				auto offset = g_entity_list->local->eye_position( ) + weapon_info.offset;

				auto view_angles = g_prediction->quadratic( offset, target, best_projectile_position( target, weapon_info.can_headshot ), weapon_info,
				                                            *aimbot_projectile_invisible );

				g_entity_list->cmd->view_angles = view_angles;

				projectile_choke = *aimbot_projectile_invisible && !g_cl_move->shifted;

				projectile_next_holding_tick = false;
			}
		} else {
			if ( g_entity_list->cmd->buttons & sdk::in_attack && should_run_aimbot( ) ) {
				auto target_hitbox = closest_hitbox( target, *aimbot_silent_hitboxes );
				auto view_angles   = math::vector_to_angle( target->get_hitbox_position( target_hitbox ) - g_entity_list->local->eye_position( ) );

				g_entity_list->cmd->view_angles = view_angles;
			}
		}
	}
}
