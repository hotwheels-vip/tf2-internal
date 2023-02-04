#pragma once

#include "../../helpers/include.hpp"

#include <sdk/include.hpp>

struct weapon_info {
	float speed{ };
	sdk::vector offset{ };

	bool next_tick{ };
	float gravity{ };
	bool can_headshot{ };
};

class prediction
{
public:
	struct prediction_projectile_backup {
	public:
		sdk::vector origin{ };
		sdk::vector velocity{ };
		sdk::vector base_velocity{ };
		sdk::c_base_handle ground_entity{ };
		int flags{ };
		float duck_time{ };
		float duck_jump_time{ };
		bool ducked{ };
		bool ducking{ };
		bool in_duck_jump{ };
		float model_scale{ };
		float simulation_time{ };
		bool is_in_prediction{ };
		bool first_time_running{ };
		float frame_time{ };
		int tick_base{ };
		float cur_time{ };
	};

	prediction_projectile_backup projectile_backup{ };
	sdk::c_user_cmd projectile_cmd{ };
	sdk::move_data_t projectile_move_data{ };

	bool running_post_think{ };

	void run( );
	void end( );

	void set_prediction_random_seed( sdk::c_user_cmd* cmd );
	void set_prediction_player( sdk::c_tf_player* player );
	void reset( );

	sdk::vector linear( sdk::vector origin, sdk::c_tf_player* player, sdk::vector offset, weapon_info data, bool choke );
	sdk::qangle quadratic( sdk::vector origin, sdk::c_tf_player* player, sdk::vector offset, weapon_info data, bool choke );
};

inline prediction* g_prediction = new prediction( );
