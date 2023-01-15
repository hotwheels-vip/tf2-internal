#pragma once

#include "c_user_cmd.hpp"

namespace sdk
{
	struct c_verified_cmd {
	public:
		c_user_cmd cmd;
		CRC32_t crc;
	};
} // namespace sdk
