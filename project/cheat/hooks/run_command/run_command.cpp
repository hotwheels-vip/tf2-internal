#include "run_command.hpp"

#include "../../features/tickbase/tickbase.hpp"
#include "../cl_move/cl_move.hpp"

void __fastcall run_command::detour( void* ecx, void* edx, sdk::c_base_player* player, sdk::c_user_cmd* command, void* move_helper )
{
	// static auto clock_correction = g_interfaces->cvar->find_var( "sv_clockcorrection_msecs" );
	// float correction_ticks       = std::clamp( clock_correction->get_float( ) / 1000.f, 0.f, 1.f ) / g_interfaces->globals->interval_per_tick;

	// auto simulation_ticks = 1;

	// int ping_ticks           = g_interfaces->engine_client->get_net_channel_info( )->get_latency( 2 ) / g_interfaces->globals->interval_per_tick;
	// int ideal_final_tick     = g_tickbase->last_tick + correction_ticks + ping_ticks;
	// int estimated_final_tick = player->tick_base( ) + simulation_ticks;
	// int too_fast_limit       = ideal_final_tick + correction_ticks;
	// int too_slow_limit       = ideal_final_tick - correction_ticks;

	// if ( estimated_final_tick > too_fast_limit || estimated_final_tick < too_slow_limit ) {
	//	int corrected_tick = ideal_final_tick - simulation_ticks + g_interfaces->globals->sim_ticks_this_frame;

	//	player->tick_base( ) = corrected_tick;

	//	g_interfaces->globals->tick_count = corrected_tick;
	//	g_interfaces->globals->cur_time   = corrected_tick * g_interfaces->globals->interval_per_tick;
	//}

	g_run_command->_hook.call( ecx, edx, player, command, move_helper );
}
