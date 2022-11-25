#ifndef WEDNESDAY_WTF_C_TF_WEAPON_INFO_HPP
#define WEDNESDAY_WTF_C_TF_WEAPON_INFO_HPP

#include "file_weapon_info.hpp"
#include "weapon_data.hpp"

namespace sdk
{
	struct key_values;

	struct c_tf_weapon_info : public file_weapon_info {
	public:
		virtual void parse( key_values* key_values_data, const char* weapon_name ){ };

		weapon_data& get_weapon_data( int weapon )
		{
			return weapon_data[ weapon ];
		}

		weapon_data weapon_data[ 2 ];

		int weapon_type;

		// grenade.
		bool grenade;
		float damage_radius;
		float primer_time;
		bool lower_weapon;
		bool suppress_gren_timer;

		// skins
		bool has_team_skins_viewmodel;
		bool has_team_skins_worldmodel;

		// muzzle flash
		char muzzle_flash_model[ 128 ];
		float muzzle_flash_model_duration;
		char muzzle_flash_particle_effect[ 128 ];

		// tracer
		char tracer_effect[ 128 ];

		// eject brass
		bool do_instant_eject_brass;
		char brass_model[ 128 ];

		// explosion effect
		char explosion_sound[ 128 ];
		char explosion_effect[ 128 ];
		char explosion_player_effect[ 128 ];
		char explosion_water_effect[ 128 ];

		bool dont_drop;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_C_TF_WEAPON_INFO_HPP
