#ifndef WEDNESDAY_WTF_I_APP_SYSTEM_HPP
#define WEDNESDAY_WTF_I_APP_SYSTEM_HPP

namespace sdk
{
	struct init_return_val;

	struct i_app_system {
	public:
		// here's where the app systems get to learn about each other
		virtual bool connect( void* factory ) = 0;
		virtual void disconnect( )            = 0;

		// here's where systems can access other interfaces implemented by this object
		// returns null if it doesn't implement the requested interface
		virtual void* query_interface( const char* interface_name ) = 0;

		// init, shutdown
		virtual init_return_val init( ) = 0;
		virtual void shutdown( )        = 0;
	};
} // namespace sdk
#endif // WEDNESDAY_WTF_I_APP_SYSTEM_HPP
