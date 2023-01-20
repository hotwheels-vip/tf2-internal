#pragma once

#include <array>
#include <iostream>
#include <sdk/include.hpp>

class lagcomp
{
private:
	struct record {
		// For record validation purposes.
		sdk::c_tf_player* player{ };

		bool is_valid{ };
		float sim_time{ };

		sdk::matrix_3x4 matracies[ 128 ]{ };
	};

public:
	std::array< int, 65 > record_iterator{ };
	std::array< record*, 65 > records{ };

	// Run before aimbob
	void update( );

	// Run during aimbob
	void run( sdk::c_tf_player* player );
};

inline lagcomp* g_lagcomp = new lagcomp{ };
