#ifndef WEDNESDAY_WTF_I_PANEL_HPP
#define WEDNESDAY_WTF_I_PANEL_HPP

#include "../structs/vpanel.hpp"
#include <iostream>

namespace sdk
{
	struct i_client_panel;
	struct h_scheme;
	struct key_values;
	struct surface_plat;
	struct panel;

	struct i_panel {
	public:
		virtual ~i_panel( ) { }

		virtual void init( vpanel vgui_panel, i_client_panel* panel ) = 0;

		// methods
		virtual void set_pos( vpanel vgui_panel, int x, int y )                  = 0;
		virtual void get_pos( vpanel vgui_panel, int& x, int& y )                = 0;
		virtual void set_size( vpanel vgui_panel, int wide, int tall )           = 0;
		virtual void get_size( vpanel vgui_panel, int& wide, int& tall )         = 0;
		virtual void set_minimum_size( vpanel vgui_panel, int wide, int tall )   = 0;
		virtual void get_minimum_size( vpanel vgui_panel, int& wide, int& tall ) = 0;
		virtual void set_z_pos( vpanel vgui_panel, int z )                       = 0;
		virtual int get_z_pos( vpanel vgui_panel )                               = 0;

		virtual void get_abs_pos( vpanel vgui_panel, int& x, int& y )                             = 0;
		virtual void get_clip_rect( vpanel vgui_panel, int& x0, int& y0, int& x1, int& y1 )       = 0;
		virtual void set_inset( vpanel vgui_panel, int left, int top, int right, int bottom )     = 0;
		virtual void get_inset( vpanel vgui_panel, int& left, int& top, int& right, int& bottom ) = 0;

		virtual void set_visible( vpanel vgui_panel, bool state )             = 0;
		virtual bool is_visible( vpanel vgui_panel )                          = 0;
		virtual void set_parent( vpanel vgui_panel, vpanel new_parent )       = 0;
		virtual int get_child_count( vpanel vgui_panel )                      = 0;
		virtual vpanel get_child( vpanel vgui_panel, int index )              = 0;
		virtual vpanel* get_children( vpanel vgui_panel )                     = 0;
		virtual vpanel get_parent( vpanel vgui_panel )                        = 0;
		virtual void move_to_front( vpanel vgui_panel )                       = 0;
		virtual void move_to_back( vpanel vgui_panel )                        = 0;
		virtual bool has_parent( vpanel vgui_panel, vpanel potential_parent ) = 0;
		virtual bool is_popup( vpanel vgui_panel )                            = 0;
		virtual void set_popup( vpanel vgui_panel, bool state )               = 0;
		virtual bool is_fully_visible( vpanel vgui_panel )                    = 0;

		// gets the scheme this panel uses
		virtual h_scheme get_scheme( vpanel vgui_panel ) = 0;
		// gets whether or not this panel should scale with screen resolution
		virtual bool is_proportional( vpanel vgui_panel ) = 0;
		// returns true if auto-deletion flag is set
		virtual bool is_auto_delete_set( vpanel vgui_panel ) = 0;
		// deletes the panel * associated with the vpanel
		virtual void delete_panel( vpanel vgui_panel ) = 0;

		// input interest
		virtual void set_key_board_input_enabled( vpanel vgui_panel, bool state ) = 0;
		virtual void set_mouse_input_enabled( vpanel vgui_panel, bool state )     = 0;
		virtual bool is_key_board_input_enabled( vpanel vgui_panel )              = 0;
		virtual bool is_mouse_input_enabled( vpanel vgui_panel )                  = 0;

		// calculates the panels current position within the hierarchy
		virtual void solve( vpanel vgui_panel ) = 0;

		// gets names of the object (for debugging purposes)
		virtual const char* get_name( vpanel vgui_panel )       = 0;
		virtual const char* get_class_name( vpanel vgui_panel ) = 0;

		// delivers a message to the panel
		virtual void send_message( vpanel vgui_panel, key_values* params, vpanel ifrom_panel ) = 0;

		// these pass through to the i_client_panel
		virtual void think( vpanel vgui_panel )                                                       = 0;
		virtual void perform_apply_scheme_settings( vpanel vgui_panel )                               = 0;
		virtual void paint_traverse( vpanel vgui_panel, bool force_repaint, bool allow_force = true ) = 0;
		virtual void repaint( vpanel vgui_panel )                                                     = 0;
		virtual vpanel is_within_traverse( vpanel vgui_panel, int x, int y, bool traverse_popups )    = 0;
		virtual void on_child_added( vpanel vgui_panel, vpanel child )                                = 0;
		virtual void on_size_changed( vpanel vgui_panel, int new_wide, int new_tall )                 = 0;

		virtual void internal_focus_changed( vpanel vgui_panel, bool lost )         = 0;
		virtual bool request_info( vpanel vgui_panel, key_values* output_data )     = 0;
		virtual void request_focus( vpanel vgui_panel, int direction = 0 )          = 0;
		virtual bool request_focus_prev( vpanel vgui_panel, vpanel existing_panel ) = 0;
		virtual bool request_focus_next( vpanel vgui_panel, vpanel existing_panel ) = 0;
		virtual vpanel get_current_key_focus( vpanel vgui_panel )                   = 0;
		virtual int get_tab_position( vpanel vgui_panel )                           = 0;

		// used by i_surface to store platform-specific data
		virtual surface_plat* plat( vpanel vgui_panel )                = 0;
		virtual void set_plat( vpanel vgui_panel, surface_plat* plat ) = 0;

		// returns a pointer to the vgui controls baseclass panel *
		// destination_module needs to be passed in to verify that the returned panel * is from the same module
		// it must be from the same module since panel * vtbl may be different in each module
		virtual panel* get_panel( vpanel vgui_panel, const char* destination_module ) = 0;

		virtual bool is_enabled( vpanel vgui_panel )              = 0;
		virtual void set_enabled( vpanel vgui_panel, bool state ) = 0;

		// used by the drag/drop manager to always draw on top
		virtual bool is_topmost_popup( vpanel vgui_panel )              = 0;
		virtual void set_topmost_popup( vpanel vgui_panel, bool state ) = 0;

		// sibling pins
		virtual void set_sibling_pin( vpanel vgui_panel, vpanel new_sibling, std::byte i_my_corner_to_pin, std::byte i_sibling_corner_to_pin_to ) = 0;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_PANEL_HPP
