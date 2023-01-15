#pragma once

#include <fstream>
#include <hash/hash.hpp>
#include <imgui/imgui.h>
#include <iostream>
#include <json/json.hpp>
#include <string>
#include <unordered_map>
#include <utility>

#include "../console/console.hpp"

class config
{
public:
	enum class variable : int {
		VARIABLE_BOOL,
		VARIABLE_INT,
		VARIABLE_FLOAT,
		VARIABLE_COLOR,
		VARIABLE_STRING,
		VARIABLE_VECTOR
	};

	struct option {
	public:
		variable type;

		bool bool_value;
		int int_value;
		float float_value;
		std::string string_value;
		ImVec4 color_value;
		ImVec2 vector_value;

		option( bool value )
		{
			type       = variable::VARIABLE_BOOL;
			bool_value = value;
		}

		option( int value )
		{
			type      = variable::VARIABLE_INT;
			int_value = value;
		}

		option( float value )
		{
			type        = variable::VARIABLE_FLOAT;
			float_value = value;
		}

		option( std::string value )
		{
			type         = variable::VARIABLE_STRING;
			string_value = std::move( value );
		}

		option( ImVec4 value )
		{
			type        = variable::VARIABLE_COLOR;
			color_value = value;
		}

		option( ImVec2 value )
		{
			type         = variable::VARIABLE_VECTOR;
			vector_value = value;
		}
	};

	std::unordered_map< std::int32_t, option > settings{ };

	void run( );
	void end( );

	void save( std::string name );
	void load( std::string name );

	void insert( std::int32_t hash, option value );

	template< typename T >
	T* find( std::uint32_t hash )
	{
		auto it = settings.find( hash );

		switch ( it->second.type ) {
		case variable::VARIABLE_BOOL:
			return ( T* )&it->second.bool_value;
		case variable::VARIABLE_INT:
			return ( T* )&it->second.int_value;
		case variable::VARIABLE_FLOAT:
			return ( T* )&it->second.float_value;
		case variable::VARIABLE_STRING:
			return ( T* )&it->second.string_value;
		case variable::VARIABLE_COLOR:
			return ( T* )&it->second.color_value;
		case variable::VARIABLE_VECTOR:
			return ( T* )&it->second.vector_value;
		default:
			return ( T* )nullptr;
		}
	}
};

inline config* g_config = new config( );

#define CONFIG( name, type ) static type* name = g_config->find< type >( HASH( #name ) )
