#ifndef WEDNESDAY_WTF_WEAPON_DATA_HPP
#define WEDNESDAY_WTF_WEAPON_DATA_HPP

namespace sdk
{
	struct weapon_data {
	public:
		int damage;
		int bullets_per_shot;
		float range;
		float spread;
		float punch_angle;
		float time_fire_delay;   // time to delay between firing
		float time_idle;         // time to idle after firing
		float time_idle_empty;   // time to idle after firing last bullet in clip
		float time_reload_start; // time to start into a reload (ie. shotgun)
		float time_reload;       // time to reload
		bool draw_crosshair;     // should the weapon draw a crosshair
		int projectile;          // the type of projectile this mode fires
		int ammo_per_shot;       // how much ammo each shot consumes
		float projectile_speed;  // start speed for projectiles (nail, etc.); note: union with something non-projectile
		float smack_delay;       // how long after swing should damage happen for melee weapons
		bool use_rapid_fire_crits;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_WEAPON_DATA_HPP
