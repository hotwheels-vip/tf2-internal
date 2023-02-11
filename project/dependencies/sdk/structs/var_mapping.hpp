#pragma once

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
