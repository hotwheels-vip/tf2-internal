#include "aimbot.hpp"

#include "../../hooks/cl_move/cl_move.hpp"
#include "../lagcomp/lagcomp.hpp"

// #include <imgui/imgui.h>

bool should_run_aimbot( )
{
	return g_entity_list->weapon->can_attack_primary( g_entity_list->local ) || g_cl_move->shifted;
}

weapon_info aimbot::get_weapon_info( )
{
	switch ( g_entity_list->weapon->get_client_class( )->class_id ) {
	case sdk::class_ids::ctf_rocket_launcher: {
		static auto flip_viewmodel = g_interfaces->cvar->find_var( "cl_flipviewmodels" );

		sdk::vector forward{ }, right{ }, up{ };

		math::angle_to_vector( g_entity_list->cmd->view_angles, &forward, &right, &up );

		const sdk::vector offset = forward * 23.5f + right * 12.f + up * -3.f;

		return { 1100.f, offset };
	}
	case sdk::class_ids::ctf_rocket_launcher_direct_hit: {
		static auto flip_viewmodel = g_interfaces->cvar->find_var( "cl_flipviewmodels" );

		sdk::vector forward{ }, right{ }, up{ };

		math::angle_to_vector( g_entity_list->cmd->view_angles, &forward, &right, &up );

		const sdk::vector offset = forward * 23.5f + right * 12.f + up * -3.f;

		return { 1980.f, offset };
	}
	case sdk::class_ids::ctf_compound_bow: {
		static auto flip_viewmodel = g_interfaces->cvar->find_var( "cl_flipviewmodels" );

		sdk::vector forward{ }, right{ }, up{ };

		math::angle_to_vector( g_entity_list->cmd->view_angles, &forward, &right, &up );

		const sdk::vector offset = forward * 23.5f + right * -8.f + up * -3.f;

		const auto weapon = reinterpret_cast< sdk::c_tf_pipebomb_launcher* >( g_entity_list->weapon );
		const auto charge = g_interfaces->globals->cur_time - weapon->charge_begin_time( );

		return { math::remap_val_clamped( charge, 0.f, 1.f, 1800.f, 2600.f ), offset, true, math::remap_val_clamped( charge, 0.f, 1.f, 0.5f, 0.1f ),
			     true };
	}
	default:
		return { 0.f, {} };
	}

	return { };
}

sdk::c_tf_player* closest_player( float max_fov )
{
	float fov                 = max_fov;
	sdk::c_tf_player* closest = nullptr;

	for ( const auto player : g_entity_list->enemy ) {
		if ( !player )
			continue;

		auto view_angles    = math::vector_to_angle( player->get_hitbox_position( sdk::hitbox_pelvis ) - g_entity_list->local->eye_position( ) );
		const auto temp_fov = math::calculate_angle_fov( g_entity_list->cmd->view_angles, view_angles );

		if ( temp_fov <= fov ) {
			fov     = temp_fov;
			closest = player;
		}
	}

	return closest;
}

sdk::vector closest_hitbox( sdk::c_tf_player* player, int hitboxes )
{
	float current_fov = 360.f;
	sdk::vector current{ };

	const auto max_allocation = static_cast< int >( 1.f / g_interfaces->globals->interval_per_tick );

	if ( const auto record_list = g_lagcomp->records[ player->entindex( ) ] ) {
		for ( int i = 0; i < max_allocation; i++ ) {
			auto record = record_list[ i ];

			if ( !record.valid )
				continue;

			for ( int i = 0; i < sdk::hitbox_max; i++ ) {
				if ( !( hitboxes & 1 << i ) )
					continue;

				const auto position = player->get_hitbox_position( i, record.matrix );

				if ( !g_entity_list->local->could_hit( position ) )
					continue;

				auto view_angles = math::vector_to_angle( position - g_entity_list->local->eye_position( ) );
				const auto fov   = math::calculate_angle_fov( g_entity_list->cmd->view_angles, view_angles );

				if ( fov <= current_fov ) {
					current_fov = fov;
					current     = position;

					g_lagcomp->run( record );
				}
			}
		}
	}

	return current;
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

	CONFIG( aimbot_silent_enabled, bool );
	CONFIG( aimbot_silent_fov, float );
	CONFIG( aimbot_silent_hitboxes, int );

	CONFIG( aimbot_projectile_enabled, bool );
	CONFIG( aimbot_projectile_invisible, bool );

	if ( *aimbot_mouse_enabled ) {
		const auto target = closest_player( *aimbot_mouse_fov );

		if ( !target )
			return;

		const auto target_hitbox = closest_hitbox( target, *aimbot_mouse_hitboxes );

		if ( target_hitbox.length( ) == 0 )
			return;

		sdk::qangle local_angles{ };

		g_interfaces->engine_client->get_view_angles( local_angles );

		const auto view_angles       = math::vector_to_angle( target_hitbox - g_entity_list->local->eye_position( ) );
		auto fov_distance            = view_angles - local_angles;
		const auto distance          = fov_distance.normalize( ).length( );
		const int curve_index        = 49 * ( -( std::clamp( distance / *aimbot_mouse_fov, 0.f, 1.f ) ) + 1.f );
		const float distance_percent = g_menu->mouse_curve[ curve_index ].y * *aimbot_mouse_smoothing;
		auto smoothed                = local_angles + ( fov_distance * distance_percent );
		auto normal                  = smoothed.normalize( );

		g_interfaces->engine_client->set_view_angles( normal );
	}

	if ( *aimbot_silent_enabled ) {
		const auto target = closest_player( *aimbot_silent_fov );

		if ( !target )
			return;

		const auto weapon_info = get_weapon_info( );

		if ( weapon_info.next_tick && g_entity_list->cmd->buttons & sdk::in_attack )
			projectile_next_holding_tick = true;

		if ( weapon_info.speed && *aimbot_projectile_enabled ) {
			if ( g_entity_list->cmd->buttons & sdk::in_attack && should_run_aimbot( ) && !weapon_info.next_tick ) {
				const auto offset = g_entity_list->local->eye_position( ) + weapon_info.offset;

				if ( !g_entity_list->local->can_hit( target->get_abs_origin( ) + best_projectile_position( target, weapon_info.can_headshot ),
				                                     target ) )
					return;

				if ( weapon_info.gravity == 0.f ) {
					const auto position =
						g_prediction->linear( offset, target, best_projectile_position( target ), weapon_info, *aimbot_projectile_invisible );

					const auto view_angles = math::vector_to_angle( position - offset );

					g_entity_list->cmd->view_angles = view_angles;
				} else {
					const auto view_angles = g_prediction->quadratic( offset, target, best_projectile_position( target, weapon_info.can_headshot ),
					                                                  weapon_info, *aimbot_projectile_invisible );

					g_entity_list->cmd->view_angles = view_angles;
				}

				projectile_choke = *aimbot_projectile_invisible && !g_cl_move->shifted;
			} else if ( !( g_entity_list->cmd->buttons & sdk::in_attack ) && projectile_next_holding_tick ) {
				const auto offset = g_entity_list->local->eye_position( ) + weapon_info.offset;

				if ( !g_entity_list->local->can_hit( target->get_abs_origin( ) + best_projectile_position( target, weapon_info.can_headshot ),
				                                     target ) )
					return;

				const auto view_angles = g_prediction->quadratic( offset, target, best_projectile_position( target, weapon_info.can_headshot ),
				                                                  weapon_info, *aimbot_projectile_invisible );

				g_entity_list->cmd->view_angles = view_angles;

				projectile_choke = *aimbot_projectile_invisible && !g_cl_move->shifted;

				projectile_next_holding_tick = false;
			}
		} else {
			if ( g_entity_list->cmd->buttons & sdk::in_attack && should_run_aimbot( ) ) {
				const auto target_hitbox = closest_hitbox( target, *aimbot_silent_hitboxes );

				if ( target_hitbox.length( ) == 0 )
					return;

				const auto view_angles = math::vector_to_angle( target_hitbox - g_entity_list->local->eye_position( ) );

				g_entity_list->cmd->view_angles = view_angles;
			}
		}
	}
}
