#include "entity_list.hpp"

void entity_list::run( sdk::c_user_cmd* _cmd )
{
	local  = nullptr;
	weapon = nullptr;
	cmd    = _cmd;

	if ( !g_interfaces->engine_client->is_connected( ) )
		return;

	if ( const auto local_index = g_interfaces->engine_client->get_local_player( ) ) {
		local = reinterpret_cast< sdk::c_tf_player* >( g_interfaces->entity_list->get_client_entity( local_index ) );

		if ( const auto weapon_index = local->active_weapon( ); weapon_index.index ) {
			weapon = reinterpret_cast< sdk::c_tf_weapon_base* >( g_interfaces->entity_list->get_client_entity_from_handle( weapon_index ) );
		}
	}

	for ( int i = 0; i < 48; i++ ) {
		enemy[ i ] = nullptr;

		const auto entity = reinterpret_cast< sdk::c_tf_player* >( g_interfaces->entity_list->get_client_entity( i ) );

		if ( !entity )
			continue;

		if ( !entity->get_ref_e_handle( ).index || !entity->get_think_handle( ) || !entity->render_handle( ) )
			continue;

		if ( !entity->is_player( ) )
			continue;

		if ( !entity->simulation_time( ) )
			continue;

		if ( !entity->is_alive( ) )
			continue;

		if ( entity == local )
			continue;

		if ( entity->team_num( ) == local->team_num( ) )
			team[ i ] = entity;
		else
			enemy[ i ] = entity;
	}
}
