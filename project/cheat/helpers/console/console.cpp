#include "console.hpp"

bool console::run( )
{
	AllocConsole( ); // Fucking pray this works LOL
	freopen_s( &file, "CONOUT$", "w", stdout );
	console_handle = GetStdHandle( STD_OUTPUT_HANDLE );

	DWORD mode = 0;

	GetConsoleMode( console_handle, &mode );
	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode( console_handle, mode );

	return true;
}

bool console::end( )
{
	fclose( g_console->file );
	FreeConsole( );

	return true;
}
