#include "entity_list.hpp"

void entity_list::run( sdk::c_user_cmd* _cmd )
{
	g_local  = nullptr;
	g_weapon = nullptr;
	g_cmd    = _cmd;

	if ( !g_interfaces->engine_client->is_connected( ) )
		return;

	if ( const auto local_index = g_interfaces->engine_client->get_local_player( ) ) {
		g_local = reinterpret_cast< sdk::c_tf_player* >( g_interfaces->entity_list->get_client_entity( local_index ) );

		if ( const auto weapon_index = g_local->active_weapon( ); weapon_index.index ) {
			g_weapon = reinterpret_cast< sdk::c_tf_weapon_base* >( g_interfaces->entity_list->get_client_entity_from_handle( weapon_index ) );
		}
	}

	for ( int i = 0; i < 65; i++ ) {
		// dormant_info backup{ };

		// memcpy( &backup, &dormant[ i ], sizeof( dormant_info ) );
		// memset( &backup, 0, sizeof( dormant_info ) );

		enemy[ i ] = nullptr;
		team[ i ]  = nullptr;

		const auto entity = reinterpret_cast< sdk::c_tf_player* >( g_interfaces->entity_list->get_client_entity( i ) );

		if ( !entity )
			continue;

		if ( !entity->get_ref_e_handle( ).index || !entity->get_think_handle( ) || !entity->render_handle( ) )
			continue;

		if ( !entity->get_var_mapping( ) )
			continue;

		if ( !entity->is_player( ) )
			continue;

		if ( !entity->simulation_time( ) )
			continue;

		if ( !entity->is_alive( ) )
			continue;

		if ( entity->is_dormant( ) )
			continue;

		if ( entity == g_local )
			continue;

		if ( entity->team_num( ) == g_local->team_num( ) )
			team[ i ] = entity;
		else
			enemy[ i ] = entity;

		// dormant[ i ] = backup;

		// if ( entity->is_dormant( ) ) {
		//	dormant[ i ].last_seen = g_interfaces->globals->tick_count;
		//	dormant[ i ].valid     = true;
		// } else if ( g_interfaces->globals->tick_count - dormant[ i ].last_seen > 5.f / g_interfaces->globals->interval_per_tick ) {
		//	dormant[ i ].valid = false;
		// }
	}
}

void entity_list::clear( )
{
	g_local  = nullptr;
	g_weapon = nullptr;
	g_cmd    = nullptr;

	for ( int i = 0; i < 65; i++ ) {
		enemy[ i ] = nullptr;
		team[ i ]  = nullptr;
	}
}
