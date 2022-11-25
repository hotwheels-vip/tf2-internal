//
// Created by liga on 11/13/2022.
//

#ifndef HOTWHEELS_TF2_INTERNAL_MACROS_HPP
#define HOTWHEELS_TF2_INTERNAL_MACROS_HPP

#include "../../cheat/helpers/memory/memory.hpp"
#include "../../cheat/helpers/netvars/netvars.hpp"

#define COMBINE( lhs, rhs ) lhs##rhs
#define CONCAT( lhs, rhs )  COMBINE( lhs, rhs )
#define PAD( size )                                                                                                                                  \
private:                                                                                                                                             \
	std::uint8_t CONCAT( pad, __COUNTER__ )[ size ];

#define NETVAR( function_name, type, table_name, netvar_name )                                                                                       \
	inline type& function_name( )                                                                                                                    \
	{                                                                                                                                                \
		static std::uint32_t offset = g_netvars->get_table( table_name, netvar_name );                                                               \
		return *( type* )( ( std::uint32_t )this + offset );                                                                                         \
	}

#endif // HOTWHEELS_TF2_INTERNAL_MACROS_HPP
