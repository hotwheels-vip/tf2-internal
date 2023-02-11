#pragma once

#include <iostream>

namespace sdk
{
	struct recv_table;
}

class netvars
{
public:
	static std::uint32_t get_offset( const sdk::recv_table* table, const char* netvar_name );
	static std::uint32_t get_table( const char* table_name, const char* netvar_name );
};

inline netvars* g_netvars = new netvars( );
