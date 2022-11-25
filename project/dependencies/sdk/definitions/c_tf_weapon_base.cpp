#include "../structs/c_tf_weapon_base.hpp"
#include "../../../cheat/helpers/interfaces/interfaces.hpp"

bool sdk::c_tf_weapon_base::can_attack_primary( sdk::c_tf_player* owner )
{
	return next_primary_attack( ) <= ( owner->tick_base( ) * g_interfaces->globals->interval_per_tick );
}

bool sdk::c_tf_weapon_base::can_attack_secondary( sdk::c_tf_player* owner )
{
	return next_secondary_attack( ) <= ( owner->tick_base( ) * g_interfaces->globals->interval_per_tick );
}
