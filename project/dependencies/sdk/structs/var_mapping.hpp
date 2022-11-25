#ifndef WEDNESDAY_WTF_VAR_MAPPING_HPP
#define WEDNESDAY_WTF_VAR_MAPPING_HPP

#include "var_map_entry.hpp"

namespace sdk
{
	struct var_mapping {
	public:
		var_map_entry* entries;

		int interpolated_entries;
		float last_interpolation_time;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_VAR_MAPPING_HPP
