#ifndef WEDNESDAY_WTF_I_CLIENT_ENTITY_HPP
#define WEDNESDAY_WTF_I_CLIENT_ENTITY_HPP

#include "i_client_networkable.hpp"
#include "i_client_renderable.hpp"
#include "i_client_thinkable.hpp"
#include "i_client_unknown.hpp"

namespace sdk
{
	struct c_mouth_info;
	struct spatialization_info_t;

	struct i_client_entity : public i_client_unknown, public i_client_renderable, public i_client_networkable, public i_client_thinkable {
	public:
		// delete yourself.
		void release( void ) override = 0;

		// network origin + angles
		virtual const vector& get_abs_origin( void ) const = 0;
		virtual const qangle& get_abs_angles( void ) const = 0;

		virtual c_mouth_info* get_mouth( void ) = 0;

		// retrieve sound spatialization info for the specified sound on this entity
		// return false to indicate sound is not audible
		virtual bool get_sound_spatialization( spatialization_info_t& info ) = 0;
	};

} // namespace sdk

#endif // WEDNESDAY_WTF_I_CLIENT_ENTITY_HPP
