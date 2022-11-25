#ifndef WEDNESDAY_WTF_DT_COMMON_HPP
#define WEDNESDAY_WTF_DT_COMMON_HPP

#include <stdio.h>

namespace sdk
{

// max number of properties in a datatable and its children.
#define max_datatables      1024 // must be a power of 2.
#define max_datatable_props 4096

#define max_array_elements 2048 // a network array should have more that 1024 elements

#define high_default -121121.121121f

#define bits_fullres    -1 // use the full resolution of the type being encoded.
#define bits_worldcoord -2 // encode as a world coordinate.

#define dt_max_string_bits       9
#define dt_max_string_buffersize ( 1 << dt_max_string_bits ) // maximum length of a string that can be sent.

#define stringbufsize( class_name, var_name ) sizeof( ( ( class_name* )0 )->var_name )

// gets the size of a variable in a class.
#define propsizeof( class_name, var_name ) sizeof( ( ( class_name* )0 )->var_name )

// send_prop::m_flags.
#define sprop_unsigned ( 1 << 0 ) // unsigned integer data.

#define sprop_coord                                                                                                                                  \
	( 1 << 1 ) // if this is set, the float/vector is treated like a world coordinate.
	           // note that the bit count is ignored in this case.

#define sprop_noscale ( 1 << 2 ) // for floating point, don't scale into range, just take value as is.

#define sprop_rounddown ( 1 << 3 ) // for floating point, limit high value to range minus one bit unit

#define sprop_roundup ( 1 << 4 ) // for floating point, limit low value to range minus one bit unit

#define sprop_normal ( 1 << 5 ) // if this is set, the vector is treated like a normal (only valid for vectors)

#define sprop_exclude ( 1 << 6 ) // this is an exclude prop (not exclud_ed, but it points at another prop to be excluded).

#define sprop_xyze ( 1 << 7 ) // use xyz/exponent encoding for vectors.

#define sprop_insidearray                                                                                                                            \
	( 1 << 8 ) // this tells us that the property is inside an array, so it shouldn't be put into the
	           // flattened property list. its array will point at it when it needs to.

#define sprop_proxy_always_yes                                                                                                                       \
	( 1 << 9 ) // set for datatable props using one of the default datatable proxies like
	           // send_proxy_data_table_to_data_table that always send the data to all clients.

#define sprop_changes_often ( 1 << 10 ) // this is an often changed field, moved to head of sendtable so it gets a small index

#define sprop_is_a_vector_elem ( 1 << 11 ) // set automatically if sprop_vectorelem is used.

#define sprop_collapsible                                                                                                                            \
	( 1 << 12 ) // set automatically if it's a datatable with an offset of 0 that doesn't change the pointer
	            // (ie: for all automatically-chained base classes).
	            // in this case, it can get rid of this send_prop_data_table altogether and spare the
	            // trouble of walking the hierarchy more than necessary.

#define sprop_coord_mp ( 1 << 13 ) // like sprop_coord, but special handling for multiplayer games
#define sprop_coord_mp_lowprecision                                                                                                                  \
	( 1 << 14 ) // like sprop_coord, but special handling for multiplayer games where the fractional component only gets a 3 bits instead of 5
#define sprop_coord_mp_integral ( 1 << 15 ) // sprop_coord_mp, but coordinates are rounded to integral boundaries

#define sprop_varint sprop_normal // reuse existing flag so we don't break demo. note you want to include sprop_unsigned if needed, its more efficient

#define sprop_numflagbits_networked 16

// this is server side only, it's used to mark properties whose send_proxy_* functions encode against gp_globals->tickcount (the only ones that
// currently do this are
//  m_fl_anim_time and m_fl_simulation_time.  mo_ds shouldn't need to mess with this probably
#define sprop_encoded_against_tickcount ( 1 << 16 )

// see sprop_numflagbits_networked for the ones which are networked
#define sprop_numflagbits 17

// used by the send_prop and recv_prop functions to disable debug checks on type sizes.
#define sizeof_ignore -1

// use this to extern send and receive datatables, and reference them.
#define extern_send_table( table_name )                                                                                                              \
	namespace table_name                                                                                                                             \
	{                                                                                                                                                \
		extern send_table g_send_table;                                                                                                              \
	}
#define extern_recv_table( table_name )                                                                                                              \
	namespace table_name                                                                                                                             \
	{                                                                                                                                                \
		extern recv_table g_recv_table;                                                                                                              \
	}

#define reference_send_table( table_name ) table_name::g_send_table
#define reference_recv_table( table_name ) table_name::g_recv_table

	class send_prop;

	// the day we do this, we break all mods until they recompile.
	//#define supports_int64

	typedef enum {
		dpt_int = 0,
		dpt_float,
		dpt_vector,
		dpt_vector_xy, // only encodes the xy of a vector, ignores z
		dpt_string,
		dpt_array, // an array of the base types (can't be of datatables).
		dpt_data_table,

		dpt_num_send_prop_types

	} send_prop_type;

	class d_variant
	{
	public:
		d_variant( )
		{
			m_type = dpt_float;
		}
		d_variant( float val )
		{
			m_type  = dpt_float;
			m_float = val;
		}

		const char* to_string( )
		{
			static char text[ 128 ];

			switch ( m_type ) {
			case dpt_int:
				// q_snprintf( text, sizeof(text), "%i", m_int );
				break;
			case dpt_float:
				// q_snprintf( text, sizeof(text), "%.3f", m_float );
				break;
			case dpt_vector:
				// q_snprintf( text, sizeof(text), "(%.3f,%.3f,%.3f)",
				// m_vector[0], m_vector[1], m_vector[2] );
				break;
			case dpt_vector_xy:
				// q_snprintf( text, sizeof(text), "(%.3f,%.3f)",
				// m_vector[0], m_vector[1] );
				break;
			case dpt_string:
				if ( string )
					return string;
				else
					return "null";
				break;
			case dpt_array:
				// q_snprintf( text, sizeof(text), "array" );
				break;
			case dpt_data_table:
				// q_snprintf( text, sizeof(text), "data_table" );
				break;
			default:
				// q_snprintf( text, sizeof(text), "d_variant type %i unknown", m_type );
				break;
			}

			return text;
		}

		union {
			float m_float;
			int m_int;
			const char* string;
			void* data; // for data_tables.
			float m_vector[ 3 ];
		};
		send_prop_type m_type;
	};

	// this can be used to set the # of bits used to transmit a number between 0 and n_max_elements-1.
	inline int num_bits_for_count( int n_max_elements )
	{
		int n_bits = 0;
		while ( n_max_elements > 0 ) {
			++n_bits;
			n_max_elements >>= 1;
		}
		return n_bits;
	}
} // namespace sdk

#endif // WEDNESDAY_WTF_DT_COMMON_HPP
