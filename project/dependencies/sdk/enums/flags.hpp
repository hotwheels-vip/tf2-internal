#ifndef WEDNESDAY_WTF_FLAGS_HPP
#define WEDNESDAY_WTF_FLAGS_HPP

namespace sdk
{
	enum flags {
		onground              = ( 1 << 0 ),
		ducking               = ( 1 << 1 ),
		animducking           = ( 1 << 2 ),
		waterjump             = ( 1 << 3 ),
		ontrain               = ( 1 << 4 ),
		inrain                = ( 1 << 5 ),
		frozen                = ( 1 << 6 ),
		atcontrols            = ( 1 << 7 ),
		client                = ( 1 << 8 ),
		fakeclient            = ( 1 << 9 ),
		inwater               = ( 1 << 10 ),
		fly                   = ( 1 << 11 ),
		swim                  = ( 1 << 12 ),
		conveyor              = ( 1 << 13 ),
		npc                   = ( 1 << 14 ),
		godmode               = ( 1 << 15 ),
		notarget              = ( 1 << 16 ),
		aimtarget             = ( 1 << 17 ),
		partialground         = ( 1 << 18 ),
		staticprop            = ( 1 << 19 ),
		graphed               = ( 1 << 20 ),
		grenade               = ( 1 << 21 ),
		stepmovement          = ( 1 << 22 ),
		donttouch             = ( 1 << 23 ),
		basevelocity          = ( 1 << 24 ),
		worldbrush            = ( 1 << 25 ),
		object                = ( 1 << 26 ),
		killme                = ( 1 << 27 ),
		onfire                = ( 1 << 28 ),
		dissolving            = ( 1 << 29 ),
		transragdoll          = ( 1 << 30 ),
		unblockable_by_player = ( 1 << 31 )
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_FLAGS_HPP
