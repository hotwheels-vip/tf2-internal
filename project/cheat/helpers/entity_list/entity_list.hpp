//
// Created by liga on 11/15/2022.
//

#ifndef HOTWHEELS_TF2_INTERNAL_ENTITY_LIST_HPP
#define HOTWHEELS_TF2_INTERNAL_ENTITY_LIST_HPP

#include "../interfaces/interfaces.hpp"
#include <array>
#include <iostream>
#include <sdk/include.hpp>
#include <vector>

class entity_list
{
public:
	void run( sdk::c_user_cmd* _cmd );

	sdk::c_tf_player* local{ };
	sdk::c_user_cmd* cmd{ };
	sdk::c_tf_weapon_base* weapon{ };

	std::array< sdk::c_tf_player*, 48 > team{ };
	std::array< sdk::c_tf_player*, 48 > enemy{ };
};

inline entity_list* g_entity_list = new entity_list( );

#endif // HOTWHEELS_TF2_INTERNAL_ENTITY_LIST_HPP
