#include "frame_stage_notify.hpp"

void __fastcall frame_stage_notify::detour( void* ecx, void* edx, sdk::client_frame_stage stage )
{
	g_frame_stage_notify->_hook.call( ecx, edx, stage );

	switch ( stage ) {
	case sdk::frame_net_update_end: {
		for ( auto player : g_entity_list->enemy ) {
			if ( !player )
				continue;

			auto var_map = player->get_var_mapping( );

			if ( !var_map )
				continue;

			if ( !g_entity_list->local || !g_entity_list->cmd )
				continue;

			if ( var_map->interpolated_entries > 20108 )
				continue;

			for ( int i = 0; i < var_map->interpolated_entries; i++ ) {
				var_map->entries[ i ].needs_to_interpolate = false;
			}
		}

		break;
	}
	}
}
