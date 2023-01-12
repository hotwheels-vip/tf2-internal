#pragma once

#include <iostream>

namespace sdk
{
	struct recv_table;
}

class netvars
{
public:
	std::uint32_t get_offset( sdk::recv_table* table, const char* netvar_name );
	std::uint32_t get_table( const char* table_name, const char* netvar_name );
};

inline netvars* g_netvars = new netvars( );
