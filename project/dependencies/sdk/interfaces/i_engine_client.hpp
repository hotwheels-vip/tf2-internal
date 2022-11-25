//
// Created by Liga on 2/23/2022.
//

#ifndef WEDNESDAY_WTF_I_ENGINE_CLIENT_HPP
#define WEDNESDAY_WTF_I_ENGINE_CLIENT_HPP

#include <iostream>

#include "../structs/color.hpp"
#include "../structs/matrix.hpp"
#include "../structs/qangle.hpp"
#include "../structs/vector.hpp"
#include "i_net_channel.hpp"

namespace sdk
{
	struct model_t;
	struct i_material;
	struct player_info;
	struct key_values;

	struct i_material_system;

	struct i_engine_client {
	public:
		// find the model's surfaces that intersect the given sphere.
		// returns the number of surfaces filled in.
		virtual int get_intersecting_surfaces( const model_t* model, const vector& v_center, const float radius,
		                                       const bool b_only_visible_surfaces, // only return surfaces visible to v_center.
		                                       void* p_infos, const int n_max_infos ) = 0;

		// get the lighting intensivty for a specified point
		// if b_clamp is specified, the resulting vector is restricted to the 0.0 to 1.0 for each element
		virtual vector get_light_for_point( const vector& pos, bool b_clamp ) = 0;

		// traces the line and reports the material impacted as well as the lighting information for the impact point
		virtual i_material* trace_line_material_and_lighting( const vector& start, const vector& end, vector& diffuse_light_color,
		                                                      vector& base_color ) = 0;

		// given an input text buffer data pointer, parses a single token into the variable token and returns the new
		//  reading position
		virtual const char* parse_file( const char* data, char* token, int maxlen ) = 0;
		virtual bool copy_local_file( const char* source, const char* destination ) = 0;

		// gets the dimensions of the game window
		virtual void get_screen_size( int& width, int& height ) = 0;

		// forwards sz_cmd_string to the server, sent reliably if b_reliable is set
		virtual void server_cmd( const char* sz_cmd_string, bool b_reliable = true ) = 0;
		// inserts sz_cmd_string into the command buffer as if it was typed by the client to his/her console.
		// note: calls to this are checked against fcvar_clientcmd_can_execute (if that bit is not set, then this function can't change it).
		//       call client_cmd_unrestricted to have access to fcvar_clientcmd_can_execute vars.
		virtual void client_cmd( const char* sz_cmd_string ) = 0;

		// fill in the player info structure for the specified player index (name, model, etc.)
		virtual bool get_player_info( int ent_num, player_info* pinfo ) = 0;

		// retrieve the player entity number for a specified user_id
		virtual int get_player_for_user_id( int user_id ) = 0;

		// retrieves text message system information for the specified message by name
		virtual void* text_message_get( const char* p_name ) = 0;

		// returns true if the console is visible
		virtual bool con_is_visible( void ) = 0;

		// get the entity index of the local player
		virtual int get_local_player( void ) = 0;

		// client dll is hooking a model, loads the model into memory and returns  pointer to the model_t
		virtual const model_t* load_model( const char* p_name, bool b_prop = false ) = 0;

		// get accurate, sub-frame clock ( profiling use )
		virtual float time( void ) = 0;

		// get the exact server timesstamp ( server time ) from the last message received from the server
		virtual float get_last_time_stamp( void ) = 0;

		// given a void (opaque pointer), retrieve the underlying void object ( stores the words, phonemes, and close
		//  captioning data )
		virtual void* get_sentence( void* p_audio_source ) = 0;
		// given a void, determines the length of the underlying audio file (.wav, .mp3, etc.)
		virtual float get_sentence_length( void* p_audio_source ) = 0;
		// returns true if the sound is streaming off of the hard disk (instead of being memory resident)
		virtual bool is_streaming( void* p_audio_source ) const = 0;

		// copy current view orientation into va
		virtual void get_view_angles( qangle& va ) = 0;
		// set current view orientation from va
		virtual void set_view_angles( qangle& va ) = 0;

		// retrieve the current game's maxclients setting
		virtual int get_max_clients( void ) = 0;

		// given the string p_binding which may be bound to a key,
		//  returns the string name of the key to which this string is bound. returns null if no such binding exists
		virtual const char* key_lookup_binding( const char* p_binding ) = 0;

		// given the name of the key "mouse1", "e", "tab", etc., return the string it is bound to "+jump", "impulse 50", etc.
		virtual const char* key_binding_for_key( void* code ) = 0;

		// key trapping (for binding keys)
		virtual void start_key_trap_mode( void )            = 0;
		virtual bool check_done_key_trapping( void*& code ) = 0;

		// returns true if the player is fully connected and active in game (i.e, not still loading)
		virtual bool is_in_game( void ) = 0;
		// returns true if the player is connected, but not necessarily active in game (could still be loading)
		virtual bool is_connected( void ) = 0;
		// returns true if the loading plaque should be drawn
		virtual bool is_drawing_loading_image( void ) = 0;

		// prints the formatted string to the notification area of the screen ( down the right hand edge
		//  numbered lines starting at position 0
		virtual void con_n_printf( int pos, const char* fmt, ... ) = 0;
		// similar to con_n_printf, but allows specifying custom text color and duration information
		virtual void con_nx_printf( const struct con_nprint_s* info, const char* fmt, ... ) = 0;

		// is the specified world-space bounding box inside the view frustum?
		virtual int is_box_visible( const vector& mins, const vector& maxs ) = 0;

		// is the specified world-space boudning box in the same pvs cluster as the view origin?
		virtual int is_box_in_view_cluster( const vector& mins, const vector& maxs ) = 0;

		// returns true if the specified box is outside of the view frustum and should be culled
		virtual bool cull_box( const vector& mins, const vector& maxs ) = 0;

		// allow the sound system to paint additional data (during lengthy rendering operations) to prevent stuttering sound.
		virtual void sound_extra_update( void ) = 0;

		// get the current game directory ( e.g., hl2, tf2, cstrike, hl1 )
		virtual const char* get_game_directory( void ) = 0;

		// get access to the world to screen transformation matrix
		virtual const view_matrix& world_to_screen_matrix( ) = 0;

		// get the matrix to move a point from world space into view space
		// (translate and rotate so the camera is at the origin looking down x).
		virtual const view_matrix& world_to_view_matrix( ) = 0;

		// the .bsp file can have mod-specified data lumps. these ap_is are for working with such game lumps.

		// get mod-specified lump version id for the specified game data lump
		virtual int game_lump_version( int lump_id ) const = 0;
		// get the raw size of the specified game data lump.
		virtual int game_lump_size( int lump_id ) const = 0;
		// loads a game lump off disk, writing the data into the buffer pointed to bye p_buffer
		// returns false if the data can't be read or the destination buffer is too small
		virtual bool load_game_lump( int lump_id, void* p_buffer, int size ) = 0;

		// returns the number of leaves in the level
		virtual int level_leaf_count( ) const = 0;

		// gets a way to perform spatial queries on the bsp tree
		virtual void* get_bsp_tree_query( ) = 0;

		// convert texlight to gamma...
		virtual void linear_to_gamma( float* linear, float* gamma ) = 0;

		// get the lightstyle value
		virtual float light_style_value( int style ) = 0;

		// computes light due to dynamic lighting at a point
		// if the normal isn't specified, then it'll return the maximum lighting
		virtual void compute_dynamic_lighting( const vector& pt, const vector* p_normal, vector& color ) = 0;

		// returns the color of the ambient light
		virtual void get_ambient_light_color( vector& color ) = 0;

		// returns the dx support level
		virtual int get_dx_support_level( ) = 0;

		// gr - returns the hdr support status
		virtual bool supports_hdr( ) = 0;

		// replace the engine's material system pointer.
		virtual void mat_stub( i_material_system* p_mat_sys ) = 0;

		// get the name of the current map
		virtual void get_chapter_name( char* pch_buff, int i_max_length ) = 0;
		virtual char const* get_level_name( void )                        = 0;
		virtual int get_level_version( void )                             = 0;

		virtual struct i_voice_tweak_s* get_voice_tweak_api( void ) = 0;

		// tell engine stats gathering system that the rendering frame is beginning/ending
		virtual void engine_stats_begin_frame( void ) = 0;
		virtual void engine_stats_end_frame( void )   = 0;

		// this tells the engine to fire any events (temp entity messages) that it has queued up this frame.
		// it should only be called once per frame.
		virtual void fire_events( ) = 0;

		// returns an area index if all the leaves are in the same area. if they span multple areas, then it returns -1.
		virtual int get_leaves_area( int* p_leaves, int n_leaves ) = 0;

		// returns true if the box touches the specified area's frustum.
		virtual bool does_box_touch_area_frustum( const vector& mins, const vector& maxs, int i_area ) = 0;

		// sets the hearing origin (i.e., the origin and orientation of the listener so that the sound system can spatialize
		//  sound appropriately ).
		virtual void set_audio_state( const void*& state ) = 0;

		// sentences / sentence groups
		virtual int sentence_group_pick( int group_index, char* name, int name_buf_len )                                           = 0;
		virtual int sentence_group_pick_sequential( int group_index, char* name, int name_buf_len, int sentence_index, int reset ) = 0;
		virtual int sentence_index_from_name( const char* p_sentence_name )                                                        = 0;
		virtual const char* sentence_name_from_index( int sentence_index )                                                         = 0;
		virtual int sentence_group_index_from_name( const char* p_group_name )                                                     = 0;
		virtual const char* sentence_group_name_from_index( int group_index )                                                      = 0;
		virtual float sentence_length( int sentence_index )                                                                        = 0;

		// computes light due to dynamic lighting at a point
		// if the normal isn't specified, then it'll return the maximum lighting
		// if p_box_colors is specified (it's an array of 6), then it'll copy the light contribution at each box side.
		virtual void compute_lighting( const vector& pt, const vector* p_normal, bool b_clamp, vector& color, vector* p_box_colors ) = 0;

		// activates/deactivates an occluder...
		virtual void activate_occluder( int n_occluder_index, bool b_active )              = 0;
		virtual bool is_occluded( const vector& vec_abs_mins, const vector& vec_abs_maxs ) = 0;

		// the save restore system allocates memory from a shared memory pool, use this allocator to allocate/free saverestore
		//  memory.
		virtual void* save_alloc_memory( size_t num, size_t size ) = 0;
		virtual void save_free_memory( void* p_save_mem )          = 0;

		// returns info interface for client netchannel
		virtual i_net_channel_info* get_net_channel_info( void ) = 0;

		// debugging functionality:
		// very slow routine to draw a physics model
		virtual void debug_draw_phys_collide( const void* p_collide, i_material* p_material, matrix_3x4& transform, const color& color ) = 0;
		// this can be used to notify test scripts that we're at a particular spot in the code.
		virtual void check_point( const char* p_name ) = 0;
		// draw portals if r_draw_portals is set (debugging only)
		virtual void draw_portals( ) = 0;
		// determine whether the client is playing back or recording a demo
		virtual bool is_playing_demo( void )               = 0;
		virtual bool is_recording_demo( void )             = 0;
		virtual bool is_playing_time_demo( void )          = 0;
		virtual int get_demo_recording_tick( void )        = 0;
		virtual int get_demo_playback_tick( void )         = 0;
		virtual int get_demo_playback_start_tick( void )   = 0;
		virtual float get_demo_playback_time_scale( void ) = 0;
		virtual int get_demo_playback_total_ticks( void )  = 0;
		// is the game paused?
		virtual bool is_paused( void ) = 0;
		// is the game currently taking a screenshot?
		virtual bool is_taking_screenshot( void ) = 0;
		// is this a hltv broadcast ?
		virtual bool is_hltv( void ) = 0;
		// is this level loaded as just the background to the main menu? (active, but unplayable)
		virtual bool is_level_main_menu_background( void ) = 0;
		// returns the name of the background level
		virtual void get_main_menu_background_name( char* dest, int destlen ) = 0;

		// get video modes
		virtual void get_video_modes( int& n_count, void*& p_modes ) = 0;

		// occlusion system control
		virtual void set_occlusion_parameters( const void*& params ) = 0;

		// what language is the user expecting to hear .wavs in, "english" or another...
		virtual void get_ui_language( char* dest, int destlen ) = 0;

		// can skybox be seen from a particular point?
		virtual void* is_skybox_visible_from_point( const vector& vec_point ) = 0;

		// get the pristine map entity lump string.  (e.g., used by cs to reload the map entities when restarting a round.)
		virtual const char* get_map_entities_string( ) = 0;

		// is the engine in map edit mode ?
		virtual bool is_in_edit_mode( void ) = 0;

		// current screen aspect ratio (eg. 4.0f/3.0f, 16.0f/9.0f)
		virtual float get_screen_aspect_ratio( ) = 0;

		// allow the game ui to login a user
		virtual bool removed_steam_refresh_login( const char* password, bool is_secure ) = 0;
		virtual bool removed_steam_process_call( bool& finished )                        = 0;

		// allow other modules to know about engine versioning (one use is a proxy for network compatability)
		virtual unsigned int get_engine_build_number( )   = 0; // engines build
		virtual const char* get_product_version_string( ) = 0; // mods version number (steam.inf)

		// communicates to the color correction editor that it's time to grab the pre-color corrected frame
		// passes in the actual size of the viewport
		virtual void grab_pre_color_corrected_frame( int x, int y, int width, int height ) = 0;

		virtual bool is_hammer_running( ) const = 0;

		// inserts sz_cmd_string into the command buffer as if it was typed by the client to his/her console.
		// and then executes the command string immediately (vs client_cmd() which executes in the next frame)
		//
		// note: this is not checked against the fcvar_clientcmd_can_execute vars.
		virtual void execute_client_cmd( const char* sz_cmd_string ) = 0;

		// returns if the loaded map was processed with hdr info. this will be set regardless
		// of what hdr mode the player is in.
		virtual bool map_has_hdr_lighting( void ) = 0;

		virtual int get_app_id( ) = 0;

		// just get the leaf ambient light - no caching, no samples
		virtual vector get_light_for_point_fast( const vector& pos, bool b_clamp ) = 0;

		// this version does not check against fcvar_clientcmd_can_execute.
		virtual void client_cmd_unrestricted( const char* sz_cmd_string ) = 0;

		// this used to be accessible through the cl_restrict_server_commands cvar.
		// by default, valve games restrict the server to only being able to execute commands marked with fcvar_server_can_execute.
		// by default, mods are allowed to execute any server commands, and they can restrict the server's ability to execute client
		// commands with this function.
		virtual void set_restrict_server_commands( bool b_restrict ) = 0;

		// if set to true (defaults to true for valve games and false for others), then iv_engine_client::client_cmd
		// can only execute things marked with fcvar_clientcmd_can_execute.
		virtual void set_restrict_client_commands( bool b_restrict ) = 0;

		// sets the client renderable for an overlay's material proxy to bind to
		virtual void set_overlay_bind_proxy( int i_overlay_id, void* p_bind_proxy ) = 0;

		virtual bool copy_frame_buffer_to_material( const char* p_material_name ) = 0;

		// matchmaking
		virtual void change_team( const char* p_team_name ) = 0;

		// causes the engine to read in the user's configuration on disk
		virtual void read_configuration( const bool read_default = false ) = 0;

		virtual void set_achievement_mgr( void* p_achievement_mgr ) = 0;
		virtual void* get_achievement_mgr( )                        = 0;

		virtual bool map_load_failed( void )             = 0;
		virtual void set_map_load_failed( bool b_state ) = 0;

		virtual bool is_low_violence( )                                     = 0;
		virtual const char* get_most_recent_save_game( void )               = 0;
		virtual void set_most_recent_save_game( const char* lpsz_filename ) = 0;

		virtual void start_xbox_exiting_process( )               = 0;
		virtual bool is_save_in_progress( )                      = 0;
		virtual std::uint32_t on_storage_device_attached( void ) = 0;
		virtual void on_storage_device_detached( void )          = 0;

		virtual void reset_demo_interpolation( void ) = 0;

		// methods to set/get a gamestats data container so client & server running in same process can send combined data
		virtual void set_gamestats_data( void* p_gamestats_data ) = 0;
		virtual void* get_gamestats_data( )                       = 0;

		// sends a key values server command, not allowed from scripts execution
		// params:
		//	p_key_values	- key values to be serialized and sent to server
		//				  the pointer is deleted inside the function: p_key_values->delete_this()
		virtual void server_cmd_key_values( key_values* p_key_values ) = 0;

		virtual bool is_skipping_playback( void ) = 0;
		virtual bool is_loading_demo( void )      = 0;

		// returns true if the engine is playing back a "locally recorded" demo, which includes
		// both source_tv and replay demos, since they're recorded locally (on servers), as opposed
		// to a client recording a demo while connected to a remote server.
		virtual bool is_playing_demo_a_locally_recorded_demo( ) = 0;

		// given the string p_binding which may be bound to a key,
		//  returns the string name of the key to which this string is bound. returns null if no such binding exists
		// unlike key_lookup_binding, leading '+' characters are not stripped from bindings.
		virtual const char* key_lookup_binding_exact( const char* p_binding ) = 0;

		virtual void add_phoneme_file( const char* psz_phoneme_file ) = 0;
		virtual float get_paused_expire_time( void )                  = 0;

		virtual bool start_demo_recording( const char* psz_filename, const char* psz_folder ) = 0;
		virtual void stop_demo_recording( void )                                              = 0;
		virtual void take_screenshot( const char* psz_filename, const char* psz_folder )      = 0;

		virtual std::uint32_t get_protocol_version( ) = 0;
		virtual bool is_windowed_mode( )              = 0;

		// flash the window (os specific)
		virtual void flash_window( ) = 0;

		// client version from the steam.inf, this will be compared to the gc version
		virtual int get_client_version( ) const = 0; // engines build

		// is app active
		virtual bool is_active_app( ) = 0;

		virtual void disconnect_internal( ) = 0;

		virtual int get_instances_running_count( ) = 0;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_ENGINE_CLIENT_HPP
