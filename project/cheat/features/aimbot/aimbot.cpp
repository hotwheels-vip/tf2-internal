//
// Created by liga on 11/15/2022.
//

#include "aimbot.hpp"
#include "../../hooks/cl_move/cl_move.hpp"

weapon_info aimbot::get_weapon_info( )
{
	switch ( g_entity_list->weapon->get_client_class( )->class_id ) {
	case sdk::e_class_ids::ctf_rocket_launcher: {
		sdk::vector right;
		sdk::qangle eye_angles{ g_entity_list->local->eye_angles_x( ), g_entity_list->local->eye_angles_y( ), 0 };
		sdk::qangle punch_angle{ g_entity_list->local->punch_angle( ).x, g_entity_list->local->punch_angle( ).y,
			                     g_entity_list->local->punch_angle( ).z };

		math::angle_to_vector( eye_angles + punch_angle, NULL, &right, NULL );

		return { 1100.f, sdk::vector( 0, 0, -8 ) + right * 12 };
	}
	case sdk::e_class_ids::ctf_rocket_launcher_direct_hit: {
		sdk::vector right;
		sdk::qangle eye_angles{ g_entity_list->local->eye_angles_x( ), g_entity_list->local->eye_angles_y( ), 0 };
		sdk::qangle punch_angle{ g_entity_list->local->punch_angle( ).x, g_entity_list->local->punch_angle( ).y,
			                     g_entity_list->local->punch_angle( ).z };

		math::angle_to_vector( eye_angles + punch_angle, NULL, &right, NULL );

		return { 1980.f, sdk::vector( 0, 0, -8 ) + right * 12 };
	}
	default:
		return { -1.f, {} };
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

void aimbot::run( )
{
	if ( !g_entity_list->cmd )
		return;

	if ( !g_entity_list->weapon )
		return;

	CONFIG( aimbot_mouse_enabled, bool );
	CONFIG( aimbot_mouse_fov, float );
	CONFIG( aimbot_mouse_hitbox_head, bool );
	CONFIG( aimbot_mouse_hitbox_chest, bool );
	CONFIG( aimbot_mouse_hitbox_stomach, bool );
	CONFIG( aimbot_mouse_hitbox_arms, bool );
	CONFIG( aimbot_mouse_hitbox_legs, bool );
	CONFIG( aimbot_mouse_curve_linear, bool );
	CONFIG( aimbot_mouse_curve_quadratic, bool );
	CONFIG( aimbot_mouse_curve_cubic, bool );
	CONFIG( aimbot_mouse_curve_quartic, bool );
	CONFIG( aimbot_mouse_curve_quintic, bool );
	CONFIG( aimbot_mouse_smoothing, float );

	CONFIG( aimbot_silent_enabled, bool );
	CONFIG( aimbot_silent_fov, float );
	CONFIG( aimbot_silent_hitbox_head, bool );
	CONFIG( aimbot_silent_hitbox_chest, bool );
	CONFIG( aimbot_silent_hitbox_stomach, bool );
	CONFIG( aimbot_silent_hitbox_arms, bool );
	CONFIG( aimbot_silent_hitbox_legs, bool );

	CONFIG( aimbot_projectile_enabled, bool );
	CONFIG( aimbot_projectile_invisible, bool );
	CONFIG( aimbot_projectile_feet, bool );

	if ( *aimbot_mouse_enabled ) {
		auto target = closest_player( *aimbot_mouse_fov );

		if ( !target )
			return;

		int hitboxes{ };

		if ( *aimbot_mouse_hitbox_head )
			hitboxes |= 1 << sdk::hitbox_head;

		if ( *aimbot_mouse_hitbox_chest )
			hitboxes |= 1 << sdk::hitbox_chest;

		if ( *aimbot_mouse_hitbox_stomach ) {
			hitboxes |= 1 << sdk::hitbox_stomach;
			hitboxes |= 1 << sdk::hitbox_pelvis;
		}

		if ( *aimbot_mouse_hitbox_arms ) {
			hitboxes |= 1 << sdk::hitbox_left_hand;
			hitboxes |= 1 << sdk::hitbox_right_hand;
			hitboxes |= 1 << sdk::hitbox_right_upper_arm;
			hitboxes |= 1 << sdk::hitbox_right_forearm;
			hitboxes |= 1 << sdk::hitbox_left_upper_arm;
			hitboxes |= 1 << sdk::hitbox_left_forearm;
		}

		if ( *aimbot_mouse_hitbox_legs ) {
			hitboxes |= 1 << sdk::hitbox_left_foot;
			hitboxes |= 1 << sdk::hitbox_right_foot;
			hitboxes |= 1 << sdk::hitbox_left_calf;
			hitboxes |= 1 << sdk::hitbox_right_calf;
			hitboxes |= 1 << sdk::hitbox_left_thigh;
			hitboxes |= 1 << sdk::hitbox_right_thigh;
		}

		auto target_hitbox = closest_hitbox( target, hitboxes );

		sdk::qangle local_angles{ };

		g_interfaces->engine_client->get_view_angles( local_angles );

		sdk::vector position{ };

		auto weapon_info = get_weapon_info( );

		// if ( weapon_info.speed > -1.f && *aimbot_projectile_enabled ) {
		//	auto offset = g_entity_list->local->eye_position( ) + weapon_info.offset;
		//	position    = g_prediction->linear(
		//              offset, target,
		//              *aimbot_projectile_feet ? sdk::vector{ 0, 0, 2 }
		//								   : sdk::vector{ 0, 0, ( target->get_hitbox_position( sdk::hitbox_pelvis ) - target->get_abs_origin( ) ).z },
		//              weapon_info.speed, *aimbot_projectile_invisible );
		//} else {
		position = target->get_hitbox_position( target_hitbox );
		//} Too performance impacting.

		auto view_angles  = math::vector_to_angle( position - g_entity_list->local->eye_position( ) );
		auto fov_distance = view_angles - local_angles;
		auto distance     = fov_distance.normalize( ).length( );
		float distance_percent{ };

		if ( *aimbot_mouse_curve_linear )
			distance_percent = ( -( LinearInterpolation( std::clamp( distance / *aimbot_mouse_fov, 0.f, 1.f ) ) ) + 1.f ) * *aimbot_mouse_smoothing;

		if ( *aimbot_mouse_curve_quadratic )
			distance_percent = ( -( QuadraticEaseIn( std::clamp( distance / *aimbot_mouse_fov, 0.f, 1.f ) ) ) + 1.f ) * *aimbot_mouse_smoothing;

		if ( *aimbot_mouse_curve_cubic )
			distance_percent = ( -( CubicEaseIn( std::clamp( distance / *aimbot_mouse_fov, 0.f, 1.f ) ) ) + 1.f ) * *aimbot_mouse_smoothing;

		if ( *aimbot_mouse_curve_quartic )
			distance_percent = ( -( QuarticEaseIn( std::clamp( distance / *aimbot_mouse_fov, 0.f, 1.f ) ) ) + 1.f ) * *aimbot_mouse_smoothing;

		if ( *aimbot_mouse_curve_quintic )
			distance_percent = ( -( QuinticEaseIn( std::clamp( distance / *aimbot_mouse_fov, 0.f, 1.f ) ) ) + 1.f ) * *aimbot_mouse_smoothing;

		auto smoothed = local_angles + ( fov_distance * distance_percent );
		auto normal   = smoothed.normalize( );

		g_interfaces->engine_client->set_view_angles( normal );
	}

	if ( *aimbot_silent_enabled ) {
		auto target = closest_player( *aimbot_silent_fov );

		if ( !target )
			return;

		int hitboxes{ };

		if ( *aimbot_silent_hitbox_head )
			hitboxes |= 1 << sdk::hitbox_head;

		if ( *aimbot_silent_hitbox_chest )
			hitboxes |= 1 << sdk::hitbox_chest;

		if ( *aimbot_silent_hitbox_stomach ) {
			hitboxes |= 1 << sdk::hitbox_stomach;
			hitboxes |= 1 << sdk::hitbox_pelvis;
		}

		if ( *aimbot_silent_hitbox_arms ) {
			hitboxes |= 1 << sdk::hitbox_left_hand;
			hitboxes |= 1 << sdk::hitbox_right_hand;
			hitboxes |= 1 << sdk::hitbox_right_upper_arm;
			hitboxes |= 1 << sdk::hitbox_right_forearm;
			hitboxes |= 1 << sdk::hitbox_left_upper_arm;
			hitboxes |= 1 << sdk::hitbox_left_forearm;
		}

		if ( *aimbot_silent_hitbox_legs ) {
			hitboxes |= 1 << sdk::hitbox_left_foot;
			hitboxes |= 1 << sdk::hitbox_right_foot;
			hitboxes |= 1 << sdk::hitbox_left_calf;
			hitboxes |= 1 << sdk::hitbox_right_calf;
			hitboxes |= 1 << sdk::hitbox_left_thigh;
			hitboxes |= 1 << sdk::hitbox_right_thigh;
		}

		auto weapon_info = get_weapon_info( );

		if ( weapon_info.speed > -1.f && *aimbot_projectile_enabled ) {
			if ( g_entity_list->cmd->buttons & sdk::in_attack &&
			     ( g_entity_list->weapon->can_attack_primary( g_entity_list->local ) || g_cl_move->max_shifted ) ) {
				if ( *aimbot_projectile_invisible ) {
					if ( !g_aimbot->choked_ticks ) {
						auto offset   = g_entity_list->local->eye_position( ) + weapon_info.offset;
						auto position = g_prediction->linear(
							offset, target,
							*aimbot_projectile_feet
								? sdk::vector{ 0, 0, 2 }
								: sdk::vector{ 0, 0, ( target->get_hitbox_position( sdk::hitbox_pelvis ) - target->get_abs_origin( ) ).z },
							weapon_info, *aimbot_projectile_invisible );

						auto view_angles = math::vector_to_angle( position - offset );

						g_aimbot->running_choke         = true;
						g_aimbot->choked_ticks          = 0;
						g_entity_list->cmd->view_angles = view_angles;
					}

					if ( g_aimbot->choked_ticks == 2 ) {
						g_aimbot->choked_ticks  = 0;
						g_aimbot->running_choke = false;
					}
				} else {
					auto offset   = g_entity_list->local->eye_position( ) + weapon_info.offset;
					auto position = g_prediction->linear(
						offset, target,
						*aimbot_projectile_feet
							? sdk::vector{ 0, 0, 2 }
							: sdk::vector{ 0, 0, ( target->get_hitbox_position( sdk::hitbox_pelvis ) - target->get_abs_origin( ) ).z },
						weapon_info, *aimbot_projectile_invisible );

					auto view_angles = math::vector_to_angle( position - offset );

					g_entity_list->cmd->view_angles = view_angles;
				}
			}
		} else {
			if ( g_entity_list->cmd->buttons & sdk::in_attack &&
			     ( g_entity_list->weapon->can_attack_primary( g_entity_list->local ) || g_cl_move->max_shifted ) ) {
				auto target_hitbox = closest_hitbox( target, hitboxes );
				auto view_angles   = math::vector_to_angle( target->get_hitbox_position( target_hitbox ) - g_entity_list->local->eye_position( ) );

				g_entity_list->cmd->view_angles = view_angles;
			}
		}
	}
}
