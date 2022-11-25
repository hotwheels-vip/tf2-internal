#include "console.hpp"

void console::run( )
{
	AllocConsole( ); // Fucking pray this works LOL
	freopen_s( &file, "CONOUT$", "w", stdout );
	console = GetStdHandle( STD_OUTPUT_HANDLE );

	DWORD mode = 0;

	GetConsoleMode( console, &mode );
	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode( console, mode );
}

void console::end( )
{
	fclose( file );
	FreeConsole( );
}