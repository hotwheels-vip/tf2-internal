#include "config.hpp"

#include <imgui/imgui.h>
#include <spdlog/spdlog.h>

void config::save( std::string name )
{
	using namespace nlohmann;
	using namespace spdlog;

	json reader;

	for ( auto& setting : settings ) {
		switch ( setting.second.type ) {
		case variable::VARIABLE_BOOL:
			reader[ setting.first ] = setting.second.bool_value;
			break;
		case variable::VARIABLE_INT:
			reader[ setting.first ] = setting.second.int_value;
			break;
		case variable::VARIABLE_FLOAT:
			reader[ setting.first ] = setting.second.float_value;
			break;
		case variable::VARIABLE_STRING:
			reader[ setting.first ] = setting.second.string_value;
			break;
		case variable::VARIABLE_COLOR:
			reader[ setting.first ] = { setting.second.color_value.x, setting.second.color_value.y, setting.second.color_value.z,
				                        setting.second.color_value.w };
			break;
		case variable::VARIABLE_VECTOR:
			reader[ setting.first ] = { setting.second.vector_value.x, setting.second.vector_value.y };
			break;
		}
	}

	std::ofstream writer( name );

	if ( writer.is_open( ) ) {
		writer << std::setw( 4 ) << reader << std::endl;
		writer.close( );
	}

	std::string file_name = name.substr( name.find_last_of( "\\/" ) + 1 );

	info( "saved config {}", file_name );
}

void config::load( std::string name )
{
	using namespace nlohmann;
	using namespace spdlog;

	std::ifstream reader( name );

	if ( reader.is_open( ) ) {
		json j;

		reader >> j;

		for ( auto& setting : settings ) {
			if ( !j.contains( setting.first ) ) {
				error( "failed to load config, missing key {}", setting.first );

				continue;
			}

			switch ( setting.second.type ) {
			case variable::VARIABLE_BOOL:
				setting.second.bool_value = j[ setting.first ].get< bool >( );
				break;
			case variable::VARIABLE_INT:
				setting.second.int_value = j[ setting.first ].get< int >( );
				break;
			case variable::VARIABLE_FLOAT:
				setting.second.float_value = j[ setting.first ].get< float >( );
				break;
			case variable::VARIABLE_STRING:
				setting.second.string_value = j[ setting.first ].get< std::string >( );
				break;
			case variable::VARIABLE_COLOR:
				setting.second.color_value = ImVec4( j[ setting.first ][ 0 ].get< float >( ), j[ setting.first ][ 1 ].get< float >( ),
				                                     j[ setting.first ][ 2 ].get< float >( ), j[ setting.first ][ 3 ].get< float >( ) );
				break;
			case variable::VARIABLE_VECTOR:
				setting.second.vector_value = ImVec2( j[ setting.first ][ 0 ].get< float >( ), j[ setting.first ][ 1 ].get< float >( ) );
				break;
			}
		}

		reader.close( );
	}

	std::string file_name = name.substr( name.find_last_of( "\\/" ) + 1 );

	info( "loaded config {}", file_name );
}

void config::insert( std::string name, config::option value )
{
	settings.insert( std::make_pair( name, value ) );
}

bool config::run( )
{
	insert( "aimbot_mouse_enabled", false );
	insert( "aimbot_mouse_fov", 0.f );
	insert( "aimbot_mouse_smoothing", 1.f );
	insert( "aimbot_mouse_hitboxes", 0b0 );
	insert( "aimbot_mouse_curve_a", ImVec2{ 0.f, 0.f } );
	insert( "aimbot_mouse_curve_b", ImVec2{ 1.f, 1.f } );
	insert( "aimbot_silent_enabled", false );
	insert( "aimbot_silent_fov", 0.f );
	insert( "aimbot_silent_hitboxes", 0b0 );
	insert( "aimbot_projectile_enabled", false );
	insert( "aimbot_projectile_invisible", false );
	insert( "aimbot_projectile_feet", false );
	insert( "aimbot_projectile_steps", 2 );
	insert( "aimbot_lagcomp_enabled", false );
	insert( "aimbot_lagcomp_time", 200 );

	insert( "visuals_player_enabled", false );
	insert( "visuals_player_teams", 0b0 );
	insert( "visuals_player_box", false );
	insert( "visuals_player_box_color", ImVec4{ 1.f, 1.f, 1.f, 1.f } );
	insert( "visuals_player_box_outline_color", ImVec4{ 0.f, 0.f, 0.f, 0.5f } );
	insert( "visuals_player_name", false );
	insert( "visuals_player_name_color", ImVec4{ 1.f, 1.f, 1.f, 1.f } );
	insert( "visuals_player_name_outline_color", ImVec4{ 0.f, 0.f, 0.f, 0.5f } );
	insert( "visuals_player_health_bar", false );
	insert( "visuals_player_health_bar_color", ImVec4{ 0.f, 1.f, 0.f, 1.f } );
	insert( "visuals_player_health_bar_outline_color", ImVec4{ 0.f, 0.f, 0.f, 0.5f } );
	insert( "visuals_player_health_bar_thickness", 2 );
	insert( "visuals_player_health_text", false );
	insert( "visuals_player_health_text_color", ImVec4{ 0.f, 1.f, 0.f, 1.f } );
	insert( "visuals_player_health_text_outline_color", ImVec4{ 0.f, 0.f, 0.f, 0.5f } );
	insert( "visuals_player_health_text_minimum", -10 );

	insert( "menu_disabled_inputs", 0b11 );

	return true;
}

bool config::end( )
{
	return true;
}
