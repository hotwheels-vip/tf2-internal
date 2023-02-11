#pragma once

#include <windows.h>

#include "helpers/include.hpp"
#include "hooks/hooks.hpp"

class cheat
{
public:
	HINSTANCE instance{ };

	void run( );
	void end( );
};

inline cheat* g_cheat = new cheat( );

#define RUN( object )                                                                                                                                \
	try {                                                                                                                                            \
		if ( ( object )->run( ) ) {                                                                                                                  \
			info( CONCAT( #object, " initialized in {:0.2f}s" ), watch );                                                                            \
		}                                                                                                                                            \
	} catch ( std::exception & e ) {                                                                                                                 \
		error( CONCAT( #object, " failed {}" ), e.what( ) );                                                                                         \
	}

#define END( object )                                                                                                                                \
	try {                                                                                                                                            \
		if ( ( object )->end( ) ) {                                                                                                                  \
			info( CONCAT( #object, " uninitialized in {:0.2f}s" ), watch );                                                                          \
		}                                                                                                                                            \
	} catch ( std::exception & e ) {                                                                                                                 \
		error( CONCAT( #object, " failed {}" ), e.what( ) );                                                                                         \
	}
