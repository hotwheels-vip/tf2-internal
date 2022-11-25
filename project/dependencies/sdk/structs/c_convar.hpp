#ifndef WEDNESDAY_WTF_C_CONVAR_HPP
#define WEDNESDAY_WTF_C_CONVAR_HPP
#include "../enums/cvar_flags.hpp"
#include "c_con_command_base.hpp"
namespace sdk
{
	struct c_con_var {
	public:
		virtual void set_value( const char* p_value ) = 0;
		virtual void set_value( float fl_value )      = 0;
		virtual void set_value( int n_value )         = 0;
		virtual const char* get_name( void ) const    = 0;
		virtual bool is_flag_set( int n_flag ) const  = 0;
	};

	struct con_var : public con_command_base, public c_con_var {
	public:
		~con_var( void ) override;
		bool is_flag_set( int flag ) const override;
		const char* get_help_text( void ) const override;
		bool is_registered( void ) const override;
		const char* get_name( void ) const override;
		void add_flags( int flags ) override;
		bool is_command( void ) const override;
		void set_value( const char* value ) override;
		void set_value( float value ) override;
		void set_value( int value ) override;
		virtual void internal_set_value( const char* value );
		virtual void internal_set_float_value( float new_value, bool force = false );
		virtual void internal_set_int_value( int value );
		virtual bool clamp_value( float& value );
		virtual void change_string_value( const char* temp_val, float old_value );
		virtual void init( );

		inline float get_float( void ) const;
		inline int get_int( void ) const;
		bool get_bool( ) const
		{
			return !!get_int( );
		}
		inline const char* get_string( void ) const;

		con_var* parent;
		const char* default_value;
		char* string_;
		int string_length;
		float float_value;
		int int_value;
		bool has_min;
		float min_val;
		bool has_max;
		float max_val;
		bool has_comp_min;
		float comp_min_val;
		bool has_comp_max;
		float comp_max_val;
		bool competitive_restrictions;
		void* change_callback; // fn_change_callback_t
	};

	inline float con_var::get_float( void ) const
	{
		return parent->float_value;
	}

	inline int con_var::get_int( void ) const
	{
		return parent->int_value;
	}

	inline const char* con_var::get_string( void ) const
	{
		if ( flags & fcvar_never_as_string )
			return "fcvar_never_as_string";

		return ( parent->string_ ) ? parent->string_ : "";
	}
} // namespace sdk

#endif // WEDNESDAY_WTF_C_CONVAR_HPP
