#ifndef WEDNESDAY_WTF_C_VIEW_SETUP_HPP
#define WEDNESDAY_WTF_C_VIEW_SETUP_HPP

#include "../enums/stereo_eye.hpp"
#include "matrix.hpp"
#include "qangle.hpp"
#include "vector.hpp"

namespace sdk
{
	struct c_view_setup {
	public:
		// left side of view window
		int x;
		int unscaled_x;
		// top side of view window
		int y;
		int unscaled_y;
		// width of view window
		int width;
		int unscaled_width;
		// height of view window
		int height;
		// which eye are we rendering?
		stereo_eye stereo_eye;
		int unscaled_height;

		// the rest are only used by 3d views

		// orthographic projection?
		bool ortho;
		// view-space rectangle for ortho projection.
		float ortho_left;
		float ortho_top;
		float ortho_right;
		float ortho_bottom;

		// horizontal fov in degrees
		float fov;
		// horizontal fov in degrees for in-view model
		float fov_viewmodel;

		// 3d origin of camera
		vector origin;

		// heading of camera (pitch, yaw, roll)
		qangle angles;
		// local z coordinate of near plane of camera
		float z_near;
		// local z coordinate of far plane of camera
		float z_far;

		// local z coordinate of near plane of camera ( when rendering view model )
		float z_near_viewmodel;
		// local z coordinate of far plane of camera ( when rendering view model )
		float z_far_viewmodel;

		// set to true if this is to draw into a subrect of the larger screen
		// this really is a hack, but no more than the rest of the way this class is used
		bool render_to_subrect_of_larger_screen;

		// the aspect ratio to use for computing the perspective projection matrix
		// (0.0f means use the viewport)
		float aspect_ratio;

		// controls for off-center projection (needed for poster rendering)
		bool off_center;
		float off_center_top;
		float off_center_bottom;
		float off_center_left;
		float off_center_right;

		// control that the sfm needs to tell the engine not to do certain post-processing steps
		bool do_bloom_and_tone_mapping;

		// cached mode for certain full-scene per-frame varying state such as sun entity coverage
		bool cache_full_scene_state;

		// if using vr, the headset calibration will feed you a projection matrix per-eye.
		// this does not override the z range - that will be set up as normal (i.e. the values in this matrix will be ignored).
		bool view_to_projection_override;
		view_matrix view_to_projection;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_C_VIEW_SETUP_HPP
