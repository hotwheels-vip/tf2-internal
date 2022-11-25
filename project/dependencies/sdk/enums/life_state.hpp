#ifndef WEDNESDAY_WTF_LIFE_STATE_HPP
#define WEDNESDAY_WTF_LIFE_STATE_HPP

namespace sdk
{

	enum life_state {
		life_alive = 0,
		life_dying,
		life_dead,
		life_respawnable,
		life_discardbody
	};

} // namespace sdk

#endif // WEDNESDAY_WTF_LIFE_STATE_HPP
