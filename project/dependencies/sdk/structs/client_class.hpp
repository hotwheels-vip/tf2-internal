#ifndef WEDNESDAY_WTF_CLIENT_CLASS_HPP
#define WEDNESDAY_WTF_CLIENT_CLASS_HPP

#include "dt_recv.hpp"
#include "../enums/class_ids.hpp"

namespace sdk
{

	struct client_class {
	public:
		void* create_fn;
		void* create_event_fn;
		const char* network_name;
		recv_table* recv_table;
		client_class* next;
		sdk::e_class_ids class_id;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_CLIENT_CLASS_HPP
