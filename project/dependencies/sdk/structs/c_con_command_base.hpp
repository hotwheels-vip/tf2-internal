#ifndef WEDNESDAY_WTF_C_CON_COMMAND_BASE_HPP
#define WEDNESDAY_WTF_C_CON_COMMAND_BASE_HPP
namespace sdk
{

	struct c_var_dll_identifier_t;

	struct con_command_base {
	public:
		virtual ~con_command_base( void );
		virtual bool is_command( void ) const;
		virtual bool is_flag_set( int flag ) const;
		virtual void add_flags( int ilags );
		virtual const char* get_name( void ) const;
		virtual const char* get_help_text( void ) const;
		virtual bool is_registered( void ) const;
		virtual c_var_dll_identifier_t get_dll_identifier( ) const;
		virtual void create_base( const char* name, const char* help_string = nullptr, int flags = 0 );

		con_command_base* next;
		bool registered;
		const char* name;
		const char* help_string;
		int flags;

	protected:
		static con_command_base* c_con_command_bases;
		static void* accessor;
	};

} // namespace sdk
#endif // WEDNESDAY_WTF_C_CON_COMMAND_BASE_HPP
