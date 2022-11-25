//
// Created by Liga on 2/26/2022.
//

#ifndef WEDNESDAY_WTF_CLIENT_FRAME_STAGE_HPP
#define WEDNESDAY_WTF_CLIENT_FRAME_STAGE_HPP

namespace sdk
{
	enum client_frame_stage {
		frame_undefined = -1,
		// (haven't run any frames yet)
		frame_start,

		// a network packet is being recieved
		frame_net_update_start,
		// data has been received and we're going to start calling postdataupdate
		frame_net_update_postdataupdate_start,
		// data has been received and we've called postdataupdate on all data recipients
		frame_net_update_postdataupdate_end,
		// we've received all packets, we can now do interpolation, prediction, etc..
		frame_net_update_end,

		// we're about to start rendering the scene
		frame_render_start,
		// we've finished rendering the scene.
		frame_render_end
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_CLIENT_FRAME_STAGE_HPP
