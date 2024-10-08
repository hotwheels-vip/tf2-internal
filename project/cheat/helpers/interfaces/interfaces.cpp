#include "interfaces.hpp"

#include <spdlog/spdlog.h>

bool interfaces::run( )
{
	engine_client   = static_cast< sdk::i_engine_client* >( get_interface( "engine.dll", HASH( "VEngineClient013" ) ) );
	client          = static_cast< sdk::i_base_client_dll* >( get_interface( "client.dll", HASH( "VClient017" ) ) );
	entity_list     = static_cast< sdk::i_client_entity_list* >( get_interface( "client.dll", HASH( "VClientEntityList003" ) ) );
	debug_overlay   = static_cast< sdk::i_debug_overlay* >( get_interface( "engine.dll", HASH( "VDebugOverlay003" ) ) );
	cvar            = static_cast< sdk::i_con_var* >( get_interface( "vstdlib.dll", HASH( "VEngineCvar004" ) ) );
	model_info      = static_cast< sdk::i_model_info* >( get_interface( "engine.dll", HASH( "VModelInfoClient006" ) ) );
	render_view     = static_cast< sdk::i_render_view* >( get_interface( "engine.dll", HASH( "VEngineRenderView014" ) ) );
	prediction      = static_cast< sdk::c_prediction* >( get_interface( "client.dll", HASH( "VClientPrediction001" ) ) );
	game_movement   = static_cast< sdk::i_game_movement* >( get_interface( "client.dll", HASH( "GameMovement001" ) ) );
	panel           = static_cast< sdk::i_panel* >( get_interface( "vgui2.dll", HASH( "VGUI_Panel009" ) ) );
	engine_trace    = static_cast< sdk::i_engine_trace* >( get_interface( "engine.dll", HASH( "EngineTraceClient003" ) ) );
	leaf_system     = static_cast< sdk::i_client_leaf_system* >( get_interface( "client.dll", HASH( "ClientLeafSystem002" ) ) );
	model_render    = static_cast< sdk::i_model_render* >( get_interface( "engine.dll", HASH( "VEngineModel016" ) ) );
	material_system = static_cast< sdk::i_material_system* >( get_interface( "materialsystem.dll", HASH( "VMaterialSystem081" ) ) );
	localize        = static_cast< sdk::i_localize* >( get_interface( "vgui2.dll", HASH( "VGUI_Localize005" ) ) );

	input        = g_database[ HASH( "8B 0D ? ? ? ? FF 75 ? D9 45 ? 51 8B 01 D9 1C ? FF 75" ) ].add( 0x2 ).get( 2 ).as< sdk::i_input* >( );
	move_helper  = g_database[ HASH( "8B 0D ? ? ? ? 8B 46 08 68 ? ? ? ? 05 ? ? ? ? 8B 11 50" ) ].add( 0x2 ).get( 2 ).as< sdk::i_move_helper* >( );
	client_mode  = g_database[ HASH( "8B 0D ? ? ? ? 8B 02 D9 05" ) ].add( 0x2 ).get( 2 ).as< sdk::i_client_mode* >( );
	device       = g_database[ HASH( "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) ].add( 0x1 ).get( 2 ).as< IDirect3DDevice9* >( );
	globals      = g_database[ HASH( "68 ? ? ? ? 50 50 FF 12" ) ].add( 0x1 ).get( 1 ).as< sdk::i_global_vars_base* >( );
	client_state = g_database[ HASH( "B9 ? ? ? ? E8 ? ? ? ? 83 3D ? ? ? ? ? 75 59" ) ].add( 0x1 ).get( 1 ).as< sdk::i_base_client_state* >( );

	return true;
}

bool interfaces::end( )
{
	return true;
}

void* interfaces::get_interface( const char* modules, std::uint32_t hash )
{
	using namespace spdlog;

	//	std::vector< const char* > vModules = { "client.dll",         "engine.dll",        "localize.dll",        "materialsystem.dll",
	//		                                    "vguimatsurface.dll", "vgui2.dll",         "shaderapidx9.dll",    "gameoverlayrenderer.dll",
	//		                                    "vphysics.dll",       "vstdlib.dll",       "tier0.dll",           "inputsystem.dll",
	//		                                    "studiorender.dll",   "datacache.dll",     "steam_api.dll",       "matchmaking.dll",
	//		                                    "server.dll",         "serverbrowser.dll", "filesystem_stdio.dll" };

	auto create_interface = reinterpret_cast< std::uintptr_t >( GetProcAddress( GetModuleHandleA( modules ), "CreateInterface" ) );

	if ( !create_interface )
		return nullptr;

	while ( *reinterpret_cast< std::uint8_t* >( create_interface ) != 0xE9 )
		create_interface++;

	create_interface = jump_address( create_interface );

	while ( *reinterpret_cast< std::uint16_t* >( create_interface ) != 0x358B )
		create_interface++;

	auto found_interface = **reinterpret_cast< interface_*** >( create_interface + 0x2 );

	char buffer[ 128 ]{ };

	while ( found_interface ) {
		std::size_t size{ };

		for ( size = 0; found_interface->name[ size ] != '\0'; size++ ) {
			buffer[ size ] = found_interface->name[ size ];
		}

		buffer[ size ] = '\0';

		if ( RT_HASH( buffer ) == hash ) {
			info( "interface {} at {}", buffer, found_interface->get( ) );

			return found_interface->get( );
		}

		found_interface = found_interface->next;
	}

	error( "failed interface {}", hash );

	return nullptr;
}

std::uintptr_t interfaces::jump_address( std::uintptr_t pAddress )
{
	const auto jump = *reinterpret_cast< std::uintptr_t* >( pAddress + 0x1 );

	pAddress += 0x5;
	pAddress += jump;

	return pAddress;
}
