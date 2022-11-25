#ifndef WEDNESDAY_WTF_I_CLIENT_LEAF_SYSTEM_HPP
#define WEDNESDAY_WTF_I_CLIENT_LEAF_SYSTEM_HPP

#include "../structs/renderable_info.hpp"

namespace sdk
{
	struct i_client_leaf_system {
	public:
		renderable_info* get_info_by_handle( client_render_handle_t handle )
		{
			auto leaf_list   = reinterpret_cast< std::uintptr_t* >( this ) + 0x8;
			auto render_info = reinterpret_cast< renderable_info* >( *leaf_list + 0x28 * handle );

			return render_info;
		}
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_CLIENT_LEAF_SYSTEM_HPP
