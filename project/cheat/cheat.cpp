#include "cheat.hpp"

#include <chrono>
#include <themida/ThemidaSDK.h>

DWORD WINAPI shutdown_routine( LPVOID )
{
	cheat::end( );

	return 0;
}

void cheat::run( )
{
	using namespace spdlog;

	stopwatch mod;

	g_console->run( );
	info( "console initialized in {:0.2f}s", mod );
	g_config->run( );
	info( "config initialized in {:0.2f}s", mod );
	g_modules->run( );
	info( "modules initialized in {:0.2f}s", mod );
	g_signatures.run( );
	info( "signatures initialized in {:0.2f}s", mod );
	g_interfaces->run( );
	info( "interfaces initialized in {:0.2f}s", mod );
	g_hooks->run( );
	info( "hooks initialized in {:0.2f}s", mod );

	g_input->add_keybind( VK_DELETE, []( bool ) {
		if ( const auto handle = CreateThread( nullptr, 0, shutdown_routine, nullptr, 0, nullptr ) ) {
			CloseHandle( handle );
		}
	} );
}

void cheat::end( )
{
	using namespace spdlog;

	stopwatch stopwatch;

	g_hooks->end( );
	info( "hooks uninitialized in {}ms", stopwatch );
	g_interfaces->end( );
	info( "interfaces uninitialized in {}ms", stopwatch );
	g_signatures.end( );
	info( "signatures uninitialized in {}ms", stopwatch );
	g_modules->end( );
	info( "modules uninitialized in {}ms", stopwatch );
	g_config->end( );
	info( "config uninitialized in {}ms", stopwatch );
	g_console->end( );

	FreeLibraryAndExitThread( g_cheat->instance, 0 );
}
