#include "cl_move.hpp"
#include "../../features/lagcomp/lagcomp.hpp"
#include <random>

void __cdecl cl_move::detour( float accumulated_extra_samples, bool final_tick )
{
	if ( g_cl_move->force_charge ) {
		if ( g_cl_move->stored < 22 ) {
			g_cl_move->stored++;
			g_cl_move->charging = true;

			return;
		}
	}

	g_cl_move->charging = false;

	g_cl_move->_hook.call( accumulated_extra_samples, final_tick );

	if ( !g_local || !g_cmd || !g_interfaces->engine_client->get_local_player( ) ) {
		g_cl_move->max_shifted = g_cl_move->stored;

		for ( int i = 1; i <= g_cl_move->stored; i++ ) {
			g_cl_move->shifting = true;
			g_cl_move->choke    = i == g_cl_move->stored;
			g_cl_move->shifted++;

			g_cl_move->_hook.call( accumulated_extra_samples, final_tick );
		}

		g_cl_move->stored      = 0;
		g_cl_move->max_shifted = 0;
		g_cl_move->shifted     = 0;
		g_cl_move->choke       = true;
		g_cl_move->shifting    = false;
		return;
	}

	// if ( ( ( sdk::i_net_channel* )g_interfaces->engine_client )->get_choked_packets( ) > 1 )
	// return;

	if ( g_cl_move->force_shift || ( g_cmd->buttons & sdk::in_attack && final_tick ) ) {
		g_cl_move->max_shifted = g_cl_move->stored;

		for ( int i = 1; i <= g_cl_move->stored; i++ ) {
			g_cl_move->shifting = true;
			g_cl_move->choke    = i == g_cl_move->stored;
			g_cl_move->shifted++;

			g_cl_move->_hook.call( accumulated_extra_samples, final_tick );
		}

		g_cl_move->shifting    = false;
		g_cl_move->stored      = 0;
		g_cl_move->max_shifted = 0;
		g_cl_move->shifted     = 0;
		g_cl_move->choke       = true;
	}
}
