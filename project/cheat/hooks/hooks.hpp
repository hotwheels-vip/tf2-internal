#pragma once

#include "../helpers/include.hpp"

#include <imgui/imgui.h>
#include <minhook/include/MinHook.h>

template< class T, class R >
class hook
{
private:
	void* source{ };
	void* original{ };
	std::string_view hook_name{ };

public:
	void create( auto source, auto destination, const char* name = "undefined" )
	{
		using namespace spdlog;

		if ( const auto ret = MH_CreateHook( static_cast< void* >( source ), reinterpret_cast< void* >( destination ), &original ); ret != MH_OK ) {
			error( "failed to create hook for {} (error code {})", name, ret );

			return;
		}

		this->source = source;
		hook_name    = name;

		info( "created hook for {}", name );
	}

	void disable( )
	{
		using namespace spdlog;

		if ( const auto ret = MH_DisableHook( source ); ret != MH_OK ) {
			error( "failed to disable hook for {} (error code {})", hook_name, ret );

			return;
		}

		info( "disabled hook for {}", hook_name );
	}

	void enable( )
	{
		using namespace spdlog;

		if ( const auto ret = MH_EnableHook( source ); ret != MH_OK ) {
			error( "failed to enable hook for {} (error code {})", hook_name, ret );

			return;
		}

		info( "enabled hook for {}", hook_name );
	}

	void remove( )
	{
		using namespace spdlog;

		if ( const auto ret = MH_RemoveHook( source ); ret != MH_OK ) {
			error( "failed to remove hook for {} (error code {})", hook_name, ret );

			return;
		}

		info( "removed hook for {}", hook_name );
	}

	template< typename... ARGS >
	R call( ARGS&&... Args )
	{
		return static_cast< R >( static_cast< T* >( original )( Args... ) );
	}
};

class hooks
{
public:
	void run( );
	void end( );
};

inline hooks* g_hooks = new hooks( );
