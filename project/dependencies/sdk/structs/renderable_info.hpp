#ifndef WEDNESDAY_WTF_RENDERABLE_INFO_HPP
#define WEDNESDAY_WTF_RENDERABLE_INFO_HPP

#include "i_client_renderable.hpp"

namespace sdk
{
	struct renderable_info {
	public:
		i_client_renderable* renderable;
		int render_frame; // which frame did I render it in?
		int render_frame_2;
		int enum_count; // Have I been added to a particular shadow yet?
		int translucency_calculated;
		unsigned int leaf_list;      // What leafs is it in?
		unsigned int render_leaf;    // What leaf do I render in?
		unsigned char flags;         // rendering flags
		unsigned char render_group;  // RenderGroup_t type
		unsigned short first_shadow; // The first shadow caster that cast on it
		short area;                  // -1 if the renderable spans multiple areas.
		signed char translucency_calculated_view;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_RENDERABLE_INFO_HPP
