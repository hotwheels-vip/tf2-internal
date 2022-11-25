#ifndef WEDNESDAY_WTF_I_LOCALIZE_HPP
#define WEDNESDAY_WTF_I_LOCALIZE_HPP

#include "../structs/key_values.hpp"

namespace sdk
{
	typedef unsigned long string_index_t;

	struct i_localize {
	public:
		// adds the contents of a file to the localization table
		virtual bool add_file( const char* file_name, const char* p_path_id, bool b_include_fallback_search_paths = false ) = 0;

		// remove all strings from the table
		virtual void remove_all( ) = 0;

		// finds the localized text for token_name
		virtual wchar_t* find( char const* token_name ) = 0;

		// finds the index of a token by token name, invalid_string_index if not found
		virtual string_index_t find_index( const char* token_name ) = 0;

		// gets the values by the string index
		virtual const char* get_name_by_index( string_index_t index ) = 0;
		virtual wchar_t* get_value_by_index( string_index_t index )   = 0;

		///////////////////////////////////////////////////////////////////
		// the following functions should only be used by localization editors

		// iteration functions
		virtual string_index_t get_first_string_index( ) = 0;
		// returns the next index, or invalid_string_index if no more strings available
		virtual string_index_t get_next_string_index( string_index_t index ) = 0;

		// adds a single name/unicode string pair to the table
		virtual void add_string( const char* token_name, wchar_t* unicode_string, const char* file_name ) = 0;

		// changes the value of a string
		virtual void set_value_by_index( string_index_t index, wchar_t* new_value ) = 0;

		// saves the entire contents of the token tree to the file
		virtual bool save_to_file( const char* file_name ) = 0;

		// iterates the filenames
		virtual int get_localization_file_count( )                  = 0;
		virtual const char* get_localization_file_name( int index ) = 0;

		// returns the name of the file the specified localized string is stored in
		virtual const char* get_file_name_by_index( string_index_t index ) = 0;

		// for development only, reloads localization files
		virtual void reload_localization_files( ) = 0;

		virtual const char* find_as_utf8( const char* pch_token_name ) = 0;

		// need to replace the existing construct_string with this
		virtual void construct_string( wchar_t* unicode_output, int unicode_buffer_size_in_bytes, const char* token_name,
		                               key_values* localization_variables ) = 0;
		virtual void construct_string( wchar_t* unicode_output, int unicode_buffer_size_in_bytes, string_index_t unlocalized_text_symbol,
		                               key_values* localization_variables ) = 0;
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_I_LOCALIZE_HPP
