#include "lagcomp.hpp"
#include "../../helpers/config/config.hpp"
#include "../../helpers/entity_list/entity_list.hpp"

float lerp_time( )
{
	static sdk::con_var *cl_updaterate              = g_interfaces->cvar->find_var( "sv_maxupdaterate" ),
						*cl_interp_ratio            = g_interfaces->cvar->find_var( "cl_interp_ratio" ),
						*cl_interp                  = g_interfaces->cvar->find_var( "cl_interp" ),
						*sv_client_min_interp_ratio = g_interfaces->cvar->find_var( "sv_client_min_interp_ratio" ),
						*sv_client_max_interp_ratio = g_interfaces->cvar->find_var( "sv_client_max_interp_ratio" );

	static auto interp_ratio = max( cl_interp_ratio->get_float( ), 1.f );

	interp_ratio = std::clamp( interp_ratio, sv_client_min_interp_ratio->get_float( ), sv_client_max_interp_ratio->get_float( ) );

	return max( cl_interp->get_float( ), interp_ratio / cl_updaterate->get_int( ) );
}

bool is_valid( lagcomp::record rec )
{
	CONFIG( aimbot_lagcomp_time, int );

	auto net_channel = g_interfaces->engine_client->get_net_channel_info( );

	if ( !net_channel )
		return false;

	float correct = 0.f;

	static auto unlag_pointer = g_interfaces->cvar->find_var( "sv_maxunlag" );
	auto sv_maxunlag          = unlag_pointer->get_float( );

	correct += net_channel->get_latency( 0 );
	correct += lerp_time( );

	correct = std::clamp( correct, 0.f, sv_maxunlag );

	const float delta_correct = std::fabsf( correct - ( g_interfaces->globals->cur_time - rec.sim_time ) );

	return delta_correct <= static_cast< float >( *aimbot_lagcomp_time ) / 1000.f;
}

void lagcomp::update( )
{
	CONFIG( aimbot_lagcomp_enabled, bool );

	const auto max_allocation = static_cast< int >( 1.f / g_interfaces->globals->interval_per_tick );

	for ( auto entity : g_entity_list->enemy ) {
		if ( !entity )
			continue;

		const auto index = entity->entindex( );

		const auto& record_list = records[ index ];

		if ( !record_list )
			continue;

		for ( int j = 0; j < max_allocation; j++ ) {
			auto& record = record_list[ j ];

			if ( record.player != index && record.player != -1 ) {
				delete[] records[ index ];

				records[ index ] = nullptr;

				break;
			}

			record.valid = *aimbot_lagcomp_enabled ? is_valid( record ) : false;
		}
	}

	for ( auto entity : g_entity_list->enemy ) {
		if ( !entity )
			continue;

		const auto index = entity->entindex( );

		if ( !entity ) {
			if ( records[ index ] ) {
				delete[] records[ index ];

				records[ index ] = nullptr;
			}

			continue;
		}

		auto record    = records[ index ];
		auto& location = record_location[ index ];

		if ( !record ) {
			records[ index ] = new lagcomp::record[ max_allocation ];

			location = 0;
			record   = records[ index ];
		}

		if ( location >= max_allocation )
			location = 0;

		// auto& new_record = record[ location ];

		lagcomp::record new_record{ };

		new_record.player   = index;
		new_record.sim_time = entity->simulation_time( );
		new_record.valid    = *aimbot_lagcomp_enabled ? is_valid( new_record ) : false;

		entity->setup_bones( new_record.matrix, 128, 0x0007FF00, 0.f );

		memcpy( &record[ location ], &new_record, sizeof( lagcomp::record ) );

		location++;
	}
}

void lagcomp::run( record rec )
{
	g_cmd->tick_count = static_cast< int >( ( rec.sim_time + lerp_time( ) ) / g_interfaces->globals->interval_per_tick );
}
