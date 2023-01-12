#include "config.hpp"

#include <imgui/imgui.h>

void config::save( std::string name )
{
	using namespace nlohmann;

	json reader;

	for ( auto& setting : settings ) {
		switch ( setting.second.type ) {
		case variable::VARIABLE_BOOL:
			reader[ std::to_string( setting.first ) ] = setting.second.bool_value;
			break;
		case variable::VARIABLE_INT:
			reader[ std::to_string( setting.first ) ] = setting.second.int_value;
			break;
		case variable::VARIABLE_FLOAT:
			reader[ std::to_string( setting.first ) ] = setting.second.float_value;
			break;
		case variable::VARIABLE_STRING:
			reader[ std::to_string( setting.first ) ] = setting.second.string_value;
			break;
		case variable::VARIABLE_COLOR:
			reader[ std::to_string( setting.first ) ] = { setting.second.color_value.x, setting.second.color_value.y, setting.second.color_value.z,
				                                          setting.second.color_value.w };
			break;
		case variable::VARIABLE_VECTOR:
			reader[ std::to_string( setting.first ) ] = { setting.second.vector_value.x, setting.second.vector_value.y };
			break;
		}
	}

	std::ofstream writer( name );

	if ( writer.is_open( ) ) {
		writer << std::setw( 4 ) << reader << std::endl;
		writer.close( );
	}

	std::string file_name = name.substr( name.find_last_of( "\\/" ) + 1 );

	g_console->log< fmt::color::gray >( "[CONFIG] " );
	g_console->log< fmt::color::sky_blue >( "Saved config {}!\n", file_name.data( ) );
}

void config::load( std::string name )
{
	using namespace nlohmann;

	std::ifstream reader( name );

	if ( reader.is_open( ) ) {
		json j;

		reader >> j;

		for ( auto& setting : settings ) {
			if ( !j.contains( std::to_string( setting.first ) ) ) {
				g_console->log< fmt::color::gray >( "[CONFIG] " );
				g_console->log< fmt::color::yellow >( "Missing setting {}!\n", std::to_string( setting.first ).data( ) );

				continue;
			}

			switch ( setting.second.type ) {
			case variable::VARIABLE_BOOL:
				setting.second.bool_value = j[ std::to_string( setting.first ) ].get< bool >( );
				break;
			case variable::VARIABLE_INT:
				setting.second.int_value = j[ std::to_string( setting.first ) ].get< int >( );
				break;
			case variable::VARIABLE_FLOAT:
				setting.second.float_value = j[ std::to_string( setting.first ) ].get< float >( );
				break;
			case variable::VARIABLE_STRING:
				setting.second.string_value = j[ std::to_string( setting.first ) ].get< std::string >( );
				break;
			case variable::VARIABLE_COLOR:
				setting.second.color_value =
					ImVec4( j[ std::to_string( setting.first ) ][ 0 ].get< float >( ), j[ std::to_string( setting.first ) ][ 1 ].get< float >( ),
				            j[ std::to_string( setting.first ) ][ 2 ].get< float >( ), j[ std::to_string( setting.first ) ][ 3 ].get< float >( ) );
				break;
			case variable::VARIABLE_VECTOR:
				setting.second.vector_value =
					ImVec2( j[ std::to_string( setting.first ) ][ 0 ].get< float >( ), j[ std::to_string( setting.first ) ][ 1 ].get< float >( ) );
				break;
			}
		}

		reader.close( );
	}

	std::string file_name = name.substr( name.find_last_of( "\\/" ) + 1 );

	g_console->log< fmt::color::gray >( "[CONFIG] " );
	g_console->log< fmt::color::sky_blue >( "Loaded config {}!\n", file_name.data( ) );
}

void config::insert( std::int32_t hash, config::option value )
{
	settings.insert( std::make_pair( hash, value ) );
}

void config::run( )
{
	insert( HASH( "aimbot_mouse_enabled" ), false );
	insert( HASH( "aimbot_mouse_fov" ), 0.f );
	insert( HASH( "aimbot_mouse_smoothing" ), 1.f );
	insert( HASH( "aimbot_mouse_hitboxes" ), 0 );
	insert( HASH( "aimbot_mouse_curve_a" ), ImVec2{ 0.f, 0.f } );
	insert( HASH( "aimbot_mouse_curve_b" ), ImVec2{ 1.f, 1.f } );

	insert( HASH( "aimbot_silent_enabled" ), false );
	insert( HASH( "aimbot_silent_fov" ), 0.f );
	insert( HASH( "aimbot_silent_hitboxes" ), 0 );

	insert( HASH( "aimbot_projectile_enabled" ), false );
	insert( HASH( "aimbot_projectile_invisible" ), false );
	insert( HASH( "aimbot_projectile_feet" ), false );
	insert( HASH( "aimbot_projectile_steps" ), 2 );

	insert( HASH( "menu_disabled_inputs" ), 3 ); // 0b11
}

void config::end( ) { }

void themes::save( std::string name )
{
	using namespace nlohmann;

	json reader;

	for ( auto& color : ImGui::GetStyle( ).Colors ) {
		const char* _name = ImGui::GetStyleColorName( ( int )( &color - ImGui::GetStyle( ).Colors ) );
		float color_array[ 4 ]{ color.x, color.y, color.z, color.w };

		reader[ _name ][ "r" ] = color_array[ 0 ];
		reader[ _name ][ "g" ] = color_array[ 1 ];
		reader[ _name ][ "b" ] = color_array[ 2 ];
		reader[ _name ][ "a" ] = color_array[ 3 ];
	}

	std::ofstream writer( name );

	if ( writer.is_open( ) ) {
		writer << std::setw( 4 ) << reader << std::endl;
		writer.close( );
	}

	std::string file_name = name.substr( name.find_last_of( "\\/" ) + 1 );

	g_console->log< fmt::color::gray >( "[THEME] " );
	g_console->log< fmt::color::sky_blue >( "Saved theme {}!\n", file_name.data( ) );
}

void themes::load( std::string name )
{
	using namespace nlohmann;

	json reader;

	std::ifstream writer( name );

	if ( writer.is_open( ) ) {
		writer >> reader;
		writer.close( );
	}

	for ( auto& color : ImGui::GetStyle( ).Colors ) {
		const char* _name = ImGui::GetStyleColorName( ( int )( &color - ImGui::GetStyle( ).Colors ) );

		if ( !reader.contains( _name ) ) {
			g_console->log< fmt::color::gray >( "[THEME] " );
			g_console->log< fmt::color::yellow >( "Missing color {}!\n", _name );

			continue;
		}

		float color_array[ 4 ]{ reader[ _name ][ "r" ].get< float >( ), reader[ _name ][ "g" ].get< float >( ),
			                    reader[ _name ][ "b" ].get< float >( ), reader[ _name ][ "a" ].get< float >( ) };

		color = ImVec4( color_array[ 0 ], color_array[ 1 ], color_array[ 2 ], color_array[ 3 ] );
	}

	std::string file_name = name.substr( name.find_last_of( "\\/" ) + 1 );

	g_console->log< fmt::color::gray >( "[THEME] " );
	g_console->log< fmt::color::sky_blue >( "Loaded theme {}!\n", file_name.data( ) );
}
