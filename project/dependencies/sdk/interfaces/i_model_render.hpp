#ifndef WEDNESDAY_WTF_I_MODEL_RENDER_HPP
#define WEDNESDAY_WTF_I_MODEL_RENDER_HPP

#include "../structs/c_tf_player.hpp"
#include "../structs/color.hpp"
#include "../structs/i_material.hpp"
#include "../structs/model_render_info.hpp"
#include "i_engine_trace.hpp"

namespace sdk
{
	using light_cache_handle_t = unsigned int;

	enum draw_model_state_t;

	struct c_studio_hdr;
	struct draw_model_info_t;
	struct static_prop_render_info_t;
	struct override_type_t; // ????

	struct i_model_render {
	public:
		virtual int draw_model( int flags, i_client_renderable* p_renderable, model_instance_handle_t instance, int entity_index,
		                        const model_t* model, const vector& origin, const qangle& angles, int skin, int body, int hitboxset,
		                        const matrix_3x4* model_to_world = nullptr, const matrix_3x4* p_lighting_offset = nullptr ) = 0;

		// this causes a material to be used when rendering the model instead
		// of the materials the model was compiled with
		virtual void forced_material_override( i_material* new_material, int n_override_type = 0 ) = 0;

		virtual void set_view_target( const c_studio_hdr* p_studio_hdr, int n_body_index, const vector& target ) = 0;

		// creates, destroys instance data to be associated with the model
		virtual model_instance_handle_t create_instance( i_client_renderable* p_renderable, light_cache_handle_t* p_cache = nullptr ) = 0;
		virtual void destroy_instance( model_instance_handle_t handle )                                                               = 0;

		// associates a particular lighting condition with a model instance handle.
		// fixme: this feature currently only works for static props. to make it work for entities, etc.,
		// we must clean up the lightcache handles as the model instances are removed.
		// at the moment, since only the static prop manager uses this, it cleans up all light_cache_handles
		// at level shutdown.
		virtual void set_static_lighting( model_instance_handle_t handle, light_cache_handle_t* p_handle ) = 0;
		virtual light_cache_handle_t get_static_lighting( model_instance_handle_t handle )                 = 0;

		// moves an existing instance_handle to a nex renderable to keep decals etc. models must be the same
		virtual bool change_instance( model_instance_handle_t handle, i_client_renderable* p_renderable ) = 0;

		// creates a decal on a model instance by doing a planar projection
		// along the ray. the material is the decal material, the radius is the
		// radius of the decal to create.
		virtual void add_decal( model_instance_handle_t handle, const ray_t& ray, const vector& decal_up, int decal_index, int body,
		                        bool no_poke_thru, int max_lod_to_decal ) = 0;

		// removes all the decals on a model instance
		virtual void remove_all_decals( model_instance_handle_t handle ) = 0;

		// remove all decals from all models
		virtual void remove_all_decals_from_all_models( ) = 0;

		// shadow rendering, draw_model_shadow_setup returns the address of the bone-to-world array, null in case of error
		virtual matrix_3x4* draw_model_shadow_setup( i_client_renderable* p_renderable, int body, int skin, draw_model_info_t* p_info,
		                                             matrix_3x4* p_custom_bone_to_world = nullptr ) = 0;
		virtual void draw_model_shadow( i_client_renderable* p_renderable, const draw_model_info_t& info,
		                                matrix_3x4* p_custom_bone_to_world = nullptr )              = 0;

		// this gets called when overbright, etc gets changed to recompute static prop lighting.
		virtual bool recompute_static_lighting( model_instance_handle_t handle ) = 0;

		virtual void release_all_static_prop_color_data( void ) = 0;
		virtual void restore_all_static_prop_color_data( void ) = 0;

		// extended version of drawmodel
		virtual int draw_model_ex( model_render_info& p_info ) = 0;

		virtual int draw_model_ex_static_prop( model_render_info& p_info ) = 0;

		virtual bool draw_model_setup( model_render_info& p_info, draw_model_state_t* p_state, matrix_3x4* p_custom_bone_to_world,
		                               matrix_3x4** pp_bone_to_world_out )              = 0;
		virtual void draw_model_execute( const draw_model_state_t& state, const model_render_info& p_info,
		                                 matrix_3x4* p_custom_bone_to_world = nullptr ) = 0;

		// sets up lighting context for a point in space
		virtual void setup_lighting( const vector& vec_center ) = 0;

		// doesn't support any debug visualization modes or other model options, but draws static props in the
		// fastest way possible
		virtual int draw_static_prop_array_fast( static_prop_render_info_t* p_props, int count, bool b_shadow_depth ) = 0;

		// allow client to override lighting state
		virtual void suppress_engine_lighting( bool b_suppress ) = 0;

		virtual void setup_color_meshes( int n_total_verts ) = 0;

		virtual void add_colored_decal( model_instance_handle_t handle, const ray_t& ray, const vector& decal_up, int decal_index, int body,
		                                color c_color, bool no_poke_thru, int max_lod_to_decal ) = 0;

		virtual void get_material_override( i_material** pp_out_forced_material, override_type_t* p_out_override_type ) = 0;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_MODEL_RENDER_HPP
