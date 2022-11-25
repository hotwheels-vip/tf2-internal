#ifndef AD4C31F0_EFA5_40FE_8CED_D3CE58E874F0
#define AD4C31F0_EFA5_40FE_8CED_D3CE58E874F0

#include "../helpers/include.hpp"
#include <imgui/imgui.h>
#include <minhook/include/MinHook.h>

template< class T, class R >
class hook
{
private:
	void* source;
	void* original;
	std::string_view hook_name;

public:
	void create( auto source, auto destination, const char* name = "undefined" )
	{
		auto thing = MH_CreateHook( ( void* )source, ( void* )destination, &original );

		if ( thing != MH_OK ) {
			g_console->log< fmt::color::gray >( "[HOOK] " );
			g_console->log< fmt::color::red >( "Failed to create hook for {}!\n", name );

			return;
		}

		this->source = source;
		hook_name    = name;

		g_console->log< fmt::color::gray >( "[HOOK] " );
		g_console->log< fmt::color::sky_blue >( "Created hook for {}!\n", name );
	}

	void disable( )
	{
		if ( MH_DisableHook( source ) != MH_OK ) {
			g_console->log< fmt::color::gray >( "[HOOK] " );
			g_console->log< fmt::color::red >( "Failed to disable hook for {}!\n", hook_name.data( ) );

			return;
		}
		
		g_console->log< fmt::color::gray >( "[HOOK] " );
		g_console->log< fmt::color::sky_blue >( "Disabled hook for {}!\n", hook_name.data( ) );
	}

	void enable( )
	{
		if ( MH_EnableHook( source ) != MH_OK ) {
			g_console->log< fmt::color::gray >( "[HOOK] " );
			g_console->log< fmt::color::red >( "Failed to enable hook for {}!\n", hook_name.data( ) );

			return;
		}
		
		g_console->log< fmt::color::gray >( "[HOOK] " );
		g_console->log< fmt::color::sky_blue >( "Enabled hook for {}!\n", hook_name.data( ) );
	}

	void remove( )
	{
		if ( MH_RemoveHook( source ) != MH_OK ) {
			g_console->log< fmt::color::gray >( "[HOOK] " );
			g_console->log< fmt::color::red >( "Failed to remove hook for {}!\n", hook_name.data( ) );

			return;
		}
		
		g_console->log< fmt::color::gray >( "[HOOK] " );
		g_console->log< fmt::color::sky_blue >( "Removed hook for {}!\n", hook_name.data( ) );
	}

	template< typename... ARGS >
	R call( ARGS&&... Args )
	{
		return ( R )( reinterpret_cast< T* >( original )( Args... ) );
	}
};

class hooks
{
public:
	void run( );
	void end( );
};

inline hooks* g_hooks = new hooks( );

#endif // AD4C31F0_EFA5_40FE_8CED_D3CE58E874F0
