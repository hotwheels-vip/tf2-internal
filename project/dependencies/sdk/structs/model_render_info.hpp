#ifndef WEDNESDAY_WTF_MODEL_RENDER_INFO_HPP
#define WEDNESDAY_WTF_MODEL_RENDER_INFO_HPP

#include "c_tf_player.hpp"

namespace sdk
{
	struct model_render_info {
	public:
		vector origin;
		qangle angles;
		i_client_renderable* renderable;
		const model_t* model;
		const matrix_3x4* model_to_world;
		const matrix_3x4* lighting_offset;
		const vector* lighting_origin;
		int flags;
		int entity_index;
		int skin;
		int body;
		int hitbox_set;
		model_instance_handle_t instance;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_MODEL_RENDER_INFO_HPP
