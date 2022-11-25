//
// Created by liga on 11/13/2022.
//

#include "entry.hpp"

DWORD WINAPI entry( LPVOID )
{
	g_cheat->run( );

	return 0;
}

BOOL WINAPI DllMain( HINSTANCE instance, DWORD reason, LPVOID )
{
	if ( reason == DLL_PROCESS_ATTACH ) {
		g_cheat->instance = instance;

		DisableThreadLibraryCalls( GetModuleHandle( nullptr ) );

		if ( auto thread = CreateThread( nullptr, 0, entry, nullptr, 0, nullptr ) )
			CloseHandle( thread );
	}

	return TRUE;
}