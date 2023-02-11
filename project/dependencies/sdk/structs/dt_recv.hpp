#pragma once

#include "dt_common.hpp"

namespace sdk
{

#define addressproxy_none -1

	struct recv_table;
	struct recv_prop;

	// this is passed into recv_proxy functions.
	struct c_recv_proxy_data {
	public:
		const recv_prop* recv_prop; // the property it's receiving.

		d_variant m_value; // the value given to you to store.

		int element; // which array element you're getting.

		int m_object_id; // the object being referred to.
	};

	//-----------------------------------------------------------------------------
	// p_struct = the base structure of the datatable this variable is in (like c_base_entity)
	// p_out    = the variable that this this proxy represents (like c_base_entity::m_some_value).
	//
	// convert the network-standard-type value in m_value into your own format in p_struct/p_out.
	//-----------------------------------------------------------------------------
	typedef void ( *recv_var_proxy_fn )( const c_recv_proxy_data* p_data, void* p_struct, void* p_out );

	// ------------------------------------------------------------------------ //
	// array_length_recv_proxies are optionally used to get the length of the
	// incoming array when it changes.
	// ------------------------------------------------------------------------ //
	typedef void ( *array_length_recv_proxy_fn )( void* p_struct, int object_id, int current_array_length );

	// note: data_table receive proxies work differently than the other proxies.
	// p_data points at the object + the recv table's offset.
	// p_out should be set to the location of the object to unpack the data table into.
	// if the parent object just contains the child object, the default proxy just does *p_out = p_data.
	// if the parent object points at the child object, you need to dereference the pointer here.
	// note: don't ever return null from a data_table receive proxy function. bad things will happen.
	typedef void ( *data_table_recv_var_proxy_fn )( const recv_prop* p_prop, void** p_out, void* p_data, int object_id );

	// this is used to fork over the standard proxy functions to the engine so it can
	// make some optimizations.
	struct c_standard_recv_proxies {
	public:
		c_standard_recv_proxies( );

		recv_var_proxy_fn m_int32_to_int8;
		recv_var_proxy_fn m_int32_to_int16;
		recv_var_proxy_fn m_int32_to_int32;
		recv_var_proxy_fn m_float_to_float;
		recv_var_proxy_fn m_vector_to_vector;
#ifdef supports_int64
		recv_var_proxy_fn m_int64_to_int64;
#endif
	};
	extern c_standard_recv_proxies g_standard_recv_proxies;

	struct c_recv_decoder;

	struct recv_prop {
		// this info comes from the receive data table.
	public:
		recv_prop( );

		void init_array( int nelements, int element_stride );

		int get_num_elements( ) const;
		void set_num_elements( int nelements );

		int get_element_stride( ) const;
		void set_element_stride( int stride );

		int get_flags( ) const;

		const char* get_name( ) const;
		int get_type( ) const;

		recv_table* get_data_table( ) const;
		void set_data_table( recv_table* p_table );

		recv_var_proxy_fn get_proxy_fn( ) const;
		void set_proxy_fn( recv_var_proxy_fn fn );

		data_table_recv_var_proxy_fn get_data_table_proxy_fn( ) const;
		void set_data_table_proxy_fn( data_table_recv_var_proxy_fn fn );

		int get_offset( ) const;
		void set_offset( int o );

		// arrays only.
		recv_prop* get_array_prop( ) const;
		void set_array_prop( recv_prop* p_prop );

		// arrays only.
		void set_array_length_proxy( array_length_recv_proxy_fn proxy );
		array_length_recv_proxy_fn get_array_length_proxy( ) const;

		bool is_inside_array( ) const;
		void set_inside_array( );

		// some property types bind more data to the prop in here.
		const void* get_extra_data( ) const;
		void set_extra_data( const void* p_data );

		// if it's one of the numbered "000", "001", etc properties in an array, then
		// these can be used to get its array property name for debugging.
		const char* get_parent_array_prop_name( );
		void set_parent_array_prop_name( const char* p_array_prop_name );

	public:
		const char* var_name;
		int recv_type;
		int flags;
		int string_buffer_size;

		bool inside_array; // set to true by the engine if this property sits inside an array.

		// extra data that certain special property types bind to the property here.
		const void* extra_data;

		// if this is an array (dpt_array).
		recv_prop* array_prop;
		array_length_recv_proxy_fn array_length_proxy;

		recv_var_proxy_fn proxy_fn;
		data_table_recv_var_proxy_fn data_table_proxy_fn; // for rdt_data_table.

		recv_table* data_table; // for rdt_data_table.
		int offset;

		int element_stride;
		int elements;

		// if it's one of the numbered "000", "001", etc properties in an array, then
		// these can be used to get its array property name for debugging.
		const char* parent_array_prop_name;
	};

	struct recv_table {
	public:
		typedef recv_prop prop_type;

		recv_table( );
		recv_table( recv_prop* p_props, int n_props, const char* p_net_table_name );
		~recv_table( );

		void construct( recv_prop* p_props, int n_props, const char* p_net_table_name );

		int get_num_props( );
		recv_prop* get_prop( int i );

		const char* get_name( );

		// used by the engine while initializing array props.
		void set_initialized( bool b_initialized );
		bool is_initialized( ) const;

		// used by the engine.
		void set_in_main_list( bool b_in_list );
		bool is_in_main_list( ) const;

	public:
		// properties described in a table.
		recv_prop* props;
		int nprops;

		// the decoder. note: this covers each recv_table and all its children (ie: its children
		// will have their own decoders that include props for all their children).
		c_recv_decoder* decoder;

		const char* net_table_name; // the name matched between client and server.

	private:
		bool initialized;
		bool in_main_list;
	};

	inline int recv_table::get_num_props( )
	{
		return nprops;
	}

	inline recv_prop* recv_table::get_prop( int i )
	{
		// assert( i >= 0 && i < m_n_props );
		return &props[ i ];
	}

	inline const char* recv_table::get_name( )
	{
		return net_table_name;
	}

	inline void recv_table::set_initialized( bool b_initialized )
	{
		initialized = b_initialized;
	}

	inline bool recv_table::is_initialized( ) const
	{
		return initialized;
	}

	inline void recv_table::set_in_main_list( bool b_in_list )
	{
		in_main_list = b_in_list;
	}

	inline bool recv_table::is_in_main_list( ) const
	{
		return in_main_list;
	}

// ------------------------------------------------------------------------------------------------------ //
// see notes on begin_send_table for a description. these macros work similarly.
// ------------------------------------------------------------------------------------------------------ //
#define begin_recv_table( struct_name, table_name )                                                                                                  \
	begin_recv_table_nobase( struct_name, table_name )                                                                                               \
		recv_prop_data_table( "basestruct", 0, 0, struct_name::basestruct::m_pstruct_recv_table, data_table_recv_proxy_static_data_table ),

#define begin_recv_table_nobase( struct_name, table_name )                                                                                           \
	template< typename t >                                                                                                                           \
	int clientstruct_init( t* );                                                                                                                     \
	namespace table_name                                                                                                                             \
	{                                                                                                                                                \
		struct ignored;                                                                                                                              \
	}                                                                                                                                                \
	template<>                                                                                                                                       \
	int clientstruct_init< table_name::ignored >( table_name::ignored* );                                                                            \
	namespace table_name                                                                                                                             \
	{                                                                                                                                                \
		recv_table g_recv_table;                                                                                                                     \
		int g_recv_table_init = clientstruct_init( ( table_name::ignored* )null );                                                                   \
	}                                                                                                                                                \
	template<>                                                                                                                                       \
	int clientstruct_init< table_name::ignored >( table_name::ignored* )                                                                             \
	{                                                                                                                                                \
		typedef struct_name current_recv_d_tstruct;                                                                                                  \
		const char* p_recv_table_name = #table_name;                                                                                                 \
		recv_table& recv_table        = table_name::g_recv_table;                                                                                    \
		static recv_prop recv_props[] = {                                                                                                            \
			recv_prop_int( "should_never_see_this", 0,                                                                                               \
			               sizeof( int ) ), // it adds a dummy property at the start so you can define "empty" send_tables.

#define end_recv_table( )                                                                                                                            \
	}                                                                                                                                                \
	;                                                                                                                                                \
	recv_table.construct( recv_props + 1, sizeof( recv_props ) / sizeof( recv_prop ) - 1, p_recv_table_name );                                       \
	return 1;                                                                                                                                        \
	}

#define recvinfo( var_name ) #var_name, offsetof( current_recv_d_tstruct, var_name ), sizeof( ( ( current_recv_d_tstruct* )0 )->var_name )
#define recvinfo_name( var_name, remote_var_name )                                                                                                   \
#	remote_var_name, offsetof( current_recv_d_tstruct, var_name ), sizeof( ( ( current_recv_d_tstruct* )0 )->var_name )
#define recvinfo_string( var_name )        #var_name, offsetof( current_recv_d_tstruct, var_name ), stringbufsize( current_recv_d_tstruct, var_name )
#define recvinfo_bas_estruct( table_name ) recv_prop_data_table( "this", 0, 0, &reference_recv_table( table_name ) )
#define recvinfo_array( var_name )                                                                                                                   \
#	var_name, offsetof( current_recv_d_tstruct, var_name ), sizeof( ( ( current_recv_d_tstruct* )0 )->var_name[ 0 ] ),                              \
		sizeof( ( ( current_recv_d_tstruct* )0 )->var_name ) / sizeof( ( ( current_recv_d_tstruct* )0 )->var_name[ 0 ] )

// just specify the name and offset. used for strings and data tables.
#define recvinfo_nosize( var_name )                  #var_name, offsetof( current_recv_d_tstruct, var_name )
#define recvinfo_dt( var_name )                      recvinfo_nosize( var_name )
#define recvinfo_dtname( var_name, remote_var_name ) #remote_var_name, offsetof( current_recv_d_tstruct, var_name )

	void recv_proxy_float_to_float( const c_recv_proxy_data* p_data, void* p_struct, void* p_out );
	void recv_proxy_vector_to_vector( const c_recv_proxy_data* p_data, void* p_struct, void* p_out );
	void recv_proxy_vector_xy_to_vector_xy( const c_recv_proxy_data* p_data, void* p_struct, void* p_out );
	void recv_proxy_quaternion_to_quaternion( const c_recv_proxy_data* p_data, void* p_struct, void* p_out );
	void recv_proxy_int32_to_int8( const c_recv_proxy_data* p_data, void* p_struct, void* p_out );
	void recv_proxy_int32_to_int16( const c_recv_proxy_data* p_data, void* p_struct, void* p_out );
	void recv_proxy_string_to_string( const c_recv_proxy_data* p_data, void* p_struct, void* p_out );
	void recv_proxy_int32_to_int32( const c_recv_proxy_data* p_data, void* p_struct, void* p_out );
#ifdef supports_int64
	void recv_proxy_int64_to_int64( const c_recv_proxy_data* p_data, void* p_struct, void* p_out );
#endif

	// static_data_table does *p_out = p_data.
	void data_table_recv_proxy_static_data_table( const recv_prop* p_prop, void** p_out, void* p_data, int object_id );

	// pointer_data_table does *p_out = *((void**)p_data)   (ie: p_data is a pointer to the object to decode into).
	void data_table_recv_proxy_pointer_data_table( const recv_prop* p_prop, void** p_out, void* p_data, int object_id );

	recv_prop recv_prop_float( const char* p_var_name, int offset,
	                           int sizeof_var = -1, // handled by recvinfo macro, but set to sizeof_ignore if you don't want to bother.
	                           int flags = 0, recv_var_proxy_fn var_proxy = recv_proxy_float_to_float );

	recv_prop recv_prop_vector( const char* p_var_name, int offset,
	                            int sizeof_var = -1, // handled by recvinfo macro, but set to sizeof_ignore if you don't want to bother.
	                            int flags = 0, recv_var_proxy_fn var_proxy = recv_proxy_vector_to_vector );

	recv_prop recv_prop_vector_xy( const char* p_var_name, int offset,
	                               int sizeof_var = -1, // handled by recvinfo macro, but set to sizeof_ignore if you don't want to bother.
	                               int flags = 0, recv_var_proxy_fn var_proxy = recv_proxy_vector_xy_to_vector_xy );

// this is here so the recv_table can look more like the send_table.
#define recv_prop_q_angles recv_prop_vector

#if 0 // we can't ship this since it changes the size of dt_variant to be 20 bytes instead of 16 and that breaks mo_ds!!!

recv_prop recv_prop_quaternion(
	const char *p_var_name,
	int offset,
	int sizeof_var=sizeof_ignore,	// handled by recvinfo macro, but set to sizeof_ignore if you don't want to bother.
	int flags=0,
	recv_var_proxy_fn var_proxy=recv_proxy_quaternion_to_quaternion
	);
#endif

	recv_prop recv_prop_int( const char* p_var_name, int offset,
	                         int sizeof_var = sizeof_ignore, // handled by recvinfo macro, but set to sizeof_ignore if you don't want to bother.
	                         int flags = 0, recv_var_proxy_fn var_proxy = 0 );

	recv_prop recv_prop_string( const char* p_var_name, int offset, int buffer_size, int flags = 0,
	                            recv_var_proxy_fn var_proxy = recv_proxy_string_to_string );

	recv_prop recv_prop_data_table( const char* p_var_name, int offset, int flags, recv_table* p_table,
	                                data_table_recv_var_proxy_fn var_proxy = data_table_recv_proxy_static_data_table );

	recv_prop recv_prop_array3( const char* p_var_name, int offset, int sizeof_var, int elements, recv_prop p_array_prop,
	                            data_table_recv_var_proxy_fn var_proxy = data_table_recv_proxy_static_data_table );

	// use the macro to let it automatically generate a table name. you shouldn't
	// ever need to reference the table name. if you want to exclude this array, then
	// reference the name of the variable in var_template.
	recv_prop internal_recv_prop_array( const int element_count, const int element_stride, const char* p_name, array_length_recv_proxy_fn proxy );

//
// use this if you want to completely manage the way the array data is stored.
// you'll need to provide a proxy inside var_template that looks for 'i_element'
// to figure out where to store the specified element.
//
#define recv_prop_virtual_array( array_length_proxy, max_array_length, var_template, property_name )                                                 \
	var_template, internal_recv_prop_array( max_array_length, 0, #property_name, array_length_proxy )

// use this and pass the array name and it will figure out the count and stride automatically.
#define recv_prop_variable_length_array( array_length_proxy, var_template, array_name )                                                              \
	var_template,                                                                                                                                    \
		internal_recv_prop_array( sizeof( ( ( current_recv_d_tstruct* )0 )->array_name ) / propsizeof( current_recv_d_tstruct, array_name[ 0 ] ),    \
	                              propsizeof( current_recv_d_tstruct, array_name[ 0 ] ), #array_name, array_length_proxy )

// use this and pass the array name and it will figure out the count and stride automatically.
#define recv_prop_array( var_template, array_name ) recv_prop_variable_length_array( 0, var_template, array_name )

// use this one to specify the element count and stride manually.
#define recv_prop_array2( array_length_proxy, var_template, element_count, element_stride, array_name )                                              \
	var_template, internal_recv_prop_array( element_count, element_stride, #array_name, array_length_proxy )

	// ---------------------------------------------------------------------------------------- //
	// inlines.
	// ---------------------------------------------------------------------------------------- //

	inline void recv_prop::init_array( int nelements, int element_stride )
	{
		recv_type      = dpt_array;
		nelements      = nelements;
		element_stride = element_stride;
	}

	inline int recv_prop::get_num_elements( ) const
	{
		return elements;
	}

	inline void recv_prop::set_num_elements( int nelements )
	{
		elements = nelements;
	}

	inline int recv_prop::get_element_stride( ) const
	{
		return element_stride;
	}

	inline void recv_prop::set_element_stride( int stride )
	{
		element_stride = stride;
	}

	inline int recv_prop::get_flags( ) const
	{
		return flags;
	}

	inline const char* recv_prop::get_name( ) const
	{
		return var_name;
	}

	inline int recv_prop::get_type( ) const
	{
		return recv_type;
	}

	inline recv_table* recv_prop::get_data_table( ) const
	{
		return data_table;
	}

	inline void recv_prop::set_data_table( recv_table* p_table )
	{
		data_table = p_table;
	}

	inline recv_var_proxy_fn recv_prop::get_proxy_fn( ) const
	{
		return proxy_fn;
	}

	inline void recv_prop::set_proxy_fn( recv_var_proxy_fn fn )
	{
		proxy_fn = fn;
	}

	inline data_table_recv_var_proxy_fn recv_prop::get_data_table_proxy_fn( ) const
	{
		return data_table_proxy_fn;
	}

	inline void recv_prop::set_data_table_proxy_fn( data_table_recv_var_proxy_fn fn )
	{
		data_table_proxy_fn = fn;
	}

	inline int recv_prop::get_offset( ) const
	{
		return offset;
	}

	inline void recv_prop::set_offset( int o )
	{
		offset = o;
	}

	inline recv_prop* recv_prop::get_array_prop( ) const
	{
		return array_prop;
	}

	inline void recv_prop::set_array_prop( recv_prop* p_prop )
	{
		array_prop = p_prop;
	}

	inline void recv_prop::set_array_length_proxy( array_length_recv_proxy_fn proxy )
	{
		array_length_proxy = proxy;
	}

	inline array_length_recv_proxy_fn recv_prop::get_array_length_proxy( ) const
	{
		return array_length_proxy;
	}

	inline bool recv_prop::is_inside_array( ) const
	{
		return inside_array;
	}

	inline void recv_prop::set_inside_array( )
	{
		inside_array = true;
	}

	inline const void* recv_prop::get_extra_data( ) const
	{
		return extra_data;
	}

	inline void recv_prop::set_extra_data( const void* p_data )
	{
		extra_data = p_data;
	}

	inline const char* recv_prop::get_parent_array_prop_name( )
	{
		return parent_array_prop_name;
	}

	inline void recv_prop::set_parent_array_prop_name( const char* p_array_prop_name )
	{
		parent_array_prop_name = p_array_prop_name;
	}
} // namespace sdk
