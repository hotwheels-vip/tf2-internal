#pragma once

#include "../interfaces/interfaces.hpp"

#include <array>
#include <iostream>
#include <sdk/include.hpp>
#include <vector>

class entity_list
{
	// private:
	//	struct dormant_info {
	//	public:
	//		int last_seen{ };
	//		bool valid{ };
	//
	//		sdk::c_tf_player* player{ };
	//		sdk::vector origin{ };
	//	};

public:
	void run( sdk::c_user_cmd* _cmd );
	void clear( );

	sdk::c_tf_player* local{ };
	sdk::c_user_cmd* cmd{ };
	sdk::c_tf_weapon_base* weapon{ };

	// A bit unoptimized! Will iter over ~32 useless entities. :-(
	std::array< sdk::c_tf_player*, 65 > team{ };
	std::array< sdk::c_tf_player*, 65 > enemy{ };
	// std::array< dormant_info, 65 > dormant{ };
};

inline entity_list* g_entity_list = new entity_list( );
