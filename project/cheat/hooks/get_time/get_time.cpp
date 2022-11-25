#include "get_time.hpp"

float __fastcall get_time::detour( void* ecx, void* edx )
{
	if ( _ReturnAddress( ) == g_signatures[ HASH( "D9 43 ? DF F1" ) ] )
		return FLT_MAX;

	return g_get_time->_hook.call( ecx, edx );
}
