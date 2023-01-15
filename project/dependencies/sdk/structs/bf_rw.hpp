#pragma once

#include "../structs/vector.hpp"
#include <iostream>

#pragma warning( disable : 4146 )
#pragma warning( disable : 4018 )

namespace sdk
{
	inline std::uint32_t zig_zag_encode32( std::int32_t n )
	{
		// note:  the right-shift must be arithmetic
		return ( n << 1 ) ^ ( n >> 31 );
	}

	inline std::int32_t zig_zag_decode32( std::uint32_t n )
	{
		return ( n >> 1 ) ^ -static_cast< std::int32_t >( n & 1 );
	}

	inline std::uint64_t zig_zag_encode64( std::int32_t n )
	{
		// note:  the right-shift must be arithmetic
#pragma warning( disable : 4293 )
		return ( n << 1 ) ^ ( n >> 63 );
	}

	inline std::int64_t zig_zag_decode64( std::uint64_t n )
	{
		return ( n >> 1 ) ^ -static_cast< std::uint64_t >( n & 1 );
	}

	inline int bit_byte( int bits )
	{
		// return PAD_NUMBER( bits, 8 ) >> 3;
		return ( bits + 7 ) >> 3;
	}

	inline std::uint32_t load_little_d_word( std::uint32_t* base, unsigned int dword_index )
	{
		return base[ dword_index ];
	}

	inline std::uint32_t load_little_d_word( unsigned long* base, unsigned int dword_index )
	{
		return base[ dword_index ];
	}

	inline void store_little_d_word( std::uint32_t* base, unsigned int dword_index, std::uint32_t dword )
	{
		base[ dword_index ] = dword;
	}

	inline void store_little_d_word( unsigned long* base, unsigned int dword_index, std::uint32_t dword )
	{
		base[ dword_index ] = dword;
	}

	class bf_write
	{
	public:
		bf_write( );

		// n_max_bits can be used as the number of bits in the buffer.
		// it must be <= n_bytes*8. if you leave it at -1, then it's set to n_bytes * 8.

		// 1
		bf_write( void* p_data, int n_bytes, int n_max_bits = -1 );
		// 2
		bf_write( const char* p_debug_name, void* p_data, int n_bytes, int n_max_bits = -1 );

		// start writing to the specified buffer.
		// n_max_bits can be used as the number of bits in the buffer.
		// it must be <= n_bytes*8. if you leave it at -1, then it's set to n_bytes * 8.

		// virtual_method(void, start_writing, 3, (void* p_data, int n_bytes, int i_start_bit = 0, int n_max_bits = -1), (this, p_data, n_bytes,
		// i_start_bit, n_max_bits))
		void start_writing( void* p_data, int n_bytes, int i_start_bit = 0, int n_max_bits = -1 );

		// restart buffer writing.
		void reset( );

		// get the base pointer.

		// virtual_method(unsigned char*, get_base_pointer, 5, (void), (this))

		unsigned char* get_base_pointer( )
		{
			return ( unsigned char* )m_p_data;
		}

		// enable or disable assertion on overflow. 99% of the time, it's a bug that we need to catch,
		// but there may be the occasional buffer that is allowed to overflow gracefully.
		void set_assert_on_overflow( bool b_assert );

		// this can be set to assign a name that gets output if the buffer overflows.
		// virtual_method(const char*, get_debug_name, 7, (void), (this))
		const char* get_debug_name( ); // 7

		void set_debug_name( const char* p_debug_name );

		// seek to a specific position.
	public:
		void seek_to_bit( int bit_pos );

		// bit functions.
	public:
		void write_one_bit( int n_value );
		void write_one_bit_no_check( int n_value );
		void write_one_bit_at( int i_bit, int n_value );

		// write signed or unsigned. range is only checked in debug.
		void write_u_bit_long( unsigned int data, int numbits, bool b_check_range = true );
		void write_s_bit_long( int data, int numbits );

		// tell it whether or not the data is unsigned. if it's signed,
		// cast to unsigned before passing in (it will cast back inside).
		void write_bit_long( unsigned int data, int numbits, bool b_signed );

		// write a list of bits in.
		bool write_bits( const void* p_in, int n_bits );

		// writes an unsigned integer with variable bit length
		void write_u_bit_var( unsigned int data );

		// writes a varint encoded integer
		void write_var_int32( std::uint32_t data );
		void write_var_int64( std::uint64_t data );
		void write_signed_var_int32( std::int32_t data );
		void write_signed_var_int64( std::int64_t data );
		int byte_size_var_int32( std::uint32_t data );
		int byte_size_var_int64( std::uint64_t data );
		int byte_size_signed_var_int32( std::int32_t data );
		int byte_size_signed_var_int64( std::int64_t data );

		// copy the bits straight out of p_in. this seeks p_in forward by n_bits.
		// returns an error if this buffer or the read buffer overflows.
		bool write_bits_from_buffer( class bf_read* p_in, int n_bits );

		void write_bit_angle( float f_angle, int numbits );
		void write_bit_coord( const float f );
		void write_bit_coord_mp( const float f, bool b_integral, bool b_low_precision );
		void write_bit_float( float val );
		void write_bit_vec3_coord( const vector& fa );
		void write_bit_normal( float f );
		void write_bit_vec3_normal( const vector& fa );
		void write_bit_angles( const vector& fa );

		// byte functions.
	public:
		void write_char( int val );
		void write_byte( int val );
		void write_short( int val );
		void write_word( int val );
		void write_long( long val );
		void write_long_long( std::int64_t val );
		void write_float( float val );
		bool write_bytes( const void* p_buf, int n_bytes );

		// returns false if it overflows the buffer.
		bool write_string( const char* p_str );

		// status.
	public:
		// how many bytes are filled in?
		int get_num_bytes_written( ) const;
		int get_num_bits_written( ) const;
		int get_max_num_bits( );
		int get_num_bits_left( );
		int get_num_bytes_left( );
		unsigned char* get_data( );
		const unsigned char* get_data( ) const;

		// has the buffer overflowed?
		bool check_for_overflow( int n_bits );
		inline bool is_overflowed( ) const
		{
			return m_b_overflow;
		}

		void set_overflow_flag( );

	public:
		// the current buffer.
		// unsigned long*  m_p_data;
		// the current buffer.
		unsigned long* m_p_data;
		std::uint32_t m_n_data_bytes;
		std::uint32_t m_n_data_bits;
		std::uint32_t m_i_cur_bit;

		bool m_b_overflow;
		bool m_b_assert_on_overflow;
		const char* m_p_debug_name;
	};
	// private:

	class bf_read
	{
	public:
		bf_read( );

		// n_max_bits can be used as the number of bits in the buffer.
		// it must be <= n_bytes*8. if you leave it at -1, then it's set to n_bytes * 8.
		bf_read( const void* p_data, int n_bytes, int n_bits = -1 );
		bf_read( const char* p_debug_name, const void* p_data, int n_bytes, int n_bits = -1 );

		// start reading from the specified buffer.
		// p_data's start address must be dword-aligned.
		// n_max_bits can be used as the number of bits in the buffer.
		// it must be <= n_bytes*8. if you leave it at -1, then it's set to n_bytes * 8.
		void start_reading( const void* p_data, int n_bytes, int i_start_bit = 0, int n_bits = -1 );

		// restart buffer reading.
		void reset( );

		// enable or disable assertion on overflow. 99% of the time, it's a bug that we need to catch,
		// but there may be the occasional buffer that is allowed to overflow gracefully.
		void set_assert_on_overflow( bool b_assert );

		// this can be set to assign a name that gets output if the buffer overflows.
		const char* get_debug_name( ) const
		{
			return m_p_debug_name;
		}
		void set_debug_name( const char* p_name );

		void excise_bits( int startbit, int bitstoremove );

		// bit functions.
	public:
		// returns 0 or 1.
		int read_one_bit( );

	protected:
		unsigned int check_read_u_bit_long( int numbits ); // for debugging.
		int read_one_bit_no_check( );                      // faster version, doesn't check bounds and is inlined.
		bool check_for_overflow( int n_bits );

	public:
		// get the base pointer.
		const unsigned char* get_base_pointer( )
		{
			return m_p_data;
		}

		__forceinline int total_bytes_available( void ) const
		{
			return m_n_data_bytes;
		}

		// read a list of bits in.
		void read_bits( void* p_out, int n_bits );
		// read a list of bits in, but don't overrun the destination buffer.
		// returns the number of bits read into the buffer. the remaining
		// bits are skipped over.
		int read_bits_clamped_ptr( void* p_out, size_t out_size_bytes, size_t n_bits );
		// helper 'safe' template function that infers the size of the destination
		// array. this version of the function should be preferred.
		// usage: char databuffer[100];
		//        read_bits_clamped( data_buffer, msg->m_n_length );
		template< typename t, size_t n >
		int read_bits_clamped( t ( &p_out )[ n ], size_t n_bits )
		{
			return read_bits_clamped_ptr( p_out, n * sizeof( t ), n_bits );
		}

		float read_bit_angle( int numbits );

		unsigned int read_u_bit_long( int numbits );
		unsigned int read_u_bit_long_no_inline( int numbits );
		unsigned int peek_u_bit_long( int numbits );
		int read_s_bit_long( int numbits );

		// reads an unsigned integer with variable bit length
		unsigned int read_u_bit_var( );
		unsigned int read_u_bit_var_internal( int encoding_type );

		// reads a varint encoded integer
		std::uint32_t read_var_int32( );
		std::uint64_t read_var_int64( );
		std::int32_t read_signed_var_int32( );
		std::int64_t read_signed_var_int64( );

		// you can read signed or unsigned data with this, just cast to
		// a signed int if necessary.
		unsigned int read_bit_long( int numbits, bool b_signed );

		float read_bit_coord( );
		float read_bit_coord_mp( bool b_integral, bool b_low_precision );
		float read_bit_float( );
		float read_bit_normal( );
		void read_bit_vec3_coord( vector& fa );
		void read_bit_vec3_normal( vector& fa );
		void read_bit_angles( vector& fa );

		// faster for comparisons but do not fully decode float values
		unsigned int read_bit_coord_bits( );
		unsigned int read_bit_coord_mp_bits( bool b_integral, bool b_low_precision );

		// byte functions (these still read data in bit-by-bit).
	public:
		__forceinline int read_char( )
		{
			return ( char )read_u_bit_long( 8 );
		}
		__forceinline int read_byte( )
		{
			return read_u_bit_long( 8 );
		}
		__forceinline int read_short( )
		{
			return ( short )read_u_bit_long( 16 );
		}
		__forceinline int read_word( )
		{
			return read_u_bit_long( 16 );
		}
		__forceinline long read_long( )
		{
			return read_u_bit_long( 32 );
		}
		std::int64_t read_long_long( );
		float read_float( );
		bool read_bytes( void* p_out, int n_bytes );

		// returns false if buf_len isn't large enough to hold the
		// string in the buffer.
		//
		// always reads to the end of the string (so you can read the
		// next piece of data waiting).
		//
		// if b_line is true, it stops when it reaches a '\n' or a null-terminator.
		//
		// p_str is always null-terminated (unless buf_len is 0).
		//
		// p_out_num_chars is set to the number of characters left in p_str when the routine is
		// complete (this will never exceed buf_len-1).
		//
		bool read_string( char* p_str, int buf_len, bool b_line = false, int* p_out_num_chars = { } );

		// reads a string and allocates memory for it. if the string in the buffer
		// is > 2048 bytes, then p_overflow is set to true (if it's not null).
		char* read_and_allocate_string( bool* p_overflow = 0 );

		// returns nonzero if any bits differ
		int compare_bits( bf_read* other, int bits );
		int compare_bits_at( int offset, bf_read* other, int other_offset, int bits );

		// status.
	public:
		int get_num_bytes_left( );
		int get_num_bytes_read( );
		int get_num_bits_left( );
		int get_num_bits_read( ) const;

		// has the buffer overflowed?
		inline bool is_overflowed( ) const
		{
			return m_b_overflow;
		}

		inline bool seek( int i_bit );                // seek to a specific bit.
		inline bool seek_relative( int i_bit_delta ); // seek to an offset from the current position.

		// called when the buffer is overflowed.
		void set_overflow_flag( );

	public:
		// the current buffer.
		unsigned char* m_p_data;
		std::uint32_t m_n_data_bytes;
		std::uint32_t m_n_data_bits;
		std::uint32_t m_i_cur_bit;
		// errors?
		bool m_b_overflow;
		// for debugging..
		bool m_b_assert_on_overflow;
		const char* m_p_debug_name;

	private:
	};

	// how many bytes are filled in?
	inline int bf_write::get_num_bytes_written( ) const
	{
		return bit_byte( m_i_cur_bit );
	}

	inline int bf_write::get_num_bits_written( ) const
	{
		return m_i_cur_bit;
	}

	inline int bf_write::get_max_num_bits( )
	{
		return m_n_data_bits;
	}

	inline int bf_write::get_num_bits_left( )
	{
		return m_n_data_bits - m_i_cur_bit;
	}

	inline int bf_write::get_num_bytes_left( )
	{
		return get_num_bits_left( ) >> 3;
	}

	inline unsigned char* bf_write::get_data( )
	{
		return ( unsigned char* )m_p_data;
	}

	inline const unsigned char* bf_write::get_data( ) const
	{
		return ( unsigned char* )m_p_data;
	}

	__forceinline bool bf_write::check_for_overflow( int n_bits )
	{
		if ( m_i_cur_bit + n_bits > m_n_data_bits ) {
			set_overflow_flag( );
		}

		return m_b_overflow;
	}

	__forceinline void bf_write::set_overflow_flag( )
	{
#ifdef dbgflag_assert
		if ( m_b_assert_on_overflow ) {
			assert( false );
		}
#endif
		m_b_overflow = true;
	}
	__forceinline void bf_write::write_one_bit_no_check( int n_value )
	{
#if __i386__
		if ( n_value )
			m_p_data[ m_i_cur_bit >> 5 ] |= 1u << ( m_i_cur_bit & 31 );
		else
			m_p_data[ m_i_cur_bit >> 5 ] &= ~( 1u << ( m_i_cur_bit & 31 ) );
#else

		if ( true ) {
			extern unsigned long g_little_bits[ 32 ];
			if ( n_value )
				m_p_data[ m_i_cur_bit >> 5 ] |= g_little_bits[ m_i_cur_bit & 31 ];
			else
				m_p_data[ m_i_cur_bit >> 5 ] &= ~g_little_bits[ m_i_cur_bit & 31 ];

			++m_i_cur_bit;
		} else {
			if ( n_value )
				m_p_data[ m_i_cur_bit >> 3 ] |= ( 1 << ( m_i_cur_bit & 7 ) );
			else
				m_p_data[ m_i_cur_bit >> 3 ] &= ~( 1 << ( m_i_cur_bit & 7 ) );

			++m_i_cur_bit;
		}

#endif
	}

	/*

	inline void bf_write::write_one_bit_no_check(int n_value)
	{

	}

	*/

	inline void bf_write::write_one_bit( int n_value )
	{
		if ( m_i_cur_bit >= m_n_data_bits ) {
			return;
		}
		write_one_bit_no_check( n_value );
	}

	inline void bf_write::write_one_bit_at( int i_bit, int n_value )
	{
		if ( i_bit >= m_n_data_bits ) {
			set_overflow_flag( );

			return;
		}

#if __i386__
		if ( n_value )
			m_p_data[ i_bit >> 5 ] |= 1u << ( i_bit & 31 );
		else
			m_p_data[ i_bit >> 5 ] &= ~( 1u << ( i_bit & 31 ) );
#else
		extern unsigned long g_little_bits[ 32 ];
		if ( n_value )
			m_p_data[ i_bit >> 5 ] |= g_little_bits[ i_bit & 31 ];
		else
			m_p_data[ i_bit >> 5 ] &= ~g_little_bits[ i_bit & 31 ];
#endif
	}

	__forceinline void bf_write::write_u_bit_long( unsigned int cur_data, int numbits, bool b_check_range )
	{
#ifdef _debug
		// make sure it doesn't overflow.
		if ( b_check_range && numbits < 32 ) {
			if ( cur_data >= ( unsigned long )( 1 << numbits ) ) {
				return;
			}
		}

#endif

		if ( get_num_bits_left( ) < numbits ) {
			m_i_cur_bit = m_n_data_bits;

			return;
		}

		int i_cur_bit_masked = m_i_cur_bit & 31;
		int i_d_word         = m_i_cur_bit >> 5;
		m_i_cur_bit += numbits;

		// mask in a dword.

		unsigned long* p_out = &m_p_data[ i_d_word ];

		// rotate data into dword alignment
		cur_data = ( cur_data << i_cur_bit_masked ) | ( cur_data >> ( 32 - i_cur_bit_masked ) );

		// calculate bitmasks for first and second word
		unsigned int temp  = 1 << ( numbits - 1 );
		unsigned int mask1 = ( temp * 2 - 1 ) << i_cur_bit_masked;
		unsigned int mask2 = ( temp - 1 ) >> ( 31 - i_cur_bit_masked );

		// only look beyond current word if necessary (avoid access violation)
		int i                = mask2 & 1;
		unsigned long dword1 = load_little_d_word( p_out, 0 );
		unsigned long dword2 = load_little_d_word( p_out, i );

		// drop bits into place
		dword1 ^= ( mask1 & ( cur_data ^ dword1 ) );
		dword2 ^= ( mask2 & ( cur_data ^ dword2 ) );

		// note reversed order of writes so that dword1 wins if mask2 == 0 && i == 0
		store_little_d_word( p_out, i, dword2 );
		store_little_d_word( p_out, 0, dword1 );
	}

	// writes an unsigned integer with variable bit length
	__forceinline void bf_write::write_u_bit_var( unsigned int data )
	{
		/* reference:
		if ( data < 0x10u )
		    write_u_bit_long( 0, 2 ), write_u_bit_long( data, 4 );
		else if ( data < 0x100u )
		    write_u_bit_long( 1, 2 ), write_u_bit_long( data, 8 );
		else if ( data < 0x1000u )
		    write_u_bit_long( 2, 2 ), write_u_bit_long( data, 12 );
		else
		    write_u_bit_long( 3, 2 ), write_u_bit_long( data, 32 );
		*/
		// a < b ? -1 : 0 translates into a cmp, sbb instruction pair
		// with no flow control. should also be branchless on consoles.
		int n = ( data < 0x10u ? -1 : 0 ) + ( data < 0x100u ? -1 : 0 ) + ( data < 0x1000u ? -1 : 0 );
		write_u_bit_long( data * 4 + n + 3, 6 + n * 4 + 12 );
		if ( data >= 0x1000u ) {
			write_u_bit_long( data >> 16, 16 );
		}
	}

	// write raw ieee float bits in little endian form
	__forceinline void bf_write::write_bit_float( float val )
	{
		long int_val;

		int_val = *( ( long* )&val );
		write_u_bit_long( int_val, 32 );
	}

	inline int bf_read::get_num_bytes_read( )
	{
		return bit_byte( m_i_cur_bit );
	}

	inline int bf_read::get_num_bits_left( )
	{
		return m_n_data_bits - m_i_cur_bit;
	}

	inline int bf_read::get_num_bytes_left( )
	{
		return get_num_bits_left( ) >> 3;
	}

	inline int bf_read::get_num_bits_read( ) const
	{
		return m_i_cur_bit;
	}

	inline bool bf_read::seek( int i_bit )
	{
		if ( i_bit < 0 || i_bit > m_n_data_bits ) {
			set_overflow_flag( );
			m_i_cur_bit = m_n_data_bits;
			return false;
		} else {
			m_i_cur_bit = i_bit;
			return true;
		}
	}

	// seek to an offset from the current position.
	inline bool bf_read::seek_relative( int i_bit_delta )
	{
		return seek( m_i_cur_bit + i_bit_delta );
	}

	inline bool bf_read::check_for_overflow( int n_bits )
	{
		if ( m_i_cur_bit + n_bits > m_n_data_bits ) {
			set_overflow_flag( );
		}

		return m_b_overflow;
	}

	inline int bf_read::read_one_bit_no_check( )
	{
#if valve_little_endian
		unsigned int value = ( ( unsigned long* )m_p_data )[ m_i_cur_bit >> 5 ] >> ( m_i_cur_bit & 31 );
#else
		unsigned char value = m_p_data[ m_i_cur_bit >> 3 ] >> ( m_i_cur_bit & 7 );
#endif
		++m_i_cur_bit;
		return value & 1;
	}

	inline int bf_read::read_one_bit( )
	{
		if ( get_num_bits_left( ) <= 0 ) {
			set_overflow_flag( );

			return 0;
		}
		return read_one_bit_no_check( );
	}

	inline float bf_read::read_bit_float( )
	{
		union {
			std::uint32_t u;
			float f;
		} c = { read_u_bit_long( 32 ) };
		return c.f;
	}

	__forceinline unsigned int bf_read::read_u_bit_var( )
	{
		// six bits: low 2 bits for encoding + first 4 bits of value
		unsigned int sixbits  = read_u_bit_long( 6 );
		unsigned int encoding = sixbits & 3;
		if ( encoding ) {
			// this function will seek back four bits and read the full value
			return read_u_bit_var_internal( encoding );
		}
		return sixbits >> 2;
	}

	__forceinline unsigned int bf_read::read_u_bit_long( int numbits )
	{
		if ( get_num_bits_left( ) < numbits ) {
			m_i_cur_bit = m_n_data_bits;
			set_overflow_flag( );

			return 0;
		}

		unsigned int i_start_bit    = m_i_cur_bit & 31u;
		int i_last_bit              = m_i_cur_bit + numbits - 1;
		unsigned int i_word_offset1 = m_i_cur_bit >> 5;
		unsigned int i_word_offset2 = i_last_bit >> 5;
		m_i_cur_bit += numbits;

#if __i386__
		unsigned int bitmask = ( 2 << ( numbits - 1 ) ) - 1;
#else
		extern unsigned long g_extra_masks[ 33 ];
		unsigned int bitmask = g_extra_masks[ numbits ];
#endif

		unsigned int dw1 = load_little_d_word( ( unsigned long* )m_p_data, i_word_offset1 ) >> i_start_bit;
		unsigned int dw2 = load_little_d_word( ( unsigned long* )m_p_data, i_word_offset2 ) << ( 32 - i_start_bit );

		return ( dw1 | dw2 ) & bitmask;
	}

	__forceinline int bf_read::compare_bits( bf_read* other, int numbits )
	{
		return ( read_u_bit_long( numbits ) != other->read_u_bit_long( numbits ) );
	}

} // namespace sdk
