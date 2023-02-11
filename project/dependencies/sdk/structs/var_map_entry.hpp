#pragma once

namespace sdk
{
	struct var_map_entry {
	public:
		unsigned short type;

		bool needs_to_interpolate;

		void* data;
		void* watcher;
	};
} // namespace sdk
