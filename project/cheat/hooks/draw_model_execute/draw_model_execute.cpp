#include "draw_model_execute.hpp"
#include "../../features/lagcomp/lagcomp.hpp"

void draw_model_execute::detour( void* ecx, void* edx, void* state, sdk::model_render_info& info, sdk::matrix_3x4* matrix )
{
	const auto unknown = info.renderable->get_i_client_unknown( );

	if ( !unknown )
		return g_draw_model_execute->_hook.call( ecx, edx, state, info, matrix );

	const auto client = unknown->get_i_client_entity( );

	if ( !client )
		return g_draw_model_execute->_hook.call( ecx, edx, state, info, matrix );

	const auto max_allocation = static_cast< int >( 1.f / g_interfaces->globals->interval_per_tick );

	if ( const auto player = reinterpret_cast< sdk::c_tf_player* >( client ); player->is_player( ) ) {
		if ( const auto record_list = g_lagcomp->records[ player->entindex( ) ] ) {
			for ( int i = 0; i < max_allocation; i++ ) {
				auto record = record_list[ i ];

				if ( !record.valid )
					continue;

				float old_mod[ 3 ]{ };
				const auto blend = g_interfaces->render_view->get_blend( );

				g_interfaces->render_view->get_color_modulation( old_mod );

				g_interfaces->render_view->set_color_modulation( 0.3f, 0.3f, 0.3f );
				g_interfaces->render_view->set_blend( 0.2f );

				g_draw_model_execute->_hook.call( ecx, edx, state, info, record.matrix );

				g_interfaces->render_view->set_color_modulation( old_mod );
				g_interfaces->render_view->set_blend( blend );
			}
		}
	}

	return g_draw_model_execute->_hook.call( ecx, edx, state, info, matrix );
}
