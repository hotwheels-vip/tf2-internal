#include "process_tick.hpp"

#include "../cheat/features/tickbase/tickbase.hpp"

bool __fastcall process_tick::detour( void* ecx, void* edx, void* msg )
{
	// DEPRECATED! Not needed for tickbase fix.
	// g_tickbase->last_tick   = *( int* )( ( std::uintptr_t )msg + 0x14 );
	// g_tickbase->clock_drift = ( void* )( ( std::uintptr_t )ecx + 0x14C ); // HACK: Lets us skip finding inside of the game :P

	return g_process_tick->_hook.call( ecx, edx, msg );
}
