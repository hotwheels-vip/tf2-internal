#pragma once

#include "../../helpers/memory/memory.hpp"
#include "i_net_channel.hpp"

namespace sdk
{
	struct c_clock_drift_mgr {
	};

	struct i_base_client_state {
		PAD( 0x10 );
		i_net_channel* net_channel; // 0x10
		PAD( 0x140 );
		c_clock_drift_mgr clock_drift_mgr; // 0x154
		int delta_tick;                    // 0x1A0
		PAD( 0x110 );
		int max_clients; // 0x2B4
		PAD( 0x486C );
		int last_out_going_command; // 0x4B24
		int choked_commands;        // 0x4B28
		int last_command_ack;       // 0x4B2C
	};
} // namespace sdk
