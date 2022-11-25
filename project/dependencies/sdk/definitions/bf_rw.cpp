#include "../structs/bf_rw.hpp"

using namespace sdk;

#pragma warning( disable : 4244 )

// #if defined(plat_little_endian)

#ifndef worldsize_h
#	define worldsize_h

// these definitions must match the coordinate message sizes in coordsize.h

// following values should be +16384, -16384, +15/16, -15/16
// note that if this goes any bigger then disk nodes/leaves cannot use shorts to store the bounds
#	define max_coord_integer  ( 16384 )
#	define min_coord_integer  ( -max_coord_integer )
#	define max_coord_fraction ( 1.0 - ( 1.0 / 16.0 ) )
#	define min_coord_fraction ( -1.0 + ( 1.0 / 16.0 ) )

#	define max_coord_float ( 16384.0f )
#	define min_coord_float ( -max_coord_float )

// width of the coord system, which is too big to send as a client/server coordinate value
#	define coord_extent ( 2 * max_coord_integer )

// maximum traceable distance ( assumes cubic world and trace from one corner to opposite )
// coord_extent * sqrt(3)
#	define max_trace_length ( 1.732050807569 * coord_extent )

// this value is the longest possible range (limited by max valid coordinate number, not 2x)
#	define max_coord_range ( max_coord_integer )

#	define test_coord( v )                                                                                                                          \
		( ( ( v ).x >= min_coord_integer * 2 ) && ( ( v ).x <= max_coord_integer * 2 ) && ( ( v ).y >= min_coord_integer * 2 ) &&                    \
		  ( ( v ).y <= max_coord_integer * 2 ) && ( ( v ).z >= min_coord_integer * 2 ) && ( ( v ).z <= max_coord_integer * 2 ) )

#	define assert_coord( v ) assert( test_coord( v ) );

#endif // worldsize_h

#ifndef coordsize_h
#	define coordsize_h

// overall coordinate size limits used in common.c msg_*bit_coord() routines (and someday the hud)
#	define coord_integer_bits    14
#	define coord_fractional_bits 5
#	define coord_denominator     ( 1 << ( coord_fractional_bits ) )
#	define coord_resolution      ( 1.0 / ( coord_denominator ) )

// special threshold for networking multiplayer origins
#	define coord_integer_bits_mp                 11
#	define coord_fractional_bits_mp_lowprecision 3
#	define coord_denominator_lowprecision        ( 1 << ( coord_fractional_bits_mp_lowprecision ) )
#	define coord_resolution_lowprecision         ( 1.0 / ( coord_denominator_lowprecision ) )

#	define normal_fractional_bits 11
#	define normal_denominator     ( ( 1 << ( normal_fractional_bits ) ) - 1 )
#	define normal_resolution      ( 1.0 / ( normal_denominator ) )

// this is limited by the network fractional bits used for coords
// because net coords will be only be accurate to 5 bits fractional
// standard collision test epsilon
// 1/32nd inch collision epsilon
#	define dist_epsilon ( 0.03125 )

// verify that coordsize.h and worldsize.h are consistently defined
#	if ( max_coord_integer != ( 1 << coord_integer_bits ) )
#		error max_coord_integer does not match coord_integer_bits
#	endif

///////////////////////////////////////////////////////////////////////////////////////////////////////
// the following are bit packing diagrams for client/server coordinate bit_field messages
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//							"coordinates" = +/-16384.9375	(21 bits max)
//
// | integer_flag_bit:1 | fraction_flag_bit:1 | sign_bit:1 | integer_field:14 | fraction_part:4 |		total
// --------------------------------------------------------------------------------------------------
//			0					0				-				-				-				2
//			0					1				x				-				xxxx			7
//			1					0				x		xxxxxxxxxxxxx			-				17
//			1					1				x		xxxxxxxxxxxxx			xxxx			21
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//							"vec3_coordinate" = up to 3 coordinates (66 bits max)
//
// | non_zero_x:1 | non_zero_y:1 | non_zero_z:1 |  0..3 "coordinates"	|	bit_field total
// -------------------------------------------------------------------------------
//			0			0				0			-					3
//			0			0				1			7..21 bits			10..24
//			0			1				0			7..21 bits			10..24
//			1			0				0			7..21 bits			10..24
//			0			1				1			14..42 bits			17..45
//			1			1				0			14..42 bits			17..45
//			1			0				1			14..42 bits			17..45
//			1			1				1			21..63 bits			24..66
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
// the following are bit packing diagrams for client/server normal bit_field messages
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//							"normals" = +/-1.0	(12 bits total)
//
// the only gotcha here is that normalization occurs so that
// 011111111111 = +1.0 and 1111111111111 = -1.0
//
// | sign_bit:1 | fraction_part:11 |		total
// --------------------------------------------------------------------------------------------------
//			1		xxxxxxxxxxx			12
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//							"vec3_normal" = up to 3 coordinates (27 bits max)
//
// | non_zero_x:1 | non_zero_y:1 |  0..2 "coordinates"	| z sign bit |	bit_field total
// -------------------------------------------------------------------------------
//			0			0				-					x			3
//			0			1			12 bits					x			14
//			1			0			12 bits					x			14
//			1			1			24 bits					x			27
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // coordsize_h

// fixme: can't use this until we get multithreaded allocations in tier0 working for tools
// this is used by vvis and fails to link
// note: this must be the last file included!!!
// #include "tier0/memdbgon.h"

#ifdef _x360
// mandatory ... wary of above comment and isolating, tier0 is built as mt though
#	include "tier0/memdbgon.h"
#endif

#if _win32
#	define fast_bit_scan 1
#	if _x360
#		define count_leading_zeros( x ) _count_leading_zeros( x )
inline unsigned int count_trailing_zeros( unsigned int elem )
{
	// this implements count_trailing_zeros() / bit_scan_forward()
	unsigned int mask = elem - 1;
	unsigned int comp = ~elem;
	elem              = mask & comp;
	return ( 32 - _count_leading_zeros( elem ) );
}
#	else
#		include <intrin.h>
#		pragma intrinsic( _bit_scan_reverse )
#		pragma intrinsic( _bit_scan_forward )

inline unsigned int count_leading_zeros( unsigned int x )
{
	unsigned long first_bit;
	if ( _bit_scan_reverse( &first_bit, x ) )
		return 31 - first_bit;
	return 32;
}
inline unsigned int count_trailing_zeros( unsigned int elem )
{
	unsigned long out;
	if ( _bit_scan_forward( &out, elem ) )
		return out;
	return 32;
}

/// compatability funcs

inline void q_memcpy( void* dest, void* src, int count ) // quake memcpy
{
	int i;

	if ( ( ( ( long )dest | ( long )src | count ) & 3 ) == 0 ) {
		count >>= 2;
		for ( i = 0; i < count; i++ ) {
			( ( int* )dest )[ i ] = ( ( int* )src )[ i ];
		}
	} else {
		for ( i = 0; i < count; i++ ) {
			( reinterpret_cast< std::byte* >( dest ) )[ i ] =
				( reinterpret_cast< std::byte* >( src ) )[ i ]; // c style cast crashes compiler... but reinterpret_cast doesn't? what mscv?????
		}
	}
}

bool is_pc( )
{
	return true;
}

#	endif
#else
#	define fast_bit_scan 0
#endif

inline int bit_for_bitnum( int bitnum )
{
	return 1;
	// return get_bit_for_bitnum(bitnum);
}

// #define bb_profiling

unsigned long g_little_bits[ 32 ];

// precalculated bit masks for write_u_bit_long. using these tables instead of
// doing the calculations gives a 33% speedup in write_u_bit_long.
unsigned long g_bit_write_masks[ 32 ][ 33 ];

// (1 << i) - 1
unsigned long g_extra_masks[ 33 ];

class c_bit_write_masks_init
{
public:
	c_bit_write_masks_init( )
	{
		for ( unsigned int startbit = 0; startbit < 32; startbit++ ) {
			for ( unsigned int n_bits_left = 0; n_bits_left < 33; n_bits_left++ ) {
				unsigned int endbit                          = startbit + n_bits_left;
				g_bit_write_masks[ startbit ][ n_bits_left ] = bit_for_bitnum( startbit ) - 1;
				if ( endbit < 32 )
					g_bit_write_masks[ startbit ][ n_bits_left ] |= ~( bit_for_bitnum( endbit ) - 1 );
			}
		}

		for ( unsigned int mask_bit = 0; mask_bit < 32; mask_bit++ )
			g_extra_masks[ mask_bit ] = bit_for_bitnum( mask_bit ) - 1;
		g_extra_masks[ 32 ] = ~0ul;

		for ( unsigned int little_bit = 0; little_bit < 32; little_bit++ ) {
			store_little_d_word( &g_little_bits[ little_bit ], 0, 1u << little_bit );
		}
	}
};
static c_bit_write_masks_init g_bit_write_masks_init;

// ---------------------------------------------------------------------------------------- //
// bf_write
// ---------------------------------------------------------------------------------------- //

bf_write::bf_write( )
{
	m_p_data               = NULL;
	m_n_data_bytes         = 0;
	m_n_data_bits          = -1; // set to -1 so we generate overflow on any operation
	m_i_cur_bit            = 0;
	m_b_overflow           = false;
	m_b_assert_on_overflow = true;
	m_p_debug_name         = NULL;
}

bf_write::bf_write( const char* p_debug_name, void* p_data, int n_bytes, int n_bits )
{
	m_b_assert_on_overflow = true;
	m_p_debug_name         = p_debug_name;
	start_writing( p_data, n_bytes, 0, n_bits );
}

bf_write::bf_write( void* p_data, int n_bytes, int n_bits )
{
	m_b_assert_on_overflow = true;
	m_p_debug_name         = NULL;
	start_writing( p_data, n_bytes, 0, n_bits );
}

void bf_write::start_writing( void* p_data, int n_bytes, int i_start_bit, int n_bits )
{
	// make sure it's dword aligned and padded.
	// assert((n_bytes % 4) == 0);
	// assert(((unsigned long)p_data & 3) == 0);

	// the writing code will overrun the end of the buffer if it isn't dword aligned, so truncate to force alignment
	n_bytes &= ~3;

	m_p_data       = ( unsigned long* )p_data;
	m_n_data_bytes = n_bytes;

	if ( n_bits == -1 ) {
		m_n_data_bits = n_bytes << 3;
	} else {
		// assert(n_bits <= n_bytes * 8);
		m_n_data_bits = n_bits;
	}

	m_i_cur_bit  = i_start_bit;
	m_b_overflow = false;
}

void bf_write::reset( )
{
	m_i_cur_bit  = 0;
	m_b_overflow = false;
}

void bf_write::set_assert_on_overflow( bool b_assert )
{
	m_b_assert_on_overflow = b_assert;
}

const char* bf_write::get_debug_name( )
{
	return m_p_debug_name;
}

void bf_write::set_debug_name( const char* p_debug_name )
{
	m_p_debug_name = p_debug_name;
}

void bf_write::seek_to_bit( int bit_pos )
{
	m_i_cur_bit = bit_pos;
}

// sign bit comes first
void bf_write::write_s_bit_long( int data, int numbits )
{
	// force the sign-extension bit to be correct even in the case of overflow.
	int n_value          = data;
	int n_preserve_bits  = ( 0x7fffffff >> ( 32 - numbits ) );
	int n_sign_extension = ( n_value >> 31 ) & ~n_preserve_bits;
	n_value &= n_preserve_bits;
	n_value |= n_sign_extension;

	// assert_msg2(n_value == data, "write_s_bit_long: 0x%08x does not fit in %d bits", data, numbits);

	write_u_bit_long( n_value, numbits, false );
}

void bf_write::write_var_int32( std::uint32_t data )
{
	// check if align and we have room, slow path if not
	if ( ( m_i_cur_bit & 7 ) == 0 && ( m_i_cur_bit + 5 * 8 ) <= m_n_data_bits ) {
		std::uint8_t* target = ( ( std::uint8_t* )m_p_data ) + ( m_i_cur_bit >> 3 );

		target[ 0 ] = static_cast< std::uint8_t >( data | 0x80 );
		if ( data >= ( 1 << 7 ) ) {
			target[ 1 ] = static_cast< std::uint8_t >( ( data >> 7 ) | 0x80 );
			if ( data >= ( 1 << 14 ) ) {
				target[ 2 ] = static_cast< std::uint8_t >( ( data >> 14 ) | 0x80 );
				if ( data >= ( 1 << 21 ) ) {
					target[ 3 ] = static_cast< std::uint8_t >( ( data >> 21 ) | 0x80 );
					if ( data >= ( 1 << 28 ) ) {
						target[ 4 ] = static_cast< std::uint8_t >( data >> 28 );
						m_i_cur_bit += 5 * 8;
						return;
					} else {
						target[ 3 ] &= 0x7f;
						m_i_cur_bit += 4 * 8;
						return;
					}
				} else {
					target[ 2 ] &= 0x7f;
					m_i_cur_bit += 3 * 8;
					return;
				}
			} else {
				target[ 1 ] &= 0x7f;
				m_i_cur_bit += 2 * 8;
				return;
			}
		} else {
			target[ 0 ] &= 0x7f;
			m_i_cur_bit += 1 * 8;
			return;
		}
	} else // slow path
	{
		while ( data > 0x7f ) {
			write_u_bit_long( ( data & 0x7f ) | 0x80, 8 );
			data >>= 7;
		}
		write_u_bit_long( data & 0x7f, 8 );
	}
}

void bf_write::write_var_int64( std::uint64_t data )
{
	// check if align and we have room, slow path if not
	if ( ( m_i_cur_bit & 7 ) == 0 && ( m_i_cur_bit + 10 * 8 ) <= m_n_data_bits ) {
		std::uint8_t* target = ( ( std::uint8_t* )m_p_data ) + ( m_i_cur_bit >> 3 );

		// splitting into 32-bit pieces gives better performance on 32-bit
		// processors.
		std::uint32_t part0 = static_cast< std::uint32_t >( data );
		std::uint32_t part1 = static_cast< std::uint32_t >( data >> 28 );
		std::uint32_t part2 = static_cast< std::uint32_t >( data >> 56 );

		int size;

		// here we can't really optimize for small numbers, since the data is
		// split into three parts.  cheking for numbers < 128, for instance,
		// would require three comparisons, since you'd have to make sure part1
		// and part2 are zero.  however, if the caller is using 64-bit integers,
		// it is likely that they expect the numbers to often be very large, so
		// we probably don't want to optimize for small numbers anyway.  thus,
		// we end up with a hardcoded binary search tree...
		if ( part2 == 0 ) {
			if ( part1 == 0 ) {
				if ( part0 < ( 1 << 14 ) ) {
					if ( part0 < ( 1 << 7 ) ) {
						size = 1;
						goto size1;
					} else {
						size = 2;
						goto size2;
					}
				} else {
					if ( part0 < ( 1 << 21 ) ) {
						size = 3;
						goto size3;
					} else {
						size = 4;
						goto size4;
					}
				}
			} else {
				if ( part1 < ( 1 << 14 ) ) {
					if ( part1 < ( 1 << 7 ) ) {
						size = 5;
						goto size5;
					} else {
						size = 6;
						goto size6;
					}
				} else {
					if ( part1 < ( 1 << 21 ) ) {
						size = 7;
						goto size7;
					} else {
						size = 8;
						goto size8;
					}
				}
			}
		} else {
			if ( part2 < ( 1 << 7 ) ) {
				size = 9;
				goto size9;
			} else {
				size = 10;
				goto size10;
			}
		}

		// assert_fatal_msg(false, "can't get here.");

	size10:
		target[ 9 ] = static_cast< std::uint8_t >( ( part2 >> 7 ) | 0x80 );
	size9:
		target[ 8 ] = static_cast< std::uint8_t >( ( part2 ) | 0x80 );
	size8:
		target[ 7 ] = static_cast< std::uint8_t >( ( part1 >> 21 ) | 0x80 );
	size7:
		target[ 6 ] = static_cast< std::uint8_t >( ( part1 >> 14 ) | 0x80 );
	size6:
		target[ 5 ] = static_cast< std::uint8_t >( ( part1 >> 7 ) | 0x80 );
	size5:
		target[ 4 ] = static_cast< std::uint8_t >( ( part1 ) | 0x80 );
	size4:
		target[ 3 ] = static_cast< std::uint8_t >( ( part0 >> 21 ) | 0x80 );
	size3:
		target[ 2 ] = static_cast< std::uint8_t >( ( part0 >> 14 ) | 0x80 );
	size2:
		target[ 1 ] = static_cast< std::uint8_t >( ( part0 >> 7 ) | 0x80 );
	size1:
		target[ 0 ] = static_cast< std::uint8_t >( ( part0 ) | 0x80 );

		target[ size - 1 ] &= 0x7f;
		m_i_cur_bit += size * 8;
	} else // slow path
	{
		while ( data > 0x7f ) {
			write_u_bit_long( ( data & 0x7f ) | 0x80, 8 );
			data >>= 7;
		}
		write_u_bit_long( data & 0x7f, 8 );
	}
}

void bf_write::write_signed_var_int32( std::int32_t data )
{
	write_var_int32( zig_zag_encode32( data ) );
}

void bf_write::write_signed_var_int64( std::int64_t data )
{
	write_var_int64( zig_zag_encode64( data ) );
}

int bf_write::byte_size_var_int32( std::uint32_t data )
{
	int size = 1;
	while ( data > 0x7f ) {
		size++;
		data >>= 7;
	}
	return size;
}

int bf_write::byte_size_var_int64( std::uint64_t data )
{
	int size = 1;
	while ( data > 0x7f ) {
		size++;
		data >>= 7;
	}
	return size;
}

int bf_write::byte_size_signed_var_int32( std::int32_t data )
{
	return byte_size_var_int32( zig_zag_encode32( data ) );
}

int bf_write::byte_size_signed_var_int64( std::int64_t data )
{
	return byte_size_var_int64( zig_zag_encode64( data ) );
}

void bf_write::write_bit_long( unsigned int data, int numbits, bool b_signed )
{
	if ( b_signed )
		write_s_bit_long( ( int )data, numbits );
	else
		write_u_bit_long( data, numbits );
}

bool bf_write::write_bits( const void* p_in_data, int n_bits )
{
#if defined( bb_profiling )
	vprof( "bf_write::write_bits" );
#endif

	unsigned char* p_out = ( unsigned char* )p_in_data;
	int n_bits_left      = n_bits;

	// bounds checking..
	if ( ( m_i_cur_bit + n_bits ) > m_n_data_bits ) {
		// call_error_handler(bitbuferror_buffer_overrun, get_debug_name());
		return false;
	}

	// align output to dword boundary
	while ( ( ( unsigned long )p_out & 3 ) != 0 && n_bits_left >= 8 ) {
		write_u_bit_long( *p_out, 8, false );
		++p_out;
		n_bits_left -= 8;
	}

	if ( ( n_bits_left >= 32 ) && ( m_i_cur_bit & 7 ) == 0 ) {
		// current bit is byte aligned, do block copy
		int numbytes = n_bits_left >> 3;
		int numbits  = numbytes << 3;

		memcpy( ( char* )m_p_data + ( m_i_cur_bit >> 3 ), p_out, numbytes );
		p_out += numbytes;
		n_bits_left -= numbits;
		m_i_cur_bit += numbits;
	}

	// x360tbd: can't write dwords in write_bits because they'll get swapped
	if ( n_bits_left >= 32 ) {
		unsigned long i_bits_right   = ( m_i_cur_bit & 31 );
		unsigned long i_bits_left    = 32 - i_bits_right;
		unsigned long bit_mask_left  = g_bit_write_masks[ i_bits_right ][ 32 ];
		unsigned long bit_mask_right = g_bit_write_masks[ 0 ][ i_bits_right ];

		unsigned long* p_data = &m_p_data[ m_i_cur_bit >> 5 ];

		// read dwords.
		while ( n_bits_left >= 32 ) {
			unsigned long cur_data = *( unsigned long* )p_out;
			p_out += sizeof( unsigned long );

			*p_data &= bit_mask_left;
			*p_data |= cur_data << i_bits_right;

			p_data++;

			if ( i_bits_left < 32 ) {
				cur_data >>= i_bits_left;
				*p_data &= bit_mask_right;
				*p_data |= cur_data;
			}

			n_bits_left -= 32;
			m_i_cur_bit += 32;
		}
	}

	// write remaining bytes
	while ( n_bits_left >= 8 ) {
		write_u_bit_long( *p_out, 8, false );
		++p_out;
		n_bits_left -= 8;
	}

	// write remaining bits
	if ( n_bits_left ) {
		write_u_bit_long( *p_out, n_bits_left, false );
	}

	return !is_overflowed( );
}

bool bf_write::write_bits_from_buffer( bf_read* p_in, int n_bits )
{
	// this could be optimized a little by
	while ( n_bits > 32 ) {
		write_u_bit_long( p_in->read_u_bit_long( 32 ), 32 );
		n_bits -= 32;
	}

	write_u_bit_long( p_in->read_u_bit_long( n_bits ), n_bits );
	return !is_overflowed( ) && !p_in->is_overflowed( );
}

void bf_write::write_bit_angle( float f_angle, int numbits )
{
	int d;
	unsigned int mask;
	unsigned int shift;

	shift = bit_for_bitnum( numbits );
	mask  = shift - 1;

	d = ( int )( ( f_angle / 360.0 ) * shift );
	d &= mask;

	write_u_bit_long( ( unsigned int )d, numbits );
}

void bf_write::write_bit_coord_mp( const float f, bool b_integral, bool b_low_precision )
{
#if defined( bb_profiling )
	vprof( "bf_write::write_bit_coord_mp" );
#endif
	int signbit  = ( f <= -( b_low_precision ? coord_resolution_lowprecision : coord_resolution ) );
	int intval   = ( int )abs( f );
	int fractval = b_low_precision ? ( abs( ( int )( f * coord_denominator_lowprecision ) ) & ( coord_denominator_lowprecision - 1 ) )
	                               : ( abs( ( int )( f * coord_denominator ) ) & ( coord_denominator - 1 ) );

	bool b_in_bounds = intval < ( 1 << coord_integer_bits_mp );

	unsigned int bits, numbits;

	if ( b_integral ) {
		// integer encoding: in-bounds bit, nonzero bit, optional sign bit + integer value bits
		if ( intval ) {
			// adjust the integers from [1..max_coord_value] to [0..max_coord_value-1]
			--intval;
			bits    = intval * 8 + signbit * 4 + 2 + b_in_bounds;
			numbits = 3 + ( b_in_bounds ? coord_integer_bits_mp : coord_integer_bits );
		} else {
			bits    = b_in_bounds;
			numbits = 2;
		}
	} else {
		// float encoding: in-bounds bit, integer bit, sign bit, fraction value bits, optional integer value bits
		if ( intval ) {
			// adjust the integers from [1..max_coord_value] to [0..max_coord_value-1]
			--intval;
			bits = intval * 8 + signbit * 4 + 2 + b_in_bounds;
			bits += b_in_bounds ? ( fractval << ( 3 + coord_integer_bits_mp ) ) : ( fractval << ( 3 + coord_integer_bits ) );
			numbits = 3 + ( b_in_bounds ? coord_integer_bits_mp : coord_integer_bits ) +
			          ( b_low_precision ? coord_fractional_bits_mp_lowprecision : coord_fractional_bits );
		} else {
			bits    = fractval * 8 + signbit * 4 + 0 + b_in_bounds;
			numbits = 3 + ( b_low_precision ? coord_fractional_bits_mp_lowprecision : coord_fractional_bits );
		}
	}

	write_u_bit_long( bits, numbits );
}

void bf_write::write_bit_coord( const float f )
{
#if defined( bb_profiling )
	vprof( "bf_write::write_bit_coord" );
#endif
	int signbit  = ( f <= -coord_resolution );
	int intval   = ( int )abs( f );
	int fractval = abs( ( int )( f * coord_denominator ) ) & ( coord_denominator - 1 );

	// send the bit flags that indicate whether we have an integer part and/or a fraction part.
	write_one_bit( intval );
	write_one_bit( fractval );

	if ( intval || fractval ) {
		// send the sign bit
		write_one_bit( signbit );

		// send the integer if we have one.
		if ( intval ) {
			// adjust the integers from [1..max_coord_value] to [0..max_coord_value-1]
			intval--;
			write_u_bit_long( ( unsigned int )intval, coord_integer_bits );
		}

		// send the fraction if we have one
		if ( fractval ) {
			write_u_bit_long( ( unsigned int )fractval, coord_fractional_bits );
		}
	}
}

void bf_write::write_bit_vec3_coord( const vector& fa )
{
	int xflag, yflag, zflag;

	xflag = ( fa.x >= coord_resolution ) || ( fa.x <= -coord_resolution );
	yflag = ( fa.y >= coord_resolution ) || ( fa.y <= -coord_resolution );
	zflag = ( fa.z >= coord_resolution ) || ( fa.z <= -coord_resolution );

	write_one_bit( xflag );
	write_one_bit( yflag );
	write_one_bit( zflag );

	if ( xflag )
		write_bit_coord( fa.x );
	if ( yflag )
		write_bit_coord( fa.y );
	if ( zflag )
		write_bit_coord( fa.z );
}

void bf_write::write_bit_normal( float f )
{
	int signbit = ( f <= -normal_resolution );

	// note: since +/-1 are valid values for a normal, i'm going to encode that as all ones
	unsigned int fractval = abs( ( int )( f * normal_denominator ) );

	// clamp..
	if ( fractval > normal_denominator )
		fractval = normal_denominator;

	// send the sign bit
	write_one_bit( signbit );

	// send the fractional component
	write_u_bit_long( fractval, normal_fractional_bits );
}

void bf_write::write_bit_vec3_normal( const vector& fa )
{
	int xflag, yflag;

	xflag = ( fa.x >= normal_resolution ) || ( fa.x <= -normal_resolution );
	yflag = ( fa.y >= normal_resolution ) || ( fa.y <= -normal_resolution );

	write_one_bit( xflag );
	write_one_bit( yflag );

	if ( xflag )
		write_bit_normal( fa.x );
	if ( yflag )
		write_bit_normal( fa.y );

	// write z sign bit
	int signbit = ( fa.z <= -normal_resolution );
	write_one_bit( signbit );
}

void bf_write::write_bit_angles( const vector& fa )
{
	// fixme:
	vector tmp{ fa.x, fa.y, fa.z };
	write_bit_vec3_coord( tmp );
}

void bf_write::write_char( int val )
{
	write_s_bit_long( val, sizeof( char ) << 3 );
}

void bf_write::write_byte( int val )
{
	write_u_bit_long( val, sizeof( unsigned char ) << 3 );
}

void bf_write::write_short( int val )
{
	write_s_bit_long( val, sizeof( short ) << 3 );
}

void bf_write::write_word( int val )
{
	write_u_bit_long( val, sizeof( unsigned short ) << 3 );
}

void bf_write::write_long( long val )
{
	write_s_bit_long( val, sizeof( long ) << 3 );
}

void bf_write::write_long_long( std::int64_t val )
{
	unsigned int* p_longs = ( unsigned int* )&val;

	// insert the two dwords according to network endian
	const short endian_index = 0x0100;
	std::byte* idx           = ( std::byte* )&endian_index;
	write_u_bit_long( p_longs[ ( *( ( int* )idx ) )++ ], sizeof( long ) << 3 );
	write_u_bit_long( p_longs[ *( ( int* )idx ) ], sizeof( long ) << 3 );
}

void bf_write::write_float( float val )
{
	write_bits( &val, sizeof( val ) << 3 );
}

bool bf_write::write_bytes( const void* p_buf, int n_bytes )
{
	return write_bits( p_buf, n_bytes << 3 );
}

bool bf_write::write_string( const char* p_str )
{
	if ( p_str ) {
		do {
			write_char( *p_str );
			++p_str;
		} while ( *( p_str - 1 ) != 0 );
	} else {
		write_char( 0 );
	}

	return !is_overflowed( );
}

// ---------------------------------------------------------------------------------------- //
// bf_read
// ---------------------------------------------------------------------------------------- //

bf_read::bf_read( )
{
	m_p_data               = NULL;
	m_n_data_bytes         = 0;
	m_n_data_bits          = -1; // set to -1 so we overflow on any operation
	m_i_cur_bit            = 0;
	m_b_overflow           = false;
	m_b_assert_on_overflow = true;
	m_p_debug_name         = NULL;
}

bf_read::bf_read( const void* p_data, int n_bytes, int n_bits )
{
	m_b_assert_on_overflow = true;
	start_reading( p_data, n_bytes, 0, n_bits );
}

bf_read::bf_read( const char* p_debug_name, const void* p_data, int n_bytes, int n_bits )
{
	m_b_assert_on_overflow = true;
	m_p_debug_name         = p_debug_name;
	start_reading( p_data, n_bytes, 0, n_bits );
}

void bf_read::start_reading( const void* p_data, int n_bytes, int i_start_bit, int n_bits )
{
	// make sure we're dword aligned.
	// assert(((size_t)p_data & 3) == 0);

	m_p_data       = ( unsigned char* )p_data;
	m_n_data_bytes = n_bytes;

	if ( n_bits == -1 ) {
		m_n_data_bits = m_n_data_bytes << 3;
	} else {
		// assert(n_bits <= n_bytes * 8);
		m_n_data_bits = n_bits;
	}

	m_i_cur_bit  = i_start_bit;
	m_b_overflow = false;
}

void bf_read::reset( )
{
	m_i_cur_bit  = 0;
	m_b_overflow = false;
}

void bf_read::set_assert_on_overflow( bool b_assert )
{
	m_b_assert_on_overflow = b_assert;
}

void bf_read::set_debug_name( const char* p_name )
{
	m_p_debug_name = p_name;
}

void bf_read::set_overflow_flag( )
{
	if ( m_b_assert_on_overflow ) {
		// assert(false);
	}
	m_b_overflow = true;
}

unsigned int bf_read::check_read_u_bit_long( int numbits )
{
	// ok, just read bits out.
	int i, n_bit_value;
	unsigned int r = 0;

	for ( i = 0; i < numbits; i++ ) {
		n_bit_value = read_one_bit_no_check( );
		r |= n_bit_value << i;
	}
	m_i_cur_bit -= numbits;

	return r;
}

void bf_read::read_bits( void* p_out_data, int n_bits )
{
#if defined( bb_profiling )
	vprof( "bf_read::read_bits" );
#endif

	unsigned char* p_out = ( unsigned char* )p_out_data;
	int n_bits_left      = n_bits;

	// align output to dword boundary
	while ( ( ( size_t )p_out & 3 ) != 0 && n_bits_left >= 8 ) {
		*p_out = ( unsigned char )read_u_bit_long( 8 );
		++p_out;
		n_bits_left -= 8;
	}

	// x360tbd: can't read dwords in read_bits because they'll get swapped
	if ( true ) {
		// read dwords
		while ( n_bits_left >= 32 ) {
			*( ( unsigned long* )p_out ) = read_u_bit_long( 32 );
			p_out += sizeof( unsigned long );
			n_bits_left -= 32;
		}
	}

	// read remaining bytes
	while ( n_bits_left >= 8 ) {
		*p_out = read_u_bit_long( 8 );
		++p_out;
		n_bits_left -= 8;
	}

	// read remaining bits
	if ( n_bits_left ) {
		*p_out = read_u_bit_long( n_bits_left );
	}
}

int bf_read::read_bits_clamped_ptr( void* p_out_data, size_t out_size_bytes, size_t n_bits )
{
	size_t out_size_bits  = out_size_bytes * 8;
	size_t read_size_bits = n_bits;
	int skipped_bits      = 0;
	if ( read_size_bits > out_size_bits ) {
		// should we print a message when we clamp the data being read? only
		// in debug builds i think.
		// assert_msg(0, "oversized network packet received, and clamped.");
		read_size_bits = out_size_bits;
		skipped_bits   = ( int )( n_bits - out_size_bits );
		// what should we do in this case, which should only happen if n_bits
		// is negative for some reason?
		// if ( skipped_bits < 0 )
		//	return 0;
	}

	read_bits( p_out_data, read_size_bits );
	seek_relative( skipped_bits );

	// return the number of bits actually read.
	return ( int )read_size_bits;
}

float bf_read::read_bit_angle( int numbits )
{
	float f_return;
	int i;
	float shift;

	shift = ( float )( bit_for_bitnum( numbits ) );

	i        = read_u_bit_long( numbits );
	f_return = ( float )i * ( 360.0 / shift );

	return f_return;
}

unsigned int bf_read::peek_u_bit_long( int numbits )
{
	unsigned int r;
	int i, n_bit_value;
#ifdef bit_verbose
	int n_shifts = numbits;
#endif

	bf_read savebf;

	savebf = *this; // save current state info

	r = 0;
	for ( i = 0; i < numbits; i++ ) {
		n_bit_value = read_one_bit( );

		// append to current stream
		if ( n_bit_value ) {
			r |= bit_for_bitnum( i );
		}
	}

	*this = savebf;

#ifdef bit_verbose
	con_printf( "peek_bit_long:  %i %i\n", n_shifts, ( unsigned int )r );
#endif

	return r;
}

unsigned int bf_read::read_u_bit_long_no_inline( int numbits )
{
	return read_u_bit_long( numbits );
}

unsigned int bf_read::read_u_bit_var_internal( int encoding_type )
{
	m_i_cur_bit -= 4;
	// int bits = { 4, 8, 12, 32 }[ encoding_type ];
	int bits = 4 + encoding_type * 4 + ( ( ( 2 - encoding_type ) >> 31 ) & 16 );
	return read_u_bit_long( bits );
}

// append numbits least significant bits from data to the current bit stream
int bf_read::read_s_bit_long( int numbits )
{
	unsigned int r = read_u_bit_long( numbits );
	unsigned int s = 1 << ( numbits - 1 );
	if ( r >= s ) {
		// sign-extend by removing sign bit and then subtracting sign bit again
		r = r - s - s;
	}
	return r;
}

std::uint32_t bf_read::read_var_int32( )
{
	std::uint32_t result = 0;
	int count            = 0;
	std::uint32_t b;

	do {
		if ( count == 5 ) {
			return result;
		}
		b = read_u_bit_long( 8 );
		result |= ( b & 0x7f ) << ( 7 * count );
		++count;
	} while ( b & 0x80 );

	return result;
}

std::uint64_t bf_read::read_var_int64( )
{
	std::uint64_t result = 0;
	int count            = 0;
	std::uint64_t b;

	do {
		if ( count == 10 ) {
			return result;
		}
		b = read_u_bit_long( 8 );
		result |= static_cast< std::uint64_t >( b & 0x7f ) << ( 7 * count );
		++count;
	} while ( b & 0x80 );

	return result;
}

std::int32_t bf_read::read_signed_var_int32( )
{
	std::uint32_t value = read_var_int32( );
	return zig_zag_decode32( value );
}

std::int64_t bf_read::read_signed_var_int64( )
{
	std::uint32_t value = read_var_int64( );
	return zig_zag_decode64( value );
}

unsigned int bf_read::read_bit_long( int numbits, bool b_signed )
{
	if ( b_signed )
		return ( unsigned int )read_s_bit_long( numbits );
	else
		return read_u_bit_long( numbits );
}

// basic coordinate routines (these contain bit-field size and fixed point scaling constants)
float bf_read::read_bit_coord( void )
{
#if defined( bb_profiling )
	vprof( "bf_read::read_bit_coord" );
#endif
	int intval = 0, fractval = 0, signbit = 0;
	float value = 0.0;

	// read the required integer and fraction flags
	intval   = read_one_bit( );
	fractval = read_one_bit( );

	// if we got either parse them, otherwise it's a zero.
	if ( intval || fractval ) {
		// read the sign bit
		signbit = read_one_bit( );

		// if there's an integer, read it in
		if ( intval ) {
			// adjust the integers from [0..max_coord_value-1] to [1..max_coord_value]
			intval = read_u_bit_long( coord_integer_bits ) + 1;
		}

		// if there's a fraction, read it in
		if ( fractval ) {
			fractval = read_u_bit_long( coord_fractional_bits );
		}

		// calculate the correct floating point value
		value = intval + ( ( float )fractval * coord_resolution );

		// fixup the sign if negative.
		if ( signbit )
			value = -value;
	}

	return value;
}

float bf_read::read_bit_coord_mp( bool b_integral, bool b_low_precision )
{
#if defined( bb_profiling )
	vprof( "bf_read::read_bit_coord_mp" );
#endif
	// bit_coord_mp float encoding: inbounds bit, integer bit, sign bit, optional int bits, float bits
	// bit_coord_mp integer encoding: inbounds bit, integer bit, optional sign bit, optional int bits.
	// int bits are always encoded as (value - 1) since zero is handled by the integer bit

	// with integer-only encoding, the presence of the third bit depends on the second
	int flags = read_u_bit_long( 3 - b_integral );
	enum {
		inbounds = 1,
		intval   = 2,
		sign     = 4
	};

	if ( b_integral ) {
		if ( flags & intval ) {
			// read the third bit and the integer portion together at once
			unsigned int bits = read_u_bit_long( ( flags & inbounds ) ? coord_integer_bits_mp + 1 : coord_integer_bits + 1 );
			// remap from [0,n] to [1,n+1]
			int intval = ( bits >> 1 ) + 1;
			return ( bits & 1 ) ? -intval : intval;
		}
		return 0.f;
	}

	static const float mul_table[ 4 ] = { 1.f / ( 1 << coord_fractional_bits ), -1.f / ( 1 << coord_fractional_bits ),
		                                  1.f / ( 1 << coord_fractional_bits_mp_lowprecision ),
		                                  -1.f / ( 1 << coord_fractional_bits_mp_lowprecision ) };
	// equivalent to: float multiply = mul_table[ ((flags & sign) ? 1 : 0) + b_low_precision*2 ];
	float multiply = *( float* )( ( std::uintptr_t )&mul_table[ 0 ] + ( flags & 4 ) + b_low_precision * 8 );

	static const unsigned char numbits_table[ 8 ] = { coord_fractional_bits,
		                                              coord_fractional_bits,
		                                              coord_fractional_bits + coord_integer_bits,
		                                              coord_fractional_bits + coord_integer_bits_mp,
		                                              coord_fractional_bits_mp_lowprecision,
		                                              coord_fractional_bits_mp_lowprecision,
		                                              coord_fractional_bits_mp_lowprecision + coord_integer_bits,
		                                              coord_fractional_bits_mp_lowprecision + coord_integer_bits_mp };
	unsigned int bits                             = read_u_bit_long( numbits_table[ ( flags & ( inbounds | intval ) ) + b_low_precision * 4 ] );

	if ( flags & intval ) {
		// shuffle the bits to remap the integer portion from [0,n] to [1,n+1]
		// and then paste in front of the fractional parts so we only need one
		// int-to-float conversion.

		unsigned int fracbits_mp = bits >> coord_integer_bits_mp;
		unsigned int fracbits    = bits >> coord_integer_bits;

		unsigned int intmask_mp = ( ( 1 << coord_integer_bits_mp ) - 1 );
		unsigned int intmask    = ( ( 1 << coord_integer_bits ) - 1 );

		unsigned int select_not_mp = ( flags & inbounds ) - 1;

		fracbits -= fracbits_mp;
		fracbits &= select_not_mp;
		fracbits += fracbits_mp;

		intmask -= intmask_mp;
		intmask &= select_not_mp;
		intmask += intmask_mp;

		unsigned int intpart        = ( bits & intmask ) + 1;
		unsigned int intbits_low    = intpart << coord_fractional_bits_mp_lowprecision;
		unsigned int intbits        = intpart << coord_fractional_bits;
		unsigned int select_not_low = ( unsigned int )b_low_precision - 1;

		intbits -= intbits_low;
		intbits &= select_not_low;
		intbits += intbits_low;

		bits = fracbits | intbits;
	}

	return ( int )bits * multiply;
}

unsigned int bf_read::read_bit_coord_bits( void )
{
#if defined( bb_profiling )
	vprof( "bf_read::read_bit_coord_bits" );
#endif

	unsigned int flags = read_u_bit_long( 2 );
	if ( flags == 0 )
		return 0;

	static const int numbits_table[ 3 ] = { coord_integer_bits + 1, coord_fractional_bits + 1, coord_integer_bits + coord_fractional_bits + 1 };
	return read_u_bit_long( numbits_table[ flags - 1 ] ) * 4 + flags;
}

unsigned int bf_read::read_bit_coord_mp_bits( bool b_integral, bool b_low_precision )
{
#if defined( bb_profiling )
	vprof( "bf_read::read_bit_coord_mp_bits" );
#endif

	unsigned int flags = read_u_bit_long( 2 );
	enum {
		inbounds = 1,
		intval   = 2
	};
	int numbits = 0;

	if ( b_integral ) {
		if ( flags & intval ) {
			numbits = ( flags & inbounds ) ? ( 1 + coord_integer_bits_mp ) : ( 1 + coord_integer_bits );
		} else {
			return flags; // no extra bits
		}
	} else {
		static const unsigned char numbits_table[ 8 ] = { 1 + coord_fractional_bits,
			                                              1 + coord_fractional_bits,
			                                              1 + coord_fractional_bits + coord_integer_bits,
			                                              1 + coord_fractional_bits + coord_integer_bits_mp,
			                                              1 + coord_fractional_bits_mp_lowprecision,
			                                              1 + coord_fractional_bits_mp_lowprecision,
			                                              1 + coord_fractional_bits_mp_lowprecision + coord_integer_bits,
			                                              1 + coord_fractional_bits_mp_lowprecision + coord_integer_bits_mp };
		numbits                                       = numbits_table[ flags + b_low_precision * 4 ];
	}

	return flags + read_u_bit_long( numbits ) * 4;
}

void bf_read::read_bit_vec3_coord( vector& fa )
{
	int xflag, yflag, zflag;

	// this vector must be initialized! otherwise, if any of the flags aren't set,
	// the corresponding component will not be read and will be stack garbage.
	fa = { 0, 0, 0 };

	xflag = read_one_bit( );
	yflag = read_one_bit( );
	zflag = read_one_bit( );

	if ( xflag )
		fa.x = read_bit_coord( );
	if ( yflag )
		fa.y = read_bit_coord( );
	if ( zflag )
		fa.z = read_bit_coord( );
}

float bf_read::read_bit_normal( void )
{
	// read the sign bit
	int signbit = read_one_bit( );

	// read the fractional part
	unsigned int fractval = read_u_bit_long( normal_fractional_bits );

	// calculate the correct floating point value
	float value = ( float )fractval * normal_resolution;

	// fixup the sign if negative.
	if ( signbit )
		value = -value;

	return value;
}

void bf_read::read_bit_vec3_normal( vector& fa )
{
	int xflag = read_one_bit( );
	int yflag = read_one_bit( );

	if ( xflag )
		fa.x = read_bit_normal( );
	else
		fa.x = 0.0f;

	if ( yflag )
		fa.y = read_bit_normal( );
	else
		fa.y = 0.0f;

	// the first two imply the third (but not its sign)
	int znegative = read_one_bit( );

	float fafafbfb = fa.x * fa.x + fa.y * fa.y;
	if ( fafafbfb < 1.0f )
		fa.z = sqrt( 1.0f - fafafbfb );
	else
		fa.z = 0.0f;

	if ( znegative )
		fa.z = -fa.z;
}

void bf_read::read_bit_angles( vector& fa )
{
	vector tmp;
	read_bit_vec3_coord( tmp );
	fa = { tmp.x, tmp.y, tmp.z };
}

std::int64_t bf_read::read_long_long( )
{
	std::int64_t retval;
	unsigned int* p_longs = ( unsigned int* )&retval;

	// read the two dwor_ds according to network endian
	const short endian_index      = 0x0100;
	std::byte* idx                = ( std::byte* )&endian_index;
	p_longs[ ( *( int* )idx )++ ] = read_u_bit_long( sizeof( long ) << 3 );
	p_longs[ ( *( int* )idx ) ]   = read_u_bit_long( sizeof( long ) << 3 );

	return retval;
}

float bf_read::read_float( )
{
	float ret;
	// assert(sizeof(ret) == 4);
	read_bits( &ret, 32 );

	return ret;
}

bool bf_read::read_bytes( void* p_out, int n_bytes )
{
	read_bits( p_out, n_bytes << 3 );
	return !is_overflowed( );
}

bool bf_read::read_string( char* p_str, int max_len, bool b_line, int* p_out_num_chars )
{
	// assert(max_len != 0);

	bool b_too_small = false;
	int i_char       = 0;
	while ( 1 ) {
		char val = read_char( );
		if ( val == 0 )
			break;
		else if ( b_line && val == '\n' )
			break;

		if ( i_char < ( max_len - 1 ) ) {
			p_str[ i_char ] = val;
			++i_char;
		} else {
			b_too_small = true;
		}
	}

	// make sure it's NULL-terminated.
	// assert(i_char < max_len);
	p_str[ i_char ] = 0;

	if ( p_out_num_chars )
		*p_out_num_chars = i_char;

	return !is_overflowed( ) && !b_too_small;
}

char* bf_read::read_and_allocate_string( bool* p_overflow )
{
	char str[ 2048 ];

	int n_chars;
	bool b_overflow = !read_string( str, sizeof( str ), false, &n_chars );
	if ( p_overflow )
		*p_overflow = b_overflow;

	// now copy into the output and return it;
	char* p_ret = new char[ n_chars + 1 ];
	for ( int i = 0; i <= n_chars; i++ )
		p_ret[ i ] = str[ i ];

	return p_ret;
}

void bf_read::excise_bits( int startbit, int bitstoremove )
{
	int endbit           = startbit + bitstoremove;
	int remaining_to_end = m_n_data_bits - endbit;

	bf_write temp;
	temp.start_writing( ( void* )m_p_data, m_n_data_bits << 3, startbit );

	seek( endbit );

	for ( int i = 0; i < remaining_to_end; i++ ) {
		temp.write_one_bit( read_one_bit( ) );
	}

	seek( startbit );

	m_n_data_bits -= bitstoremove;
	m_n_data_bytes = m_n_data_bits >> 3;
}
int bf_read::compare_bits_at( int offset, bf_read* other, int other_offset, int numbits )
{
	extern unsigned long g_extra_masks[ 33 ];

	if ( numbits == 0 )
		return 0;

	int overflow1 = offset + numbits > m_n_data_bits;
	int overflow2 = other_offset + numbits > other->m_n_data_bits;

	int x = overflow1 | overflow2;
	if ( x != 0 )
		return x;

	unsigned int i_start_bit1  = offset & 31u;
	unsigned int i_start_bit2  = other_offset & 31u;
	unsigned long* p_data1     = ( unsigned long* )m_p_data + ( offset >> 5 );
	unsigned long* p_data2     = ( unsigned long* )other->m_p_data + ( other_offset >> 5 );
	unsigned long* p_data1_end = p_data1 + ( ( offset + numbits - 1 ) >> 5 );
	unsigned long* p_data2_end = p_data2 + ( ( other_offset + numbits - 1 ) >> 5 );

	while ( numbits > 32 ) {
		x = load_little_d_word( ( unsigned long* )p_data1, 0 ) >> i_start_bit1;
		x ^= load_little_d_word( ( unsigned long* )p_data1, 1 ) << ( 32 - i_start_bit1 );
		x ^= load_little_d_word( ( unsigned long* )p_data2, 0 ) >> i_start_bit2;
		x ^= load_little_d_word( ( unsigned long* )p_data2, 1 ) << ( 32 - i_start_bit2 );
		if ( x != 0 ) {
			return x;
		}
		++p_data1;
		++p_data2;
		numbits -= 32;
	}

	x = load_little_d_word( ( unsigned long* )p_data1, 0 ) >> i_start_bit1;
	x ^= load_little_d_word( ( unsigned long* )p_data1_end, 0 ) << ( 32 - i_start_bit1 );
	x ^= load_little_d_word( ( unsigned long* )p_data2, 0 ) >> i_start_bit2;
	x ^= load_little_d_word( ( unsigned long* )p_data2_end, 0 ) << ( 32 - i_start_bit2 );
	return x & g_extra_masks[ numbits ];
}
