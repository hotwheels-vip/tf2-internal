#ifndef WEDNESDAY_WTF_I_CLIENT_RENDERABLE_HPP
#define WEDNESDAY_WTF_I_CLIENT_RENDERABLE_HPP

#include "matrix.hpp"
#include "qangle.hpp"
#include "vector.hpp"

namespace sdk
{
	using client_render_handle_t  = unsigned int;
	using model_instance_handle_t = unsigned int;

	enum shadow_type_t;

	struct i_client_unknown;
	struct client_shadow_handle_t;
	struct model_t;
	struct ipvs_notify;

	struct i_client_renderable {
	public:
		// gets at the containing class...
		virtual i_client_unknown* get_i_client_unknown( ) = 0;

		// data accessors
		virtual const vector& get_render_origin( void )        = 0;
		virtual const qangle& get_render_angles( void )        = 0;
		virtual bool should_draw( void )                       = 0;
		virtual bool is_transparent( void )                    = 0;
		virtual bool uses_power_of_two_frame_buffer_texture( ) = 0;
		virtual bool uses_full_frame_buffer_texture( )         = 0;

		virtual client_shadow_handle_t get_shadow_handle( ) const = 0;

		// used by the leaf system to store its render handle.
		virtual client_render_handle_t& render_handle( ) = 0;

		// render baby!
		virtual const model_t* get_model( ) const = 0;
		virtual int draw_model( int flags )       = 0;

		// get the body parameter
		virtual int get_body( ) = 0;

		// determine alpha and blend amount for transparent objects based on render state info
		virtual void compute_fx_blend( ) = 0;
		virtual int get_fx_blend( void ) = 0;

		// determine the color modulation amount
		virtual void get_color_modulation( float* color ) = 0;

		// returns false if the entity shouldn't be drawn due to lod.
		// (note: this is no longer used/supported, but kept in the vtable for backwards compat)
		virtual bool lod_test( ) = 0;

		// call this to get the current bone transforms for the model.
		// current_time parameter will affect interpolation
		// n_max_bones specifies how many matrices p_bone_to_world_out can hold. (should be greater than or
		// equal to studiohdr_t::numbones. use maxstudiobones to be safe.)
		virtual bool setup_bones( matrix_3x4* p_bone_to_world_out, int n_max_bones, int bone_mask, float current_time ) = 0;

		virtual void setup_weights( const matrix_3x4* p_bone_to_world, int n_flex_weight_count, float* p_flex_weights,
		                            float* p_flex_delayed_weights ) = 0;
		virtual void do_animation_events( void )                    = 0;

		// return this if you want pvs notifications. see ipvs_notify for more info.
		// note: you must always return the same value from this function. if you don't,
		// undefined things will occur, and they won't be good.
		virtual ipvs_notify* get_pvs_notify_interface( ) = 0;

		// returns the bounds relative to the origin (render bounds)
		virtual void get_render_bounds( vector& mins, vector& maxs ) = 0;

		// returns the bounds as an aabb in worldspace
		virtual void get_render_bounds_worldspace( vector& mins, vector& maxs ) = 0;

		// these normally call through to get_render_angles/get_render_bounds, but some entities custom implement them.
		virtual void get_shadow_render_bounds( vector& mins, vector& maxs, shadow_type_t shadow_type ) = 0;

		// should this object be able to have shadows cast onto it?
		virtual bool should_receive_projected_textures( int flags ) = 0;

		// these methods return true if we want a per-renderable shadow cast direction + distance
		virtual bool get_shadow_cast_distance( float* p_dist, shadow_type_t shadow_type ) const        = 0;
		virtual bool get_shadow_cast_direction( vector* p_direction, shadow_type_t shadow_type ) const = 0;

		// other methods related to shadow rendering
		virtual bool is_shadow_dirty( )                = 0;
		virtual void mark_shadow_dirty( bool b_dirty ) = 0;

		// iteration over shadow hierarchy
		virtual i_client_renderable* get_shadow_parent( )  = 0;
		virtual i_client_renderable* first_shadow_child( ) = 0;
		virtual i_client_renderable* next_shadow_peer( )   = 0;

		// returns the shadow cast type
		virtual shadow_type_t shadow_cast_type( ) = 0;

		// create/get/destroy model instance
		virtual void create_model_instance( )                 = 0;
		virtual model_instance_handle_t get_model_instance( ) = 0;

		// returns the transform from render_origin/render_angles to world
		virtual const matrix_3x4& renderable_to_world_transform( ) = 0;

		// attachments
		virtual int lookup_attachment( const char* p_attachment_name )            = 0;
		virtual bool get_attachment( int number, vector& origin, qangle& angles ) = 0;
		virtual bool get_attachment( int number, matrix_3x4& matrix )             = 0;

		// rendering clip plane, should be 4 floats, return value of null indicates a disabled render clip plane
		virtual float* get_render_clip_plane( void ) = 0;

		// get the skin parameter
		virtual int get_skin( ) = 0;

		// is this a two-pass renderable?
		virtual bool is_two_pass( void ) = 0;

		virtual void on_threaded_draw_setup( ) = 0;

		virtual bool uses_flex_delayed_weights( ) = 0;

		virtual void record_tool_message( ) = 0;

		virtual bool ignores_z_buffer( void ) const = 0;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_CLIENT_RENDERABLE_HPP
