#ifndef DC61F3B3_BE78_4958_9120_33C500E3F369
#define DC61F3B3_BE78_4958_9120_33C500E3F369

#include "../../../dependencies/fmt/color.h"
#include "../../../dependencies/fmt/core.h"

#include <Windows.h>
#include <iostream>
#include <string>

class console
{
private:
	HANDLE console;
	FILE* file;

public:
	void run( );
	void end( );

	template< fmt::color COLOR = fmt::color::white_smoke, typename... ARGS >
	void log( fmt::string_view format, ARGS&&... args )
	{
		std::string formatted_string = fmt::vformat( format, fmt::make_format_args( args... ) );

		fmt::print( fmt::fg( COLOR ), formatted_string );
	}
};

inline console* g_console = new console( );

#endif // DC61F3B3_BE78_4958_9120_33C500E3F369
