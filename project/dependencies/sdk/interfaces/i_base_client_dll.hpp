#ifndef WEDNESDAY_WTF_I_BASE_CLIENT_DLL_HPP
#define WEDNESDAY_WTF_I_BASE_CLIENT_DLL_HPP

namespace sdk
{
	enum buttons;

	struct c_global_vars_base;
	struct client_class;
	class bf_write;
	class bf_read;
	struct vrect_t;
	struct c_view_setup;
	struct screen_fade_t;
	struct qangle;
	struct c_engine_sprite;
	struct client_frame_stage_t;
	struct c_save_restore_data;
	struct datamap_t;
	struct typedescription_t;
	struct c_standard_recv_proxies;
	struct i_con_var;
	struct i_file_list;
	struct c_renamed_recv_table_info;
	struct c_mouth_info;

	struct i_base_client_dll {
	public:
		// called once when the client dll is loaded
		virtual int init( void* app_system_factory, void* physics_factory, c_global_vars_base* p_globals ) = 0;

		virtual void post_init( ) = 0;

		// called once when the client dll is being unloaded
		virtual void shutdown( void ) = 0;

		// called once the client is initialized to setup client-side replay interface pointers
		virtual bool replay_init( void* replay_factory ) = 0;
		virtual bool replay_post_init( )                 = 0;

		// called at the start of each level change
		virtual void level_init_pre_entity( const char* p_map_name ) = 0;
		// called at the start of a new level, after the entities have been received and created
		virtual void level_init_post_entity( ) = 0;
		// called at the end of a level
		virtual void level_shutdown( void ) = 0;

		// request a pointer to the list of client datatable classes
		virtual client_class* get_all_classes( void ) = 0;

		// called once per level to re-initialize any hud element drawing stuff
		virtual int hud_vid_init( void ) = 0;
		// called by the engine when gathering user input
		virtual void hud_process_input( bool b_active ) = 0;
		// called oncer per frame to allow the hud elements to think
		virtual void hud_update( bool b_active ) = 0;
		// reset the hud elements to their initial states
		virtual void hud_reset( void ) = 0;
		// display a hud text message
		virtual void hud_text( const char* message ) = 0;

		// mouse input interfaces
		// activate the mouse (hides the cursor and locks it to the center of the screen)
		virtual void in_activate_mouse( void ) = 0;
		// deactivates the mouse (shows the cursor and unlocks it)
		virtual void in_deactivate_mouse( void ) = 0;
		// this is only called during extra sound updates and just accumulates mouse x, y offets and recenters the mouse.
		//  this call is used to try to prevent the mouse from appearing out of the side of a windowed version of the engine if
		//  rendering or other processing is taking too long
		virtual void in_accumulate( void ) = 0;
		// reset all key and mouse states to their initial, unpressed state
		virtual void in_clear_states( void ) = 0;
		// if key is found by name, returns whether it's being held down in isdown, otherwise function returns false
		virtual bool in_is_key_down( const char* name, bool& isdown ) = 0;
		// notify the client that the mouse was wheeled while in game - called prior to executing any bound commands.
		virtual void in_on_mouse_wheeled( int n_delta ) = 0;
		// raw keyboard signal, if the client .dll returns 1, the engine processes the key as usual, otherwise,
		//  if the client .dll returns 0, the key is swallowed.
		virtual int in_key_event( int eventcode, buttons keynum, const char* psz_current_binding ) = 0;

		// this function is called once per tick to create the player c_user_cmd (used for prediction/physics simulation of the player)
		// because the mouse can be sampled at greater than the tick interval, there is a separate input_sample_frametime, which
		//  specifies how much additional mouse / keyboard simulation to perform.
		virtual void create_move( int sequence_number,          // sequence_number of this cmd
		                          float input_sample_frametime, // frametime for mouse input sampling
		                          bool active ) = 0;            // true if the player is active (not paused)

		// if the game is running faster than the tick_interval framerate, then we do extra mouse sampling to avoid jittery input
		//  this code path is much like the normal move creation code, except no move is created
		virtual void extra_mouse_sample( float frametime, bool active ) = 0;

		// encode the delta (changes) between the c_user_cmd in slot from vs the one in slot to.  the game code will have
		//  matching logic to read the delta.
		virtual bool write_usercmd_delta_to_buffer( bf_write* buf, int from, int to, bool isnewcommand ) = 0;
		// demos need to be able to encode/decode c_user_cmds to memory buffers, so these functions wrap that
		virtual void encode_user_cmd_to_buffer( bf_write& buf, int slot )  = 0;
		virtual void decode_user_cmd_from_buffer( bf_read& buf, int slot ) = 0;

		// set up and render one or more views (e.g., rear view window, etc.).  this called into override_view below
		virtual void view_render( vrect_t* rect ) = 0;

		// allow engine to expressly render a view (e.g., during timerefresh)
		// see iv_render_view.h, push_view_flags_t for n_flags values 27
		virtual void render_view( const c_view_setup& view, int n_clear_flags, int what_to_draw ) = 0;

		// apply screen fade directly from engine
		virtual void view_fade( screen_fade_t* p_sf ) = 0;

		// the engine has parsed a crosshair angle message, this function is called to dispatch the new crosshair angle
		virtual void set_crosshair_angle( const qangle& angle ) = 0;

		// sprite (.spr) model handling code
		// load a .spr file by name
		virtual void init_sprite( c_engine_sprite* p_sprite, const char* loadname ) = 0;
		// shutdown a .spr file
		virtual void shutdown_sprite( c_engine_sprite* p_sprite ) = 0;
		// returns sizeof( c_engine_sprite ) so the engine can allocate appropriate memory
		virtual int get_sprite_size( void ) const = 0;

		// called when a player starts or stops talking.
		// entindex is -1 to represent the local client talking (before the data comes back from the server).
		// entindex is -2 to represent the local client's voice being acked by the server.
		// entindex is get_player() when the server acknowledges that the local client is talking.
		virtual void voice_status( int entindex, bool b_talking ) = 0;

		// networked string table definitions have arrived, allow client .dll to
		//  hook string changes with a callback function ( see i_network_string_table_client.h )
		virtual void install_string_table_callback( const char* table_name ) = 0;

		// notification that we're moving into another stage during the frame.
		virtual void frame_stage_notify( client_frame_stage_t cur_stage ) = 0;

		// the engine has received the specified user message, this code is used to dispatch the message handler
		virtual bool dispatch_user_message( int msg_type, bf_read& msg_data ) = 0;

		// save/restore system hooks
		virtual c_save_restore_data* save_init( int size )                                                              = 0;
		virtual void save_write_fields( c_save_restore_data*, const char*, void*, datamap_t*, typedescription_t*, int ) = 0;
		virtual void save_read_fields( c_save_restore_data*, const char*, void*, datamap_t*, typedescription_t*, int )  = 0;
		virtual void pre_save( c_save_restore_data* )                                                                   = 0;
		virtual void save( c_save_restore_data* )                                                                       = 0;
		virtual void write_save_headers( c_save_restore_data* )                                                         = 0;
		virtual void read_restore_headers( c_save_restore_data* )                                                       = 0;
		virtual void restore( c_save_restore_data*, bool )                                                              = 0;
		virtual void dispatch_on_restore( )                                                                             = 0;

		// hand over the standard_recv_proxies in the client dll's module.
		virtual c_standard_recv_proxies* get_standard_recv_proxies( ) = 0;

		// save game screenshot writing
		virtual void write_save_game_screenshot( const char* p_filename ) = 0;

		// given a list of "s(wavname) s(wavname2)" tokens, look up the localized text and emit
		//  the appropriate close caption if running with closecaption = 1
		virtual void emit_sentence_close_caption( const char* tokenstream ) = 0;
		// emits a regular close caption by token name
		virtual void emit_close_caption( const char* captionname, float duration ) = 0;

		// returns true if the client can start recording a demo now.  if the client returns false,
		// an error message of up to length bytes should be returned in error_msg.
		virtual bool can_record_demo( char* error_msg, int length ) const = 0;

		// give the client a chance to do setup/cleanup.
		virtual void on_demo_record_start( const char* p_demo_base_name )   = 0;
		virtual void on_demo_record_stop( )                                 = 0;
		virtual void on_demo_playback_start( const char* p_demo_base_name ) = 0;
		virtual void on_demo_playback_stop( )                               = 0;

		// draw the console overlay?
		virtual bool should_draw_dropdown_console( ) = 0;

		// get client screen dimensions
		virtual int get_screen_width( )  = 0;
		virtual int get_screen_height( ) = 0;

		// added interface

		// save game screenshot writing
		virtual void write_save_game_screenshot_of_size( const char* p_filename, int width, int height, bool b_create_power_of2_padded = false,
		                                                 bool b_write_vtf = false ) = 0;

		// gets the current view
		virtual bool get_player_view( c_view_setup& player_view ) = 0;

		// matchmaking
		virtual void setup_game_properties( void*& contexts, void*& properties )                                     = 0;
		virtual unsigned int get_presence_id( const char* p_id_name )                                                = 0;
		virtual const char* get_property_id_string( unsigned int id )                                                = 0;
		virtual void get_property_display_string( unsigned int id, unsigned int value, char* p_output, int n_bytes ) = 0;

		virtual void start_stats_reporting( void* handle, bool b_arbitrated ) = 0;

		virtual void invalidate_mdl_cache( ) = 0;

		virtual void in_set_sample_time( float frametime ) = 0;

		// for sv_pure mode. the filesystem figures out which files the client needs to reload to be "pure" ala the server's preferences.
		virtual void reload_files_in_list( i_file_list* p_files_to_reload ) = 0;

		// let the client handle ui toggle - if this function returns false, the ui will toggle, otherwise it will not.
		virtual bool handle_ui_toggle( ) = 0;

		// allow the console to be shown?
		virtual bool should_allow_console( ) = 0;

		// get renamed recv tables
		virtual c_renamed_recv_table_info* get_renamed_recv_table_infos( ) = 0;

		// get the mouthinfo for the sound being played inside ui panels
		virtual c_mouth_info* get_client_ui_mouth_info( ) = 0;

		// notify the client that a file has been received from the game server
		virtual void file_received( const char* file_name, unsigned int transfer_id ) = 0;

		virtual const char* translate_effect_for_vision_filter( const char* pch_effect_type, const char* pch_effect_name ) = 0;

		// give the client a chance to modify sound settings however they want before the sound plays. this is used for
		// things like adjusting pitch of voice lines in pyroland in tf2.
		virtual void client_adjust_start_sound_params( struct start_sound_params_t& params ) = 0;

		// returns true if the disconnect command has been handled by the client
		virtual bool disconnect_attempt( void ) = 0;

		virtual bool is_connected_user_info_change_allowed( i_con_var* p_cvar ) = 0;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_BASE_CLIENT_DLL_HPP
