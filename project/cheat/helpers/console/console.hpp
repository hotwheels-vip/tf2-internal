#pragma once

#include <Windows.h>
#include <iostream>
#include <string>

class console
{
private:
	HANDLE console_handle;
	FILE* file;

public:
	bool run( );
	bool end( );

	//	Deprecated
	//	template< fmt::color COLOR = fmt::color::white_smoke, typename... ARGS >
	//	void log( fmt::string_view format, ARGS&&... args )
	//	{
	//		std::string formatted_string = fmt::vformat( format, fmt::make_format_args( args... ) );
	//
	//		fmt::print( fmt::fg( COLOR ), formatted_string );
	//	}
};

inline console* g_console = new console( );
