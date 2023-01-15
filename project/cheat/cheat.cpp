#include "cheat.hpp"

#include <chrono>
#include <themida/ThemidaSDK.h>

DWORD WINAPI shutdown_routine( LPVOID )
{
	g_cheat->end( );

	return 0;
}

void cheat::run( )
{
	using namespace spdlog;

	stopwatch stopwatch;

	g_console->run( );
	info( "console initialized in {}ms", stopwatch );
	g_config->run( );
	info( "config initialized in {}ms", stopwatch );
	g_modules->run( );
	info( "modules initialized in {}ms", stopwatch );
	g_signatures.run( );
	info( "signatures initialized in {}ms", stopwatch );
	g_interfaces->run( );
	info( "interfaces initialized in {}ms", stopwatch );
	g_hooks->run( );
	info( "hooks initialized in {}ms", stopwatch );

	g_input->add_keybind( VK_DELETE, []( bool ) {
		if ( auto handle = CreateThread( nullptr, 0, shutdown_routine, nullptr, 0, nullptr ) ) {
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

	FreeLibraryAndExitThread( instance, 0 );
}
