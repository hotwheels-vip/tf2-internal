#ifndef WEDNESDAY_WTF_I_CLIENT_THINKABLE_HPP
#define WEDNESDAY_WTF_I_CLIENT_THINKABLE_HPP

namespace sdk
{
	enum client_think_handle_t;

	struct i_client_unknown;

	struct i_client_thinkable {
	public:
		// gets at the containing class...
		virtual i_client_unknown* get_i_client_unknown( ) = 0;

		virtual void client_think( ) = 0;

		// called when you're added to the think list.
		// get_think_handle's return value must be initialized to invalid_think_handle.
		virtual client_think_handle_t get_think_handle( )              = 0;
		virtual void set_think_handle( client_think_handle_t h_think ) = 0;

		// called by the client when it deletes the entity.
		virtual void release( ) = 0;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_CLIENT_THINKABLE_HPP
