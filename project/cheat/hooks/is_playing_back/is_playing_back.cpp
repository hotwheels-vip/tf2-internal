#include "is_playing_back.hpp"

bool __fastcall is_playing_back::detour( void* ecx, void* edx )
{
	if ( _ReturnAddress( ) == g_database[ HASH( "84 C0 75 ? 38 05 ? ? ? ? 75 ? A1" ) ] )
		return true;

	return g_is_playing_back->_hook.call( ecx, edx );
}
