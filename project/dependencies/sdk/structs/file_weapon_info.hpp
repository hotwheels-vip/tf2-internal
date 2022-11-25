#ifndef WEDNESDAY_WTF_FILE_WEAPON_INFO_HPP
#define WEDNESDAY_WTF_FILE_WEAPON_INFO_HPP

namespace sdk
{
	struct file_weapon_info {
	public:
		file_weapon_info( );

		virtual void parse( void* key_values_data, const char* weapon_name ){ };

		bool parsed_script;
		bool loaded_hud_elements;

		// shared
		char class_name[ 80 ];
		char print_name[ 80 ]; // name for showing in hud, etc.

		char view_model[ 80 ];       // view model of this weapon
		char world_model[ 80 ];      // model of this weapon seen carried by the player
		char animation_prefix[ 16 ]; // prefix of the animations that should be used by the player carrying this weapon
		int slot;                    // inventory slot.
		int position;                // position in the inventory slot.
		int max_clip1;               // max primary clip size (-1 if no clip)
		int max_clip2;               // max secondary clip size (-1 if no clip)
		int default_clip1;           // amount of primary ammo in the gun when it's created
		int default_clip2;           // amount of secondary ammo in the gun when it's created
		int weight;                  // this value used to determine this weapon's importance in autoselection.
		int rumble_effect;           // which rumble effect to use when fired? (xbox)
		bool auto_switch_to;         // whether this weapon should be considered for autoswitching to
		bool auto_switch_from;       // whether this weapon can be autoswitched away from when picking up another weapon or ammo
		int flags;                   // miscellaneous weapon flags
		char ammo1[ 32 ];            // "primary" ammo type
		char ammo2[ 32 ];            // "secondary" ammo type

		// sound blocks
		char shoot_sounds[ 16 ][ 80 ];

		int ammo_type;
		int ammo2_type;
		bool melee_weapon; // melee weapons can always "fire" regardless of ammo.

		// this tells if the weapon was built right-handed (defaults to true).
		// this helps cl_righthand make the decision about whether to flip the model or not.
		bool built_right_handed;
		bool allow_flipping; // false to disallow flipping the model, regardless of whether
		// it is built left or right handed.

		// client dll
		// sprite data, read from the data file
		int sprite_count;
		void* icon_active;
		void* icon_inactive;
		void* icon_ammo;
		void* icon_ammo2;
		void* icon_crosshair;
		void* icon_autoaim;
		void* icon_zoomed_crosshair;
		void* icon_zoomed_autoaim;
		void* icon_small;

		// tf2 specific
		bool show_usage_hint;
	};

} // namespace sdk

#endif // WEDNESDAY_WTF_FILE_WEAPON_INFO_HPP
