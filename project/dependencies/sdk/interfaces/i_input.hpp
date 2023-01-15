#pragma once

#include "../structs/c_verified_cmd.hpp"

namespace sdk
{
	enum button_code_t;
	enum game_action_set_t;
	enum game_action_set_flags_t;
	enum camera_third_data_t;

	struct kbutton_t;
	struct c_base_combat_weapon;
	class bf_write;
	class bf_read;

	struct i_input {
	public:
		// initialization/shutdown of the subsystem
		virtual void init_all( void )     = 0;
		virtual void shutdown_all( void ) = 0;
		// latching button states
		virtual int get_button_bits( int ) = 0;
		// create movement command
		virtual void create_move( int sequence_number, float input_sample_frametime, bool active )       = 0;
		virtual void extra_mouse_sample( float frametime, bool active )                                  = 0;
		virtual bool write_usercmd_delta_to_buffer( bf_write* buf, int from, int to, bool isnewcommand ) = 0;
		virtual void encode_user_cmd_to_buffer( bf_write& buf, int slot )                                = 0;
		virtual void decode_user_cmd_from_buffer( bf_read& buf, int slot )                               = 0;

		virtual c_user_cmd* get_user_cmd( int sequence_number ) = 0;

		virtual void make_weapon_selection( c_base_combat_weapon* weapon ) = 0;

		// retrieve key state
		virtual float key_state( kbutton_t* key ) = 0;
		// issue key event
		virtual int key_event( int eventcode, button_code_t keynum, const char* psz_current_binding ) = 0;
		// look for key
		virtual kbutton_t* find_key( const char* name ) = 0;

		// issue commands from controllers
		virtual void controller_commands( void ) = 0;
		// extra initialization for some joysticks
		virtual void joystick_advanced( void )                   = 0;
		virtual void joystick_set_sample_time( float frametime ) = 0;
		virtual void in_set_sample_time( float frametime )       = 0;

		// accumulate mouse delta
		virtual void accumulate_mouse( void ) = 0;
		// activate/deactivate mouse
		virtual void activate_mouse( void )   = 0;
		virtual void deactivate_mouse( void ) = 0;

		// clear mouse state data
		virtual void clear_states( void ) = 0;
		// retrieve lookspring setting
		virtual float get_look_spring( void ) = 0;

		// retrieve mouse position
		virtual void get_fullscreen_mouse_pos( int* mx, int* my, int* unclampedx = 0, int* unclampedy = 0 ) = 0;
		virtual void set_fullscreen_mouse_pos( int mx, int my )                                             = 0;
		virtual void reset_mouse( void )                                                                    = 0;
		virtual float get_last_forward_move( void )                                                         = 0;
		virtual float joystick_get_forward( void )                                                          = 0;
		virtual float joystick_get_side( void )                                                             = 0;
		virtual float joystick_get_pitch( void )                                                            = 0;
		virtual float joystick_get_yaw( void )                                                              = 0;

		// third person camera
		virtual void cam_think( void )             = 0;
		virtual int cam_is_third_person( void )    = 0;
		virtual void cam_to_third_person( void )   = 0;
		virtual void cam_to_first_person( void )   = 0;
		virtual void cam_start_mouse_move( void )  = 0;
		virtual void cam_end_mouse_move( void )    = 0;
		virtual void cam_start_distance( void )    = 0;
		virtual void cam_end_distance( void )      = 0;
		virtual int cam_intercepting_mouse( void ) = 0;

		// orthographic camera info
		virtual void cam_to_orthographic( )                            = 0;
		virtual bool cam_is_orthographic( ) const                      = 0;
		virtual void cam_orthographic_size( float& w, float& h ) const = 0;

		virtual void set_preferred_game_action_set( game_action_set_t action_set )         = 0;
		virtual game_action_set_t get_preferred_game_action_set( )                         = 0;
		virtual void set_game_action_set_flags( game_action_set_flags_t action_set_flags ) = 0;

		virtual void level_init( void ) = 0;

		// causes an input to have to be re-pressed to become active
		virtual void clear_input_button( int bits ) = 0;

		virtual void cam_set_camera_third_data( camera_third_data_t* p_camera_data, const qangle& vec_camera_offset ) = 0;
		virtual void cam_camera_third_think( )                                                                        = 0;

		virtual bool enable_joystick_mode( ) = 0;

		virtual bool is_steam_controller_active( ) = 0;

		c_user_cmd* get_cmds( )
		{
			return *reinterpret_cast< c_user_cmd** >( reinterpret_cast< std::uintptr_t >( this ) + 0xFC );
		}

		c_verified_cmd* get_verified_cmds( )
		{
			return *reinterpret_cast< c_verified_cmd** >( reinterpret_cast< std::uintptr_t >( this ) + 0x100 );
		}

		c_verified_cmd* get_verified_cmd( int sequence_number )
		{
			return &get_verified_cmds( )[ sequence_number % 90 ];
		}
	};
} // namespace sdk
