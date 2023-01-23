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

	stopwatch watch;

	RUN( g_console )
	RUN( g_config )
	RUN( g_modules )
	RUN( g_signatures )
	RUN( g_interfaces )
	RUN( g_hooks )

	g_input->add_keybind( VK_DELETE, []( bool ) {
		if ( const auto handle = CreateThread( nullptr, 0, shutdown_routine, nullptr, 0, nullptr ) ) {
			CloseHandle( handle );
		}
	} );
}

void cheat::end( )
{
	using namespace spdlog;

	stopwatch watch;

	END( g_hooks )
	END( g_interfaces )
	END( g_signatures )
	END( g_modules )
	END( g_config )
	END( g_console )

	FreeLibraryAndExitThread( g_cheat->instance, 0 );
}
