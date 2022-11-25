//
// Created by liga on 11/13/2022.
//

#ifndef HOTWHEELS_TF2_INTERNAL_NETVARS_HPP
#define HOTWHEELS_TF2_INTERNAL_NETVARS_HPP

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

#endif // HOTWHEELS_TF2_INTERNAL_NETVARS_HPP
