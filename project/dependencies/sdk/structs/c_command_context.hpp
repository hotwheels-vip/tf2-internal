#pragma once

#include "c_user_cmd.hpp"

namespace sdk
{
	struct c_command_context {
	public:
		bool needs_processing;
		c_user_cmd command;
		int command_number;
	};
} // namespace sdk
