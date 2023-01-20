#include "paint_traverse.hpp"

void paint_traverse::detour( void* ecx, void* edx, unsigned int panel, bool force_repaint, bool allow_force )
{
	CONFIG( menu_disabled_inputs, int );

	g_paint_traverse->_hook.call( ecx, edx, panel, force_repaint, allow_force );

	static unsigned int overlay_panel{ };

	if ( !overlay_panel ) {
		if ( RT_HASH( g_interfaces->panel->get_name( panel ) ) == HASH( "FocusOverlayPanel" ) ) {
			overlay_panel = panel;
		}
	}

	g_paint_traverse->matrix = g_interfaces->engine_client->world_to_screen_matrix( );

	if ( overlay_panel == panel ) {
		g_interfaces->panel->set_mouse_input_enabled( panel, g_menu->open && *menu_disabled_inputs & 1 << 0 );
		g_interfaces->panel->set_key_board_input_enabled( panel, g_menu->open && *menu_disabled_inputs & 1 << 1 );
	}
}
