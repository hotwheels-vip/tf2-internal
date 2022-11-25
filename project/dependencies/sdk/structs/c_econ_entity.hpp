#ifndef WEDNESDAY_WTF_C_ECON_ENTITY_HPP
#define WEDNESDAY_WTF_C_ECON_ENTITY_HPP

#include "../macros.hpp"

namespace sdk
{
	struct c_econ_entity {
	public:
		NETVAR( item_definition_index, int, "CEconEntity", "m_iItemDefinitionIndex" );
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_C_ECON_ENTITY_HPP
