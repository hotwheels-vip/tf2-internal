//
// Created by blanket on 2/26/2022.
//

#ifndef WEDNESDAY_WTF_I_MODEL_INFO_HPP
#define WEDNESDAY_WTF_I_MODEL_INFO_HPP

#include "../structs/qangle.hpp"
#include "../structs/studio_hdr.hpp"
#include "../structs/vector.hpp"

namespace sdk
{
	struct model_t;
	struct cplane_t;
	struct i_material;
	struct vcollide_t;
	struct c_utl_buffer;
	struct c_phys_collide;
	struct virtualmodel_t;
	struct i_client_renderable;
	struct i_model_load_callback;

	struct i_model_info {
	public:
		virtual ~i_model_info( void ) { }

		// returns model_t* pointer for a model given a precached or dynamic model index.
		virtual const model_t* get_model( int modelindex ) = 0;

		// returns index of model by name for precached or known dynamic models.
		// does not adjust reference count for dynamic models.
		virtual int get_model_index( const char* name ) const = 0;

		// returns name of model
		virtual const char* get_model_name( const model_t* model ) const                               = 0;
		virtual vcollide_t* get_v_collide( const model_t* model )                                      = 0;
		virtual vcollide_t* get_v_collide( int modelindex )                                            = 0;
		virtual void get_model_bounds( const model_t* model, vector& mins, vector& maxs ) const        = 0;
		virtual void get_model_render_bounds( const model_t* model, vector& mins, vector& maxs ) const = 0;
		virtual int get_model_frame_count( const model_t* model ) const                                = 0;
		virtual int get_model_type( const model_t* model ) const                                       = 0;
		virtual void* get_model_extra_data( const model_t* model )                                     = 0;
		virtual bool model_has_material_proxy( const model_t* model ) const                            = 0;
		virtual bool is_translucent( const model_t* model ) const                                      = 0;
		virtual bool is_translucent_two_pass( const model_t* model ) const                             = 0;
		virtual void recompute_translucency( const model_t* model, int n_skin, int n_body, void /*i_client_renderable*/* p_client_renderable,
		                                     float f_instance_alpha_modulate = 1.0f )                  = 0;
		virtual int get_model_material_count( const model_t* model ) const                             = 0;
		virtual void get_model_materials( const model_t* model, int count, i_material** pp_material )  = 0;
		virtual bool is_model_vertex_lit( const model_t* model ) const                                 = 0;
		virtual const char* get_model_key_value_text( const model_t* model )                           = 0;
		virtual bool get_model_key_value( const model_t* model, c_utl_buffer& buf )                    = 0; // supports keyvalue blocks in submodels
		virtual float get_model_radius( const model_t* model )                                         = 0;

		virtual const studio_hdr_t* find_model( const studio_hdr_t* p_studio_hdr, void** cache, const char* modelname ) const = 0;
		virtual const studio_hdr_t* find_model( void* cache ) const                                                           = 0;
		virtual virtualmodel_t* get_virtual_model( const studio_hdr_t* p_studio_hdr ) const                                   = 0;
		virtual unsigned char* get_anim_block( const studio_hdr_t* p_studio_hdr, int i_block ) const                          = 0;

		// available on client only!!!
		virtual void get_model_material_color_and_lighting( const model_t* model, const vector& origin, const qangle& angles, void* p_trace,
		                                                    vector& lighting, vector& mat_color ) = 0;
		virtual void get_illumination_point( const model_t* model, i_client_renderable* p_renderable, const vector& origin, const qangle& angles,
		                                     vector* p_lighting_center )                          = 0;

		virtual int get_model_contents( int model_index )                 = 0;
		virtual studio_hdr_t* get_studio_model( const model_t* mod )      = 0;
		virtual int get_model_sprite_width( const model_t* model ) const  = 0;
		virtual int get_model_sprite_height( const model_t* model ) const = 0;

		// sets/gets a map-specified fade range (client only)
		virtual void set_level_screen_fade_range( float fl_min_size, float fl_max_size )       = 0;
		virtual void get_level_screen_fade_range( float* p_min_area, float* p_max_area ) const = 0;

		// sets/gets a map-specified per-view fade range (client only)
		virtual void set_view_screen_fade_range( float fl_min_size, float fl_max_size ) = 0;

		// computes fade alpha based on distance fade + screen fade (client only)
		virtual unsigned char compute_level_screen_fade( const vector& vec_abs_origin, float fl_radius, float fl_fade_scale ) const = 0;
		virtual unsigned char compute_view_screen_fade( const vector& vec_abs_origin, float fl_radius, float fl_fade_scale ) const  = 0;

		// both client and server
		virtual int get_autoplay_list( const studio_hdr_t* p_studio_hdr, unsigned short** p_autoplay_list ) const = 0;

		// gets a virtual terrain collision model (creates if necessary)
		// note: this may return null if the terrain model cannot be virtualized
		virtual c_phys_collide* get_collide_for_virtual_terrain( int index ) = 0;

		virtual bool is_using_fb_texture( const model_t* model, int n_skin, int n_body, void /*i_client_renderable*/* p_client_renderable ) const = 0;

		// obsolete methods. these are left in to maintain binary compatibility with clients using the i_model_info old version.
		virtual const model_t* find_or_load_model( const char* name );
		virtual void init_dynamic_models( );
		virtual void shutdown_dynamic_models( );
		virtual void add_dynamic_model( const char* name, int n_model_index = -1 );
		virtual void reference_model( int modelindex );
		virtual void unreference_model( int modelindex );
		virtual void cleanup_dynamic_models( bool b_force = false );

		virtual mdl_handle_t get_cache_handle( const model_t* model ) const = 0;

		// returns planes of non-nodraw brush model surfaces
		virtual int get_brush_model_plane_count( const model_t* model ) const                                            = 0;
		virtual void get_brush_model_plane( const model_t* model, int n_index, cplane_t& plane, vector* p_origin ) const = 0;
		virtual int get_surfaceprops_for_virtual_terrain( int index )                                                    = 0;

		// poked by engine host system
		virtual void on_level_change( ) = 0;

		virtual int get_model_client_side_index( const char* name ) const = 0;

		// returns index of model by name, dynamically registered if not already known.
		virtual int register_dynamic_model( const char* name, bool b_client_side ) = 0;

		virtual bool is_dynamic_model_loading( int model_index ) = 0;

		virtual void add_ref_dynamic_model( int model_index ) = 0;
		virtual void release_dynamic_model( int model_index ) = 0;

		// registers callback for when dynamic model has finished loading.
		// automatically adds reference, pair with release_dynamic_model.
		virtual bool register_model_load_callback( int modelindex, i_model_load_callback* p_callback, bool b_call_immediately_if_loaded = true ) = 0;
		virtual void unregister_model_load_callback( int modelindex, i_model_load_callback* p_callback )                                         = 0;
	};
} // namespace sdk
#endif // WEDNESDAY_WTF_I_MODEL_INFO_HPP
