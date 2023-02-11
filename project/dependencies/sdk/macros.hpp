#pragma once

#include "../../cheat/helpers/memory/memory.hpp"
#include "../../cheat/helpers/netvars/netvars.hpp"

#define COMBINE( lhs, rhs ) lhs##rhs
#define CONCAT( lhs, rhs )  COMBINE( lhs, rhs )
#define PAD( size )                                                                                                                                  \
private:                                                                                                                                             \
	std::uint8_t CONCAT( pad, __COUNTER__ )[ size ];                                                                                                 \
                                                                                                                                                     \
public:

#define NETVAR( function_name, type, table_name, netvar_name )                                                                                       \
	inline type& function_name( )                                                                                                                    \
	{                                                                                                                                                \
		static std::uint32_t offset = netvars::get_table( table_name, netvar_name );                                                                 \
		return *( type* )( ( std::uint32_t )this + offset );                                                                                         \
	}
