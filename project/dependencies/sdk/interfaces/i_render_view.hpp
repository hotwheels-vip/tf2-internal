#ifndef WEDNESDAY_WTF_I_RENDER_VIEW_HPP
#define WEDNESDAY_WTF_I_RENDER_VIEW_HPP

#include "../structs/c_tf_player.hpp"
#include "../structs/color.hpp"

namespace sdk
{
	struct i_world_render_list;
	struct visible_fog_volume_info_t;
	struct world_list_info_t;
	struct vis_override_data_t;
	struct i_material;
	struct color_vec;
	struct i_brush_renderer;
	struct c_view_setup;
	struct i_texture;
	struct frustum;
	struct e_render_depth_mode;
	struct draw_brush_model_mode_t;

	struct i_render_view {
	public:
		// draw normal brush model.
		// if p_material_override is non-null, then all the faces of the bmodel will
		// set this material rather than their regular material.
		virtual void draw_brush_model( i_client_entity* baseentity, model_t* model, const vector& origin, const qangle& angles, bool b_unused ) = 0;

		// draw brush model that has no origin/angles change ( uses identity transform )
		// fixme, material proxy i_client_entity *baseentity is unused right now, use draw_brush_model for brushes with
		//  proxies for now.
		virtual void draw_identity_brush_model( i_world_render_list* p_list, model_t* model ) = 0;

		// mark this dynamic light as having changed this frame ( so light maps affected will be recomputed )
		virtual void touch_light( struct dlight_t* light ) = 0;
		// draw 3d overlays
		virtual void draw3d_debug_overlays( void ) = 0;
		// sets global blending fraction
		virtual void set_blend( float blend ) = 0;
		virtual float get_blend( void )       = 0;

		// sets global color modulation
#pragma warning( push )
#pragma warning( disable : 4244 )
		virtual void set_color_modulation( const float* blend ) = 0;

		void set_color_modulation( float r, float g, float b )
		{
			float buffer[ 3 ] = { r, g, b };
			set_color_modulation( buffer );
		}

		void set_color_modulation( color clr )
		{
			set_color_modulation( clr.r / 255.f, clr.g / 255.f, clr.b / 255.f );
		}
#pragma warning( pop )

		virtual void get_color_modulation( float* blend ) = 0;

		// wrap entire scene drawing
		virtual void scene_begin( void ) = 0;
		virtual void scene_end( void )   = 0;

		// gets the fog volume for a particular point
		virtual void get_visible_fog_volume( const vector& eye_point, visible_fog_volume_info_t* p_info ) = 0;

		// wraps world drawing
		// if i_force_view_leaf is not -1, then it uses the specified leaf as your starting area for setting up area portal culling.
		// this is used by water since your reflected view origin is often in solid space, but we still want to treat it as though
		// the first portal we're looking out of is a water portal, so our view effectively originates under the water.
		virtual i_world_render_list* create_world_list( ) = 0;

		virtual void build_world_lists( i_world_render_list* p_list, world_list_info_t* p_info, int i_force_f_view_leaf,
		                                const vis_override_data_t* p_vis_data = nullptr, bool b_shadow_depth = false,
		                                float* p_reflection_water_height = nullptr )                            = 0;
		virtual void draw_world_lists( i_world_render_list* p_list, unsigned long flags, float water_z_adjust ) = 0;

		// optimization for top view
		virtual void draw_top_view( bool enable )                              = 0;
		virtual void top_view_bounds( const vector& mins, const vector& maxs ) = 0;

		// draw lights
		virtual void draw_lights( void ) = 0;
		// fixme:  this function is a stub, doesn't do anything in the engine right now
		virtual void draw_mask_entities( void ) = 0;

		// draw surfaces with alpha
		virtual void draw_translucent_surfaces( i_world_render_list* p_list, int sort_index, unsigned long flags, bool b_shadow_depth ) = 0;

		// draw particles ( just draws the linefine for debugging map leaks )
		virtual void draw_line_file( void ) = 0;
		// draw lightmaps
		virtual void draw_lightmaps( i_world_render_list* p_list, int page_id ) = 0;
		// wraps view render sequence, sets up a view
		virtual void view_setup_vis( bool novis, int numorigins, const vector origin[] ) = 0;

		// return true if any of these leaves are visible in the current pvs.
		virtual bool are_any_leaves_visible( int* leaf_list, int n_leaves ) = 0;

		virtual void vgui_paint( void ) = 0;
		// sets up view fade parameters
		virtual void view_draw_fade( byte* color, i_material* p_material ) = 0;
		// sets up the projection matrix for the specified field of view
		virtual void old_set_projection_matrix( float fov, float z_near, float z_far ) = 0;
		// determine lighting at specified position
		virtual color_vec get_light_at_point( vector& pos ) = 0;
		// whose eyes are we looking through?
		virtual int get_view_entity( void ) = 0;
		// get engine field of view setting
		virtual float get_field_of_view( void ) = 0;
		// 1 == ducking, 0 == not
		virtual unsigned char** get_area_bits( void ) = 0;

		// set up fog for a particular leaf
		virtual void set_fog_volume_state( int n_visible_fog_volume, bool b_use_height_fog ) = 0;

		// installs a brush surface draw override method, null means use normal renderer
		virtual void install_brush_surface_renderer( i_brush_renderer* p_brush_renderer ) = 0;

		// draw brush model shadow
		virtual void draw_brush_model_shadow( i_client_renderable* p_renderable ) = 0;

		// does the leaf contain translucent surfaces?
		virtual bool leaf_contains_translucent_surfaces( i_world_render_list* p_list, int sort_index, unsigned long flags ) = 0;

		virtual bool does_box_intersect_water_volume( const vector& mins, const vector& maxs, int leaf_water_data_id ) = 0;

		virtual void set_area_state( unsigned char ch_area_bits[ 32 ], unsigned char ch_area_portal_bits[ 24 ] ) = 0;

		// see i
		virtual void v_gui_paint( int mode ) = 0;

		// push, pop views (see push_view_flags_t above for flags)
		virtual void push3d_view( const c_view_setup& view, int n_flags, i_texture* p_render_target, frustum frustum_planes ) = 0;
		virtual void push2d_view( const c_view_setup& view, int n_flags, i_texture* p_render_target, frustum frustum_planes ) = 0;
		virtual void pop_view( frustum frustum_planes )                                                                       = 0;

		// sets the main view
		virtual void set_main_view( const vector& vec_origin, const qangle& angles ) = 0;

		enum {
			view_setup_vis_ex_return_flags_uses_radial_vis = 0x00000001
		};

		// wraps view render sequence, sets up a view
		virtual void view_setup_vis_ex( bool novis, int numorigins, const vector origin[], unsigned int& return_flags ) = 0;

		// replaces the current view frustum with a rhyming replacement of your choice
		virtual void override_view_frustum( frustum custom ) = 0;

		virtual void draw_brush_model_shadow_depth( i_client_entity* baseentity, model_t* model, const vector& origin, const qangle& angles,
		                                            e_render_depth_mode depth_mode )                                                = 0;
		virtual void update_brush_model_lightmap( model_t* model, i_client_renderable* p_renderable )                               = 0;
		virtual void begin_update_lightmaps( void )                                                                                 = 0;
		virtual void end_update_lightmaps( void )                                                                                   = 0;
		virtual void old_set_off_center_projection_matrix( float fov, float z_near, float z_far, float fl_aspect_ratio, float fl_bottom, float fl_top,
		                                                   float fl_left, float fl_right )                                          = 0;
		virtual void old_set_projection_matrix_ortho( float left, float top, float right, float bottom, float z_near, float z_far ) = 0;
		virtual void push3d_view( const c_view_setup& view, int n_flags, i_texture* p_render_target, frustum frustum_planes,
		                          i_texture* p_depth_texture )                                                                      = 0;
		virtual void get_matrices_for_view( const c_view_setup& view, view_matrix* p_world_to_view, view_matrix* p_view_to_projection,
		                                    view_matrix* p_world_to_projection, view_matrix* p_world_to_pixels )                    = 0;
		virtual void draw_brush_model_ex( i_client_entity* baseentity, model_t* model, const vector& origin, const qangle& angles,
		                                  draw_brush_model_mode_t mode )                                                            = 0;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_RENDER_VIEW_HPP
