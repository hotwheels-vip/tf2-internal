#ifndef WEDNESDAY_WTF_I_CLIENT_MODE_HPP
#define WEDNESDAY_WTF_I_CLIENT_MODE_HPP

namespace sdk
{
	enum buttons;

	struct c_base_entity;
	struct c_base_player;
	struct c_view_setup;
	struct c_user_cmd;
	struct key_values;
	struct headtrack_movement_mode_t;

	class i_client_mode
	{
	public:
		virtual ~i_client_mode( ) { }

		virtual void init_viewport( )                                                                                                         = 0;
		virtual void init( )                                                                                                                  = 0;
		virtual void v_gui_shutdown( )                                                                                                        = 0;
		virtual void shutdown( )                                                                                                              = 0;
		virtual void enable( )                                                                                                                = 0;
		virtual void disable( )                                                                                                               = 0;
		virtual void layout( )                                                                                                                = 0;
		virtual unsigned int* get_viewport( )                                                                                                 = 0;
		virtual void* get_viewport_animation_controller( )                                                                                    = 0;
		virtual void process_input( bool b_active )                                                                                           = 0;
		virtual bool should_draw_detail_objects( )                                                                                            = 0;
		virtual bool should_draw_entity( c_base_entity* p_ent )                                                                               = 0;
		virtual bool should_draw_local_player( c_base_player* p_player )                                                                      = 0;
		virtual bool should_draw_particles( )                                                                                                 = 0;
		virtual bool should_draw_fog( void )                                                                                                  = 0;
		virtual void override_view( c_view_setup* p_setup )                                                                                   = 0;
		virtual int key_input( int down, buttons keynum, const char* psz_current_binding )                                                    = 0;
		virtual void start_message_mode( int i_message_mode_type )                                                                            = 0;
		virtual unsigned int* get_message_panel( )                                                                                            = 0;
		virtual void override_mouse_input( float* x, float* y )                                                                               = 0;
		virtual bool create_move( float fl_input_sample_time, c_user_cmd* cmd )                                                               = 0;
		virtual void level_init( const char* newmap )                                                                                         = 0;
		virtual void level_shutdown( void )                                                                                                   = 0;
		virtual bool should_draw_view_model( void )                                                                                           = 0;
		virtual bool should_draw_crosshair( void )                                                                                            = 0;
		virtual void adjust_engine_viewport( int& x, int& y, int& width, int& height )                                                        = 0;
		virtual void pre_render( c_view_setup* p_setup )                                                                                      = 0;
		virtual void post_render( void )                                                                                                      = 0;
		virtual void post_render_v_gui( )                                                                                                     = 0;
		virtual void activate_in_game_v_gui_context( unsigned int* p_panel )                                                                  = 0;
		virtual void deactivate_in_game_v_gui_context( )                                                                                      = 0;
		virtual float get_view_model_fov( void )                                                                                              = 0;
		virtual bool can_record_demo( char* error_msg, int length ) const                                                                     = 0;
		virtual void compute_vgui_res_conditions( key_values* pkv_conditions )                                                                = 0;
		virtual wchar_t* get_server_name( )                                                                                                   = 0;
		virtual void set_server_name( wchar_t* name )                                                                                         = 0;
		virtual wchar_t* get_map_name( )                                                                                                      = 0;
		virtual void set_map_name( wchar_t* name )                                                                                            = 0;
		virtual bool do_post_screen_space_effects( const c_view_setup* p_setup )                                                              = 0;
		virtual void display_replay_message( const char* p_localize_name, float fl_duration, bool b_urgent, const char* p_sound, bool b_dlg ) = 0;
		virtual void update( )                                                                                                                = 0;
		virtual bool should_blackout_around_hud( )                                                                                            = 0;
		virtual headtrack_movement_mode_t should_override_headtrack_control( )                                                                = 0;
		virtual bool is_info_panel_allowed( )                                                                                                 = 0;
		virtual void info_panel_displayed( )                                                                                                  = 0;
		virtual bool is_html_info_panel_allowed( )                                                                                            = 0;
		virtual void on_demo_record_start( const char* p_demo_base_name )                                                                     = 0;
		virtual void on_demo_record_stop( )                                                                                                   = 0;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_CLIENT_MODE_HPP
