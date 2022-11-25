

#ifndef WEDNESDAY_WTF_I_CVAR_HPP
#define WEDNESDAY_WTF_I_CVAR_HPP

#include "../structs/c_convar.hpp"
#include "i_app_system.hpp"

namespace sdk
{
	struct i_con_var : public i_app_system {
	public:
		virtual c_var_dll_identifier_t allocate_dll_identifier( )                                                 = 0;
		virtual void register_con_command( con_command_base* p_command_base )                                     = 0;
		virtual void unregister_con_command( con_command_base* p_command_base )                                   = 0;
		virtual void unregister_con_commands( c_var_dll_identifier_t id )                                         = 0;
		virtual const char* get_command_line_value( const char* p_variable_name )                                 = 0;
		virtual con_command_base* find_command_base( const char* sz_name )                                        = 0;
		virtual const con_command_base* find_command_base( const char* sz_name ) const                            = 0;
		virtual con_var* find_var( const char* sz_var_name )                                                      = 0;
		virtual const con_var* find_var( const char* sz_var_name ) const                                          = 0;
		virtual void* find_command( const char* sz_name )                                                         = 0;
		virtual const void* find_command( const char* sz_name ) const                                             = 0;
		virtual con_command_base* get_commands( void )                                                            = 0;
		virtual const con_command_base* get_commands( void ) const                                                = 0;
		virtual void install_global_change_callback( void* p_callback )                                           = 0;
		virtual void remove_global_change_callback( void* p_callback )                                            = 0;
		virtual void call_global_change_callbacks( con_var* p_var, const char* p_old_string, float fl_old_value ) = 0;
		virtual void install_console_display_func( void* p_display_func )                                         = 0;
		virtual void remove_console_display_func( void* p_display_func )                                          = 0;
		virtual void console_color_printf( void* clr, const char* p_format, ... ) const                           = 0; // color might be fucked
		virtual void console_printf( const char* p_format, ... ) const                                            = 0;
		virtual void console_d_printf( const char* p_format, ... ) const                                          = 0;
		virtual void revert_flagged_con_vars( int n_flag )                                                        = 0;
		virtual void install_c_var_query( void* p_query )                                                         = 0;
		virtual bool is_material_thread_set_allowed( ) const                                                      = 0;
		virtual void queue_material_thread_set_value( con_var* p_con_var, const char* p_value )                   = 0;
		virtual void queue_material_thread_set_value( con_var* p_con_var, int n_value )                           = 0;
		virtual void queue_material_thread_set_value( con_var* p_con_var, float fl_value )                        = 0;
		virtual bool has_queued_material_thread_con_var_sets( ) const                                             = 0;
		virtual int process_queued_material_thread_con_var_sets( )                                                = 0;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_CVAR_HPP
