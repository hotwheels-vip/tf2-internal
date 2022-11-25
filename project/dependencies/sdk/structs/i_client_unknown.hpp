#ifndef WEDNESDAY_WTF_I_CLIENT_UNKNOWN_HPP
#define WEDNESDAY_WTF_I_CLIENT_UNKNOWN_HPP

#include "i_handle_entity.hpp"

namespace sdk
{
	struct i_collideable;
	struct i_client_networkable;
	struct i_client_renderable;
	struct i_client_entity;
	struct c_base_entity;
	struct i_client_thinkable;

	struct i_client_unknown : public i_handle_entity {
	public:
		virtual i_collideable* get_collideable( )               = 0;
		virtual i_client_networkable* get_client_networkable( ) = 0;
		virtual i_client_renderable* get_client_renderable( )   = 0;
		virtual i_client_entity* get_i_client_entity( )         = 0;
		virtual c_base_entity* get_base_entity( )               = 0;
		virtual i_client_thinkable* get_client_thinkable( )     = 0;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_CLIENT_UNKNOWN_HPP
