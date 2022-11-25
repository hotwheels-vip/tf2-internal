#ifndef WEDNESDAY_WTF_I_HAS_OWNER_HPP
#define WEDNESDAY_WTF_I_HAS_OWNER_HPP

#include "c_base_entity.hpp"

namespace sdk
{
	struct i_has_owner {
	public:
		virtual c_base_entity* get_owner_via_interface( ) = 0;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_HAS_OWNER_HPP
