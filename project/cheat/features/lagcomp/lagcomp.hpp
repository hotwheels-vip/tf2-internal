#pragma once

#include <array>
#include <deque>
#include <iostream>
#include <sdk/include.hpp>

class lagcomp
{
public:
	struct record {
		// For record validation purposes.
		int player = -1;

		float sim_time{ };
		int tick_count{ };

		bool valid{ };

		sdk::matrix_3x4 matrix[ 128 ]{ };
	};

	std::array< int, 65 > record_location{ };
	std::array< record*, 65 > records{ };

	void update( );

	void run( record rec );
};

inline lagcomp* g_lagcomp = new lagcomp{ };
