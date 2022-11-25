#ifndef WEDNESDAY_WTF_C_COMMAND_CONTEXT_HPP
#define WEDNESDAY_WTF_C_COMMAND_CONTEXT_HPP

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

#endif // WEDNESDAY_WTF_C_COMMAND_CONTEXT_HPP
