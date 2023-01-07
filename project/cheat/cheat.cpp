//
// Created by liga on 11/13/2022.
//

#include "cheat.hpp"

#include <chrono>
#include <imgui/imgui_notify.h>

DWORD WINAPI shutdown_routine( LPVOID )
{
	g_cheat->end( );

	return 0;
}

void cheat::run( )
{
	using namespace std::chrono;

	auto start = high_resolution_clock::now( );

	g_console->run( );
	g_console->log< fmt::color::gray >( "[CHEAT] " );
	g_console->log< fmt::color::sky_blue >( "Console run successful!\n" );
	g_config->run( );
	g_console->log< fmt::color::gray >( "[CHEAT] " );
	g_console->log< fmt::color::sky_blue >( "Config run successful!\n" );
	g_modules->run( );
	g_console->log< fmt::color::gray >( "[CHEAT] " );
	g_console->log< fmt::color::sky_blue >( "Modules run successful!\n" );
	g_signatures.run( );
	g_console->log< fmt::color::gray >( "[CHEAT] " );
	g_console->log< fmt::color::sky_blue >( "Signatures run successful!\n" );
	g_interfaces->run( );
	g_console->log< fmt::color::gray >( "[CHEAT] " );
	g_console->log< fmt::color::sky_blue >( "Interfaces run successful!\n" );
	g_hooks->run( );
	g_console->log< fmt::color::gray >( "[CHEAT] " );
	g_console->log< fmt::color::sky_blue >( "Hooks run successful!\n" );

	auto end = high_resolution_clock::now( );

	ImGui::InsertNotification(
		{ ImGuiToastType_Success, 3000,
	      fmt::format( "Successfully loaded in {0:.2f}s!", duration_cast< milliseconds >( end - start ).count( ) / 1000.f ).c_str( ) } );

	g_input->add_keybind( VK_DELETE, []( bool ) {
		if ( auto handle = CreateThread( nullptr, 0, shutdown_routine, nullptr, 0, nullptr ) ) {
			CloseHandle( handle );
		}
	} );
}

void cheat::end( )
{
	g_hooks->end( );
	g_console->log< fmt::color::gray >( "[CHEAT] " );
	g_console->log< fmt::color::sky_blue >( "Hooks end successful!\n" );
	g_interfaces->end( );
	g_console->log< fmt::color::gray >( "[CHEAT] " );
	g_console->log< fmt::color::sky_blue >( "Interfaces end successful!\n" );
	g_signatures.end( );
	g_console->log< fmt::color::gray >( "[CHEAT] " );
	g_console->log< fmt::color::sky_blue >( "Signatures end successful!\n" );
	g_modules->end( );
	g_console->log< fmt::color::gray >( "[CHEAT] " );
	g_console->log< fmt::color::sky_blue >( "Modules end successful!\n" );
	g_config->end( );
	g_console->log< fmt::color::gray >( "[CHEAT] " );
	g_console->log< fmt::color::sky_blue >( "Config end successful!\n" );
	g_console->end( );

	FreeLibraryAndExitThread( instance, 0 );
}
