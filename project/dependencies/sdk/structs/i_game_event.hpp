#ifndef WEDNESDAY_WTF_I_GAME_EVENT_HPP
#define WEDNESDAY_WTF_I_GAME_EVENT_HPP

namespace sdk
{
	struct i_game_event {
	public:
		virtual ~i_game_event( ){ };

		virtual const char* get_name( ) const                                                            = 0;
		virtual bool is_reliable( ) const                                                                = 0;
		virtual bool is_local( ) const                                                                   = 0;
		virtual bool is_empty( const char* key_name = nullptr )                                          = 0;
		virtual bool get_bool( const char* key_name = nullptr, bool default_value = false )              = 0;
		virtual int get_int( const char* key_name = nullptr, int default_value = 0 )                     = 0;
		virtual float get_float( const char* key_name = nullptr, float default_value = 0.0f )            = 0;
		virtual const char* get_string( const char* key_name = nullptr, const char* default_value = "" ) = 0;
		virtual void set_bool( const char* key_name, bool value )                                        = 0;
		virtual void set_int( const char* key_name, int value )                                          = 0;
		virtual void set_float( const char* key_name, float value )                                      = 0;
		virtual void set_string( const char* key_name, const char* value )                               = 0;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_GAME_EVENT_HPP
