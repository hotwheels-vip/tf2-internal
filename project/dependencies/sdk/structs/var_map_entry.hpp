#ifndef WEDNESDAY_WTF_VAR_MAP_ENTRY_HPP
#define WEDNESDAY_WTF_VAR_MAP_ENTRY_HPP

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

#endif // WEDNESDAY_WTF_VAR_MAP_ENTRY_HPP
