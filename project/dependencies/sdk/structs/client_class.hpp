#pragma once

#include "../enums/class_ids.hpp"
#include "dt_recv.hpp"

namespace sdk
{

	struct client_class {
	public:
		void* create_fn;
		void* create_event_fn;
		const char* network_name;
		recv_table* recv_table;
		client_class* next;
		sdk::class_ids class_id;
	};
} // namespace sdk
