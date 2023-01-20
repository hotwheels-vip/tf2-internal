//
// Created by liga on 11/13/2022.
//

#include "prediction.hpp"
#include "../../helpers/config/config.hpp"
#include "../../hooks/cl_move/cl_move.hpp"
#include <chrono>
#include <deque>

restore< float > cur_time{ };
restore< float > frame_time{ };
restore< int > tick_count{ };
restore< int > tick_base{ };
restore< float > fall_velocity{ };

void prediction::run( sdk::c_user_cmd* cmd, sdk::c_tf_player* player )
{
	const auto last_command    = g_interfaces->client_state->last_command_ack;
	const auto last_outgoing   = g_interfaces->client_state->last_out_going_command;
	const auto choked_commands = g_interfaces->client_state->choked_commands;
	const auto delta_tick      = g_interfaces->client_state->delta_tick;

	if ( delta_tick > 0 || g_cl_move->force_update )
		g_interfaces->prediction->update( delta_tick, delta_tick > 0, last_command, last_outgoing + choked_commands );

	cur_time   = restore( &g_interfaces->globals->cur_time );
	frame_time = restore( &g_interfaces->globals->frame_time );
	tick_count = restore( &g_interfaces->globals->tick_count );
	tick_base  = restore( &player->tick_base( ) );

	reset( );

	player->current_command( ) = cmd;
	set_prediction_random_seed( cmd );
	set_prediction_player( player );

	g_interfaces->globals->tick_count = player->tick_base( );
	g_interfaces->globals->cur_time   = static_cast< float >( player->tick_base( ) ) * g_interfaces->globals->interval_per_tick;
	g_interfaces->globals->frame_time = g_interfaces->globals->interval_per_tick;

	auto first_time_predicted = restore( &g_interfaces->prediction->first_time_predicted );
	auto in_prediction        = restore( &g_interfaces->prediction->is_in_prediction );

	g_interfaces->prediction->first_time_predicted = false;
	g_interfaces->prediction->is_in_prediction     = true;

	sdk::move_data_t move_data{ };

	g_interfaces->game_movement->start_track_prediction_errors( player );
	g_interfaces->prediction->set_local_view_angles( cmd->view_angles );

	player->pre_think( );

	g_interfaces->prediction->setup_move( player, cmd, g_interfaces->move_helper, &move_data );
	g_interfaces->game_movement->process_movement( player, &move_data );
	g_interfaces->prediction->finish_move( player, cmd, &move_data );

	g_interfaces->move_helper->process_impacts( );

	fall_velocity = restore( &player->fall_velocity( ) );

	running_post_think = true;

	player->post_think( );

	running_post_think = false;

	fall_velocity.run( );
	tick_base.run( );
	first_time_predicted.run( );
	in_prediction.run( );
}

void prediction::end( sdk::c_user_cmd* cmd, sdk::c_tf_player* player )
{
	player->current_command( ) = nullptr;

	if ( g_interfaces->globals->frame_time > 0.f )
		player->tick_base( )++;

	g_interfaces->game_movement->finish_track_prediction_errors( player );
	g_interfaces->move_helper->set_host( nullptr );

	set_prediction_random_seed( nullptr );
	set_prediction_player( nullptr );

	cur_time.run( );
	frame_time.run( );
	tick_count.run( );
}

void prediction::set_prediction_random_seed( sdk::c_user_cmd* cmd )
{
	static auto set_prediction_random_seed = g_signatures[ HASH( "55 8B EC 8B 45 ? 85 C0 75 ? C7 05" ) ].as< void ( * )( sdk::c_user_cmd* ) >( );
	set_prediction_random_seed( cmd );
}

void prediction::set_prediction_player( sdk::c_tf_player* player )
{
	static auto predicted_player = g_signatures[ HASH( "83 3D ? ? ? ? ? 74 ? 6A ? 50" ) ].get( 1 ).as< sdk::c_tf_player* >( );
	predicted_player             = player;
}

void prediction::reset( )
{
	static auto reset = g_signatures[ HASH( "68 ? ? ? ? 6A ? 68 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? 83 C4 ? C3" ) ].as< void ( * )( ) >( );
	reset( );
}

sdk::vector prediction::linear( sdk::vector origin, sdk::c_tf_player* player, sdk::vector offset, weapon_info data, bool choke )
{
	CONFIG( aimbot_projectile_steps, int );

	using namespace std::chrono;

	static auto gravity_cvar = g_interfaces->cvar->find_var( "sv_gravity" );

	auto gravity  = gravity_cvar->get_float( );
	auto position = player->get_abs_origin( );

	std::deque< sdk::vector > records{ };

	for ( int i = 0; i < *aimbot_projectile_steps; i++ ) {
		player->current_command( ) = &projectile_cmd;

		projectile_backup.origin          = player->origin( );
		projectile_backup.base_velocity   = player->base_velocity( );
		projectile_backup.duck_jump_time  = player->duck_jump_time( );
		projectile_backup.duck_time       = player->duck_timer( );
		projectile_backup.ducked          = player->ducked( );
		projectile_backup.ducking         = player->ducking( );
		projectile_backup.flags           = player->flags( );
		projectile_backup.ground_entity   = player->ground_entity( );
		projectile_backup.in_duck_jump    = player->in_duck_jump( );
		projectile_backup.model_scale     = player->model_scale( );
		projectile_backup.velocity        = player->estimate_abs_velocity( );
		projectile_backup.simulation_time = player->simulation_time( );

		projectile_backup.is_in_prediction   = g_interfaces->prediction->is_in_prediction;
		projectile_backup.first_time_running = g_interfaces->prediction->first_time_predicted;
		projectile_backup.frame_time         = g_interfaces->globals->frame_time;
		projectile_backup.tick_base          = player->tick_base( );
		projectile_backup.cur_time           = g_interfaces->globals->cur_time;

		if ( player->flags( ) & sdk::ducking ) {
			player->flags( ) &= ~sdk::ducking;
			player->ducked( )         = true;
			player->ducktime( )       = 0.f;
			player->duck_jump_time( ) = 0.f;
			player->ducking( )        = false;
			player->in_duck_jump( )   = false;
		}

		player->ground_entity( ) = { };

		player->model_scale( ) -= 0.03125f;

		if ( player->flags( ) & sdk::onground )
			player->origin( ).z += 0.03125f;

		if ( fabsf( player->velocity( ).x ) < 0.01f )
			player->velocity( ).x = 0.015f;

		if ( fabsf( player->velocity( ).y ) < 0.01f )
			player->velocity( ).y = 0.015f;

		projectile_move_data.first_run_of_functions = false;
		projectile_move_data.game_code_moved_player = false;
		projectile_move_data.player_handle          = player->get_ref_e_handle( );
		projectile_move_data.velocity               = player->estimate_abs_velocity( );
		projectile_move_data.abs_origin             = player->get_abs_origin( );

		projectile_move_data.view_angles = { 0.f, math::vector_to_angle( projectile_move_data.velocity ).yaw, 0.f };

		sdk::vector forward{ }, right{ }, up{ };

		math::angle_to_vector( projectile_move_data.view_angles, &forward, &right, &up );

		projectile_move_data.forward_move =
			( projectile_move_data.velocity.y - right.y / right.x * projectile_move_data.velocity.x ) / ( forward.y - right.y / right.x * forward.x );
		projectile_move_data.side_move = ( projectile_move_data.velocity.x - forward.x * projectile_move_data.forward_move ) / right.x;

		if ( i == 0 ) {
			auto pred_time = origin.dist_to( position ) / data.speed;
			pred_time += g_interfaces->engine_client->get_net_channel_info( )->get_latency( 0 );
			pred_time += choke ? g_interfaces->globals->interval_per_tick : 0.f;

			g_interfaces->prediction->is_in_prediction     = true;
			g_interfaces->prediction->first_time_predicted = true;
			g_interfaces->globals->frame_time              = g_interfaces->prediction->engine_paused ? 0.f : g_interfaces->globals->interval_per_tick;

			for ( int j = 0; j < pred_time / g_interfaces->globals->interval_per_tick; j++ )
				g_interfaces->game_movement->process_movement( player, &projectile_move_data );

		} else {
			auto pred_time = origin.dist_to( records.at( i - 1 ) ) / data.speed;
			pred_time += g_interfaces->engine_client->get_net_channel_info( )->get_latency( 0 );
			pred_time += choke ? g_interfaces->globals->interval_per_tick : 0.f;

			g_interfaces->prediction->is_in_prediction     = true;
			g_interfaces->prediction->first_time_predicted = true;
			g_interfaces->globals->frame_time              = g_interfaces->prediction->engine_paused ? 0.f : g_interfaces->globals->interval_per_tick;

			for ( int j = 0; j < pred_time / g_interfaces->globals->interval_per_tick; j++ )
				g_interfaces->game_movement->process_movement( player, &projectile_move_data );
		}

		records.push_back( projectile_move_data.abs_origin );

		player->current_command( ) = { };

		player->origin( )          = projectile_backup.origin;
		player->base_velocity( )   = projectile_backup.base_velocity;
		player->duck_jump_time( )  = projectile_backup.duck_jump_time;
		player->duck_timer( )      = projectile_backup.duck_time;
		player->ducked( )          = projectile_backup.ducked;
		player->ducking( )         = projectile_backup.ducking;
		player->flags( )           = projectile_backup.flags;
		player->ground_entity( )   = projectile_backup.ground_entity;
		player->in_duck_jump( )    = projectile_backup.in_duck_jump;
		player->model_scale( )     = projectile_backup.model_scale;
		player->velocity( )        = projectile_backup.velocity;
		player->simulation_time( ) = projectile_backup.simulation_time;
		player->tick_base( )       = projectile_backup.tick_base;

		g_interfaces->prediction->is_in_prediction     = projectile_backup.is_in_prediction;
		g_interfaces->prediction->first_time_predicted = projectile_backup.first_time_running;
		g_interfaces->globals->frame_time              = projectile_backup.frame_time;
		g_interfaces->globals->cur_time                = projectile_backup.cur_time;

		memset( &projectile_move_data, 0, sizeof( sdk::move_data_t ) );
		memset( &projectile_backup, 0, sizeof( prediction_projectile_backup ) );
	}

	return records.at( *aimbot_projectile_steps - 1 ) + offset;
}

sdk::vector solve_quadratic( sdk::vector start, sdk::vector end, weapon_info info )
{
	static auto g0 = g_interfaces->cvar->find_var( "sv_gravity" );

	sdk::vector m = end - start;
	float dx      = sqrt( m.x * m.x + m.y * m.y );
	float dy      = m.z;
	float v       = info.speed;
	float g       = g0->get_float( ) * info.gravity;

	float a = v * v * v * v - g * ( g * dx * dx + 2.f * dy * v * v );

	if ( a < 0.f )
		return { };

	float pitch = atan( ( v * v - sqrt( a ) ) / ( g * dx ) );
	float yaw   = atan2( m.y, m.x );

	return { pitch, yaw, dx / ( cos( pitch ) * v ) };
}

sdk::qangle prediction::quadratic( sdk::vector origin, sdk::c_tf_player* player, sdk::vector offset, weapon_info data, bool choke )
{
	CONFIG( aimbot_projectile_steps, int );

	using namespace std::chrono;

	static auto gravity_cvar = g_interfaces->cvar->find_var( "sv_gravity" );

	auto gravity  = gravity_cvar->get_float( );
	auto position = player->get_abs_origin( );

	std::deque< sdk::vector > records{ };

	for ( int i = 0; i < *aimbot_projectile_steps; i++ ) {
		player->current_command( ) = &projectile_cmd;

		projectile_backup.origin          = player->origin( );
		projectile_backup.base_velocity   = player->base_velocity( );
		projectile_backup.duck_jump_time  = player->duck_jump_time( );
		projectile_backup.duck_time       = player->duck_timer( );
		projectile_backup.ducked          = player->ducked( );
		projectile_backup.ducking         = player->ducking( );
		projectile_backup.flags           = player->flags( );
		projectile_backup.ground_entity   = player->ground_entity( );
		projectile_backup.in_duck_jump    = player->in_duck_jump( );
		projectile_backup.model_scale     = player->model_scale( );
		projectile_backup.velocity        = player->estimate_abs_velocity( );
		projectile_backup.simulation_time = player->simulation_time( );

		projectile_backup.is_in_prediction   = g_interfaces->prediction->is_in_prediction;
		projectile_backup.first_time_running = g_interfaces->prediction->first_time_predicted;
		projectile_backup.frame_time         = g_interfaces->globals->frame_time;
		projectile_backup.tick_base          = player->tick_base( );
		projectile_backup.cur_time           = g_interfaces->globals->cur_time;

		if ( player->flags( ) & sdk::ducking ) {
			player->flags( ) &= ~sdk::ducking;
			player->ducked( )         = true;
			player->ducktime( )       = 0.f;
			player->duck_jump_time( ) = 0.f;
			player->ducking( )        = false;
			player->in_duck_jump( )   = false;
		}

		player->ground_entity( ) = { };

		player->model_scale( ) -= 0.03125f;

		if ( player->flags( ) & sdk::onground )
			player->origin( ).z += 0.03125f;

		if ( fabsf( player->velocity( ).x ) < 0.01f )
			player->velocity( ).x = 0.015f;

		if ( fabsf( player->velocity( ).y ) < 0.01f )
			player->velocity( ).y = 0.015f;

		projectile_move_data.first_run_of_functions = false;
		projectile_move_data.game_code_moved_player = false;
		projectile_move_data.player_handle          = player->get_ref_e_handle( );
		projectile_move_data.velocity               = player->estimate_abs_velocity( );
		projectile_move_data.abs_origin             = player->get_abs_origin( );

		projectile_move_data.view_angles = { 0.f, math::vector_to_angle( projectile_move_data.velocity ).yaw, 0.f };

		sdk::vector forward{ }, right{ }, up{ };

		math::angle_to_vector( projectile_move_data.view_angles, &forward, &right, &up );

		projectile_move_data.forward_move =
			( projectile_move_data.velocity.y - right.y / right.x * projectile_move_data.velocity.x ) / ( forward.y - right.y / right.x * forward.x );
		projectile_move_data.side_move = ( projectile_move_data.velocity.x - forward.x * projectile_move_data.forward_move ) / right.x;

		if ( i == 0 ) {
			auto pred_time = solve_quadratic( origin, position, data ).z;
			pred_time += g_interfaces->engine_client->get_net_channel_info( )->get_latency( 0 );
			pred_time += choke ? g_interfaces->globals->interval_per_tick : 0.f;

			g_interfaces->prediction->is_in_prediction     = true;
			g_interfaces->prediction->first_time_predicted = true;
			g_interfaces->globals->frame_time              = g_interfaces->prediction->engine_paused ? 0.f : g_interfaces->globals->interval_per_tick;

			for ( int j = 0; j < pred_time / g_interfaces->globals->interval_per_tick; j++ )
				g_interfaces->game_movement->process_movement( player, &projectile_move_data );

			// pred_time = solve_quadratic( origin, projectile_move_data.abs_origin, data ).z;

			// for ( int j = 0; j < pred_time / g_interfaces->globals->interval_per_tick; j++ )
			//	g_interfaces->game_movement->process_movement( player, &projectile_move_data );

		} else {
			auto pred_time = solve_quadratic( origin, records.at( i - 1 ), data ).z;
			pred_time += g_interfaces->engine_client->get_net_channel_info( )->get_latency( 0 );
			pred_time += choke ? g_interfaces->globals->interval_per_tick : 0.f;

			g_interfaces->prediction->is_in_prediction     = true;
			g_interfaces->prediction->first_time_predicted = true;
			g_interfaces->globals->frame_time              = g_interfaces->prediction->engine_paused ? 0.f : g_interfaces->globals->interval_per_tick;

			for ( int j = 0; j < pred_time / g_interfaces->globals->interval_per_tick; j++ )
				g_interfaces->game_movement->process_movement( player, &projectile_move_data );

			// pred_time = solve_quadratic( origin, projectile_move_data.abs_origin, data ).z;

			// for ( int j = 0; j < pred_time / g_interfaces->globals->interval_per_tick; j++ )
			// g_interfaces->game_movement->process_movement( player, &projectile_move_data );
		}

		records.push_back( projectile_move_data.abs_origin );

		player->current_command( ) = { };

		player->origin( )          = projectile_backup.origin;
		player->base_velocity( )   = projectile_backup.base_velocity;
		player->duck_jump_time( )  = projectile_backup.duck_jump_time;
		player->duck_timer( )      = projectile_backup.duck_time;
		player->ducked( )          = projectile_backup.ducked;
		player->ducking( )         = projectile_backup.ducking;
		player->flags( )           = projectile_backup.flags;
		player->ground_entity( )   = projectile_backup.ground_entity;
		player->in_duck_jump( )    = projectile_backup.in_duck_jump;
		player->model_scale( )     = projectile_backup.model_scale;
		player->velocity( )        = projectile_backup.velocity;
		player->simulation_time( ) = projectile_backup.simulation_time;
		player->tick_base( )       = projectile_backup.tick_base;

		g_interfaces->prediction->is_in_prediction     = projectile_backup.is_in_prediction;
		g_interfaces->prediction->first_time_predicted = projectile_backup.first_time_running;
		g_interfaces->globals->frame_time              = projectile_backup.frame_time;
		g_interfaces->globals->cur_time                = projectile_backup.cur_time;

		memset( &projectile_move_data, 0, sizeof( sdk::move_data_t ) );
		memset( &projectile_backup, 0, sizeof( prediction_projectile_backup ) );
	}

	auto final = records.at( *aimbot_projectile_steps - 1 ) + offset;
	auto solve = solve_quadratic( origin, final, data );
	sdk::qangle convert{ -RAD2DEG( solve.x ), RAD2DEG( solve.y ), 0 };

	return convert.normalize( );
}
