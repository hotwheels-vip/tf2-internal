#ifndef B617673D_5C4D_4C16_B6A2_AD6F65FD363D
#define B617673D_5C4D_4C16_B6A2_AD6F65FD363D

#include <Windows.h>
#include <unordered_map>

template< typename T, T MY_VALUE >
struct CONST_HOLDER {
	enum class VALUE_HOLDER : T {
		RET_VALUE = MY_VALUE,
	};
};

#define CONSTANT_HOLD( value ) ( ( decltype( value ) )CONST_HOLDER< decltype( value ), value >::VALUE_HOLDER::RET_VALUE )

// [!] build time hashing
#define HASH( s ) CONSTANT_HOLD( hash::fnv1a_ct( s ) )
// [!] run time hashing
#define RT_HASH( s ) hash::fnv1a_rt( s )

namespace hash
{
	namespace holder
	{
		constexpr static std::uint32_t seed  = 0x811C9DC5;
		constexpr static std::uint32_t prime = 0x01000193;
	} // namespace holder

	inline UINT32 fnv1a_rt( const char* key, const UINT32 val = hash::holder::seed )
	{
		auto temp_hash = ( key[ 0 ] == '\0' ) ? val : fnv1a_rt( &key[ 1 ], ( val ^ UINT32( key[ 0 ] ) ) * hash::holder::prime );

		return temp_hash;
	}

	constexpr static UINT32 fnv1a_ct( char const* string, const UINT32 val = hash::holder::seed )
	{
		auto temp_hash = ( string[ 0 ] == '\0' ) ? val : fnv1a_ct( &string[ 1 ], ( val ^ UINT32( string[ 0 ] ) ) * hash::holder::prime );

		return temp_hash;
	}
} // namespace hash

#endif // B617673D_5C4D_4C16_B6A2_AD6F65FD363D
