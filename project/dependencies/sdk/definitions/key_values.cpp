#include "../structs/key_values.hpp"

namespace sdk
{
	struct i_key_values_system {
	public:
		// registers the size of the key_values in the specified instance
		// so it can build a properly sized memory pool for the key_values objects
		// the sizes will usually never differ but this is for versioning safety
		virtual void register_sizeof_key_values( int size ) = 0;

		// allocates/frees a key_values object from the shared mempool
		virtual void* alloc_key_values_memory( int size )  = 0;
		virtual void free_key_values_memory( void* p_mem ) = 0;

		// symbol table access (used for key names)
		virtual int get_symbol_for_string( const char* name, bool b_create = true ) = 0;
		virtual const char* get_string_for_symbol( int symbol )                     = 0;

		// for debugging, adds key_values record into global list so we can track memory leaks
		virtual void add_key_values_to_memory_leak_list( void* p_mem, int name ) = 0;
		virtual void remove_key_values_from_memory_leak_list( void* p_mem )      = 0;

		// maintain a cache of key_values we load from disk. this saves us quite a lot of time on app startup.
		virtual void add_file_key_values_to_cache( const key_values* _kv, const char* resource_name, const char* path_id ) = 0;
		virtual bool load_file_key_values_from_cache( key_values* _out_kv, const char* resource_name, const char* path_id,
		                                              i_base_file_system* filesystem ) const                               = 0;
		virtual void invalidate_cache( )                                                                                   = 0;
		virtual void invalidate_cache_for_file( const char* resource_name, const char* path_id )                           = 0;
	};

	i_key_values_system* ( *key_values_system )( );

	void key_values::init( )
	{
		m_i_key_name  = -1;
		m_i_data_type = type_none;

		m_p_sub   = nullptr;
		m_p_peer  = nullptr;
		m_p_chain = nullptr;

		m_s_value  = nullptr;
		m_ws_value = nullptr;
		m_p_value  = nullptr;

		m_b_has_escape_sequences  = false;
		m_b_evaluate_conditionals = true;

		// for future proof
		memset( unused, 0, sizeof( unused ) );
	}

	key_values* key_values::find_key( int key_symbol ) const
	{
		for ( key_values* dat = m_p_sub; dat != nullptr; dat = dat->m_p_peer ) {
			if ( dat->m_i_key_name == key_symbol )
				return dat;
		}

		return nullptr;
	}

	key_values* key_values::find_key( const char* key_name, bool b_create )
	{
		// return the current key if a null subkey is asked for
		if ( !key_name || !key_name[ 0 ] )
			return this;

		// look for '/' characters deliminating sub fields
		char sz_buf[ 256 ];
		const char* sub_str    = strchr( key_name, '/' );
		const char* search_str = key_name;

		// pull out the substring if it exists
		if ( sub_str ) {
			int size = sub_str - key_name;
			memcpy( sz_buf, key_name, size );
			sz_buf[ size ] = 0;
			search_str     = sz_buf;
		}

		// lookup the symbol for the search string
		int i_search_str = key_values_system( )->get_symbol_for_string( search_str, b_create );

		if ( i_search_str == -1 ) {
			// not found, couldn't possibly be in key value list
			return nullptr;
		}

		key_values* last_item = nullptr;
		key_values* dat;
		// find the search_str in the current peer list
		for ( dat = m_p_sub; dat != nullptr; dat = dat->m_p_peer ) {
			last_item = dat; // record the last item looked at (for if we need to
			// append to the end of the list)

			// symbol compare
			if ( dat->m_i_key_name == i_search_str ) {
				break;
			}
		}

		if ( !dat && m_p_chain ) {
			dat = m_p_chain->find_key( key_name, false );
		}

		// make sure a key was found
		if ( !dat ) {
			if ( b_create ) {
				// we need to create a new key
				dat = new key_values( search_str );
				//			assert(dat != null);

				dat->uses_escape_sequences( m_b_has_escape_sequences != 0 ); // use same format as parent
				dat->uses_conditionals( m_b_evaluate_conditionals != 0 );

				// insert new key at end of list
				if ( last_item ) {
					last_item->m_p_peer = dat;
				} else {
					m_p_sub = dat;
				}
				dat->m_p_peer = nullptr;

				// a key graduates to be a submsg as soon as it's m_p_sub is set
				// this should be the only place m_p_sub is set
				m_i_data_type = type_none;
			} else {
				return nullptr;
			}
		}

		// if we've still got a sub_str we need to keep looking deeper in the tree
		if ( sub_str ) {
			// recursively chain down through the paths in the string
			return dat->find_key( sub_str + 1, b_create );
		}

		return dat;
	}

	void key_values::set_float( const char* key_name, float value )
	{
		key_values* dat = find_key( key_name, true );

		if ( dat ) {
			dat->m_fl_value    = value;
			dat->m_i_data_type = type_float;
		}
	}

	void key_values::set_int( const char* key_name, int value )
	{
		key_values* dat = find_key( key_name, true );

		if ( dat ) {
			dat->m_i_value     = value;
			dat->m_i_data_type = type_int;
		}
	}

	void key_values::set_string( const char* key_name, const char* value )
	{
		key_values* dat = find_key( key_name, true );

		if ( dat ) {
			int length = strlen( value );

			dat->m_s_value = new char[ length + 1 ];

			memcpy( dat->m_s_value, value, length + 1 );
			dat->m_i_data_type = type_string;
		}
	}

	key_values::key_values( const char* _set_name )
	{
		init( );
		set_name( _set_name );
	}

	void key_values::uses_escape_sequences( bool state )
	{
		m_b_has_escape_sequences = state;
	}

	void key_values::set_name( const char* set_name )
	{
		m_i_key_name = key_values_system( )->get_symbol_for_string( set_name, true );
	}

	//-----------------------------------------------------------------------------
	// purpose: if parser should evaluate conditional blocks ( [$windows] etc. )
	//-----------------------------------------------------------------------------
	void key_values::uses_conditionals( bool state )
	{
		m_b_evaluate_conditionals = state;
	}

	key_values::~key_values( )
	{
		remove_everything( );
	}

	void* key_values::operator new( size_t i_alloc_size )
	{
		if ( !key_values_system )
			key_values_system = reinterpret_cast< decltype( key_values_system ) >(
				reinterpret_cast< i_key_values_system* >( GetProcAddress( GetModuleHandle( "vstdlib.dll" ), "KeyValuesSystem" ) ) );

		return key_values_system( )->alloc_key_values_memory( static_cast< int >( i_alloc_size ) );
	}

	//-----------------------------------------------------------------------------
	// purpose: remove everything
	//-----------------------------------------------------------------------------
	void key_values::remove_everything( )
	{
		key_values* dat;
		key_values* dat_next = nullptr;
		for ( dat = m_p_sub; dat != nullptr; dat = dat_next ) {
			dat_next      = dat->m_p_peer;
			dat->m_p_peer = nullptr;
			delete dat;
		}

		for ( dat = m_p_peer; dat && dat != this; dat = dat_next ) {
			dat_next      = dat->m_p_peer;
			dat->m_p_peer = nullptr;
			delete dat;
		}

		delete[] m_s_value;
		m_s_value = nullptr;
		delete[] m_ws_value;
		m_ws_value = nullptr;
	}

	void key_values::operator delete( void* p_mem )
	{
		key_values_system( )->free_key_values_memory( p_mem );
	}

	void key_values::operator delete( void* p_mem, int n_block_use, const char* p_file_name, int n_line )
	{
		key_values_system( )->free_key_values_memory( p_mem );
	}

	void key_values::delete_this( )
	{
		delete this;
	}
} // namespace sdk