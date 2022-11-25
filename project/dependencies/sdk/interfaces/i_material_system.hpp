#ifndef WEDNESDAY_WTF_I_MATERIAL_SYSTEM_HPP
#define WEDNESDAY_WTF_I_MATERIAL_SYSTEM_HPP

#include "../structs/c_tf_player.hpp"
#include "../structs/i_material.hpp"
#include "i_app_system.hpp"

namespace sdk
{
	using create_interface_fn = void* ( * )( const char* name, int* return_code );
	using init_return_val_t   = unsigned int;

	struct i_mesh;
	struct i_morph;
	struct i_shader;
	struct hdr_type_t;
	struct i_file_list;
	struct i_call_queue;
	struct light_desc_t;
	struct i_index_buffer;
	struct i_vertex_buffer;
	struct morph_weight_t;
	struct material_lock_t;
	struct deformation_base_t;
	struct flashlight_state_t;
	struct i_mat_render_context;
	struct material_fog_mode_t;
	struct material_cull_mode_t;
	struct i_texture_compositor;
	struct material_video_mode_t;
	struct material_matrix_mode_t;
	struct material_index_format_t;
	struct material_adapter_info_t;
	struct material_context_type_t;
	struct color_correction_handle_t;
	struct material_primitive_type_t;
	struct material_system_config_t;
	struct material_height_clip_mode_t;
	struct mode_change_callback_func_t;
	struct material_system_sort_info_t;
	struct material_buffer_restore_func_t;
	struct material_buffer_release_func_t;
	struct material_non_interactive_mode_t;
	struct occlusion_query_object_handle_t;
	struct i_material_system_hardware_config;
	struct i_async_texture_operation_receiver;
	struct material_system_hardware_identifier_t;
	struct i_material_proxy_factory;
	struct material_thread_mode_t;
	struct key_values;
	struct image_format;
	struct material_handle_t;
	struct i_texture;
	struct render_target_size_mode_t;
	struct material_render_target_depth_t;
	struct material_rt_depth_shared;
	struct textureflags_clamps;
	struct textureflags_clampt;

	struct i_material_system : public i_app_system {
	public:
		bool connect( void* factory )                                                                                                       = 0;
		void disconnect( )                                                                                                                  = 0;
		void* query_interface( const char* p_interface_name )                                                                               = 0;
		init_return_val init( )                                                                                                             = 0;
		void shutdown( )                                                                                                                    = 0;
		virtual create_interface_fn init( const char* p_shader_apidll, i_material_proxy_factory* p_material_proxy_factory,
		                                  create_interface_fn file_system_factory, create_interface_fn cvar_factory )                       = 0;
		virtual void set_shader_api( const char* p_shader_apidll )                                                                          = 0;
		virtual void set_adapter( int n_adapter, int n_flags )                                                                              = 0;
		virtual void mod_init( )                                                                                                            = 0;
		virtual void mod_shutdown( )                                                                                                        = 0;
		virtual void set_thread_mode( material_thread_mode_t mode, int n_service_thread = -1 )                                              = 0;
		virtual material_thread_mode_t get_thread_mode( )                                                                                   = 0;
		virtual bool is_render_thread_safe( )                                                                                               = 0;
		virtual void execute_queued( )                                                                                                      = 0;
		virtual i_material_system_hardware_config* get_hardware_config( const char* p_version, int* return_code )                           = 0;
		virtual bool update_config( bool b_force_update )                                                                                   = 0;
		virtual bool override_config( const material_system_config_t& config, bool b_force_update )                                         = 0;
		virtual const material_system_config_t& get_current_config_for_video_card( ) const                                                  = 0;
		virtual bool get_recommended_configuration_info( int n_dx_level, key_values* p_key_values )                                         = 0;
		virtual int get_display_adapter_count( ) const                                                                                      = 0;
		virtual int get_current_adapter( ) const                                                                                            = 0;
		virtual void get_display_adapter_info( int adapter, material_adapter_info_t& info ) const                                           = 0;
		virtual int get_mode_count( int adapter ) const                                                                                     = 0;
		virtual void get_mode_info( int adapter, int mode, material_video_mode_t& info ) const                                              = 0;
		virtual void add_mode_change_call_back( mode_change_callback_func_t func )                                                          = 0;
		virtual void get_display_mode( material_video_mode_t& mode ) const                                                                  = 0;
		virtual bool set_mode( void* hwnd, const material_system_config_t& config )                                                         = 0;
		virtual bool supports_msaa_mode( int n_msaa_mode )                                                                                  = 0;
		virtual const material_system_hardware_identifier_t& get_video_card_identifier( void ) const                                        = 0;
		virtual void spew_driver_info( ) const                                                                                              = 0;
		virtual void get_dx_level_defaults( uint32_t& max_dxlevel, uint32_t& recommended_dxlevel )                                          = 0;
		virtual void get_back_buffer_dimensions( int& width, int& height ) const                                                            = 0;
		virtual image_format get_back_buffer_format( ) const                                                                                = 0;
		virtual bool supports_hdr_mode( hdr_type_t n_hdr_modede )                                                                           = 0;
		virtual bool add_view( void* hwnd )                                                                                                 = 0;
		virtual void remove_view( void* hwnd )                                                                                              = 0;
		virtual void set_view( void* hwnd )                                                                                                 = 0;
		virtual void begin_frame( float frame_time )                                                                                        = 0;
		virtual void end_frame( )                                                                                                           = 0;
		virtual void flush( bool flush_hardware = false )                                                                                   = 0;
		virtual void swap_buffers( )                                                                                                        = 0;
		virtual void evict_managed_resources( )                                                                                             = 0;
		virtual void release_resources( void )                                                                                              = 0;
		virtual void reacquire_resources( void )                                                                                            = 0;
		virtual void add_release_func( material_buffer_release_func_t func )                                                                = 0;
		virtual void remove_release_func( material_buffer_release_func_t func )                                                             = 0;
		virtual void add_restore_func( material_buffer_restore_func_t func )                                                                = 0;
		virtual void remove_restore_func( material_buffer_restore_func_t func )                                                             = 0;
		virtual void reset_temp_hw_memory( bool b_exiting_level = false )                                                                   = 0;
		virtual void handle_device_lost( )                                                                                                  = 0;
		virtual int shader_count( ) const                                                                                                   = 0;
		virtual int get_shaders( int n_first_shader, int n_max_count, i_shader** pp_shader_list ) const                                     = 0;
		virtual int shader_flag_count( ) const                                                                                              = 0;
		virtual const char* shader_flag_name( int n_index ) const                                                                           = 0;
		virtual void get_shader_fallback( const char* p_shader_name, char* p_fallback_shader, int n_fallback_length )                       = 0;
		virtual i_material_proxy_factory* get_material_proxy_factory( )                                                                     = 0;
		virtual void set_material_proxy_factory( i_material_proxy_factory* p_factory )                                                      = 0;
		virtual void enable_editor_materials( )                                                                                             = 0;
		virtual void set_in_stub_mode( bool b_in_stub_mode )                                                                                = 0;
		virtual void debug_print_used_materials( const char* p_search_sub_string, bool b_verbose )                                          = 0;
		virtual void debug_print_used_textures( void )                                                                                      = 0;
		virtual void toggle_suppress_material( const char* p_material_name )                                                                = 0;
		virtual void toggle_debug_material( const char* p_material_name )                                                                   = 0;
		virtual bool using_fast_clipping( void )                                                                                            = 0;
		virtual int stencil_buffer_bits( void )                                                                                             = 0;
		virtual void suspend_texture_streaming( )                                                                                           = 0;
		virtual void resume_texture_streaming( )                                                                                            = 0;
		virtual void uncache_all_materials( )                                                                                               = 0;
		virtual void uncache_unused_materials( bool b_recompute_state_snapshots = false )                                                   = 0;
		virtual void cache_used_materials( )                                                                                                = 0;
		virtual void reload_textures( )                                                                                                     = 0;
		virtual void reload_materials( const char* p_sub_string = nullptr )                                                                 = 0;
		virtual i_material* create_material( const char* p_material_name, key_values* p_vmt_key_values )                                    = 0;
		virtual i_material* find_material( const char* p_material_name, const char* p_texture_group_name = nullptr, bool complain = true,
		                                   const char* p_complain_prefix = nullptr )                                                        = 0;
		virtual bool is_material_loaded( const char* p_material_name )                                                                      = 0;
		virtual material_handle_t first_material( ) const                                                                                   = 0;
		virtual material_handle_t next_material( material_handle_t h ) const                                                                = 0;
		virtual material_handle_t invalid_material( ) const                                                                                 = 0;
		virtual i_material* get_material( material_handle_t h ) const                                                                       = 0;
		virtual int get_num_materials( ) const                                                                                              = 0;
		virtual void set_async_texture_load_cache( void* h_file_cache )                                                                     = 0;
		virtual i_texture* find_texture( const char* p_texture_name, const char* p_texture_group_name, bool complain = true,
		                                 int n_additional_creation_flags = 0 )                                                              = 0;
		virtual bool is_texture_loaded( const char* p_texture_name ) const                                                                  = 0;
		virtual i_texture* create_procedural_texture( const char* p_texture_name, const char* p_texture_group_name, int w, int h, image_format fmt,
		                                              int n_flags )                                                                         = 0;
		virtual void begin_render_target_allocation( )                                                                                      = 0;
		virtual void end_render_target_allocation( )                                                                                        = 0;
		virtual i_texture* create_render_target_texture( int w, int h, render_target_size_mode_t size_mode, image_format format,
		                                                 material_render_target_depth_t depth )                                             = 0;
		virtual i_texture* create_named_render_target_texture_ex( const char* p_rt_name, int w, int h, render_target_size_mode_t size_mode,
		                                                          image_format format, material_render_target_depth_t depth,
		                                                          unsigned int texture_flags, unsigned int render_target_flags )            = 0;
		virtual i_texture* create_named_render_target_texture( const char* p_rt_name, int w, int h, render_target_size_mode_t size_mode,
		                                                       image_format format, material_render_target_depth_t depth,
		                                                       bool b_clamp_tex_coords = true, bool b_auto_mip_map = false )                = 0;
		virtual i_texture* create_named_render_target_texture_ex2( const char* p_rt_name, int w, int h, render_target_size_mode_t size_mode,
		                                                           image_format format, material_render_target_depth_t depth,
		                                                           unsigned int texture_flags, unsigned int render_target_flags )           = 0;
		virtual void begin_lightmap_allocation( )                                                                                           = 0;
		virtual void end_lightmap_allocation( )                                                                                             = 0;
		virtual int allocate_lightmap( int width, int height, int offset_into_lightmap_page[ 2 ], i_material* p_material )                  = 0;
		virtual int allocate_white_lightmap( i_material* p_material )                                                                       = 0;
		virtual void update_lightmap( int lightmap_page_id, int lightmap_size[ 2 ], int offset_into_lightmap_page[ 2 ], float* p_float_image,
		                              float* p_float_image_bump1, float* p_float_image_bump2, float* p_float_image_bump3 )                  = 0;
		virtual int get_num_sort_i_ds( )                                                                                                    = 0;
		virtual void get_sort_info( material_system_sort_info_t* sort_info_array )                                                          = 0;
		virtual void get_lightmap_page_size( int lightmap, int* width, int* height ) const                                                  = 0;
		virtual void reset_material_lightmap_page_info( )                                                                                   = 0;
		virtual void clear_buffers( bool b_clear_color, bool b_clear_depth, bool b_clear_stencil = false )                                  = 0;
		virtual i_mat_render_context* get_render_context( )                                                                                 = 0;
		virtual bool supports_shadow_depth_textures( void )                                                                                 = 0;
		virtual void begin_update_lightmaps( void )                                                                                         = 0;
		virtual void end_update_lightmaps( void )                                                                                           = 0;
		virtual material_lock_t lock( )                                                                                                     = 0;
		virtual void unlock( material_lock_t )                                                                                              = 0;
		virtual image_format get_shadow_depth_texture_format( )                                                                             = 0;
		virtual bool supports_fetch4( void )                                                                                                = 0;
		virtual i_mat_render_context* create_render_context( material_context_type_t type )                                                 = 0;
		virtual i_mat_render_context* set_render_context( i_mat_render_context* )                                                           = 0;
		virtual bool supports_csaa_mode( int n_num_samples, int n_quality_level )                                                           = 0;
		virtual void remove_mode_change_call_back( mode_change_callback_func_t func )                                                       = 0;
		virtual i_material* find_procedural_material( const char* p_material_name, const char* p_texture_group_name,
		                                              key_values* p_vmt_key_values )                                                        = 0;
		virtual image_format get_null_texture_format( )                                                                                     = 0;
		virtual void add_texture_alias( const char* p_alias, const char* p_real_name )                                                      = 0;
		virtual void remove_texture_alias( const char* p_alias )                                                                            = 0;
		virtual int allocate_dynamic_lightmap( int lightmap_size[ 2 ], int* p_out_offset_into_page, int frame_id )                          = 0;
		virtual void set_excluded_textures( const char* p_script_name )                                                                     = 0;
		virtual void update_excluded_textures( void )                                                                                       = 0;
		virtual bool is_in_frame( ) const                                                                                                   = 0;
		virtual void compact_memory( )                                                                                                      = 0;
		virtual void reload_files_in_list( i_file_list* p_files_to_reload )                                                                 = 0;
		virtual bool allow_threading( bool b_allow, int n_service_thread )                                                                  = 0;
		virtual i_material* find_material_ex( const char* p_material_name, const char* p_texture_group_name, int n_context, bool complain = true,
		                                      const char* p_complain_prefix = nullptr )                                                     = 0;
		virtual void set_render_target_frame_buffer_size_overrides( int n_width, int n_height )                                             = 0;
		virtual void get_render_target_frame_buffer_dimensions( int& n_width, int& n_height )                                               = 0;
		virtual char* get_display_device_name( ) const                                                                                      = 0;
		virtual i_texture* create_texture_from_bits( int w, int h, int mips, image_format fmt, int src_buffer_size, uint8_t* src_bits )     = 0;
		virtual void override_render_target_allocation( bool rt_alloc )                                                                     = 0;
		virtual i_texture_compositor* new_texture_compositor( int w, int h, const char* p_composite_name, int n_team_num, uint64_t random_seed,
		                                                      key_values* stage_desc, uint32_t tex_composite_create_flags = 0 )             = 0;
		virtual void async_find_texture( const char* p_filename, const char* p_texture_group_name, i_async_texture_operation_receiver* p_recipient,
		                                 void* p_extra_args, bool b_complain = true, int n_additional_creation_flags = 0 )                  = 0;
		virtual i_texture* create_named_texture_from_bits_ex( const char* p_name, const char* p_texture_group_name, int w, int h, int mips,
		                                                      image_format fmt, int src_buffer_size, uint8_t* src_bits, int n_flags )       = 0;
		virtual bool add_texture_compositor_template( const char* p_name, key_values* p_tmpl_desc, int n_tex_composite_template_flags = 0 ) = 0;
		virtual bool verify_texture_compositor_templates( )                                                                                 = 0;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_MATERIAL_SYSTEM_HPP
