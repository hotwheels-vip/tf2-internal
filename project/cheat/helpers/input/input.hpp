//
// Created by liga on 11/11/2022.
//

#ifndef HOTWHEELS_TF2_INTERNAL_INPUT_HPP
#define HOTWHEELS_TF2_INTERNAL_INPUT_HPP

#pragma warning( disable : 4244 )

#include <array>
#include <functional>
#include <iostream>
#include <vector>
#include <windows.h>
#include <windowsx.h>

#include <sdk/include.hpp>

class input
{
public:
	enum key_state_ {
		KEY_NONE     = 0,
		KEY_UP       = 1,
		KEY_DOWN     = 2,
		KEY_RELEASED = 3
	};

	std::uint32_t max_release_time = 100;

	struct keybind {
		bool awaiting_input{ };
		std::function< void( std::uint8_t, bool ) > poll_callback{ };

		std::uint8_t key{ };
		std::function< void( bool ) > callback{ };
	};

	struct key {
		key_state_ state{ KEY_NONE };
		std::uint64_t time{ };

		key( ) = default;
		key( key_state_ state, std::uint64_t time ) : state( state ), time( time ) { }
	};

	std::array< key, 256 > keys{ };
	std::vector< keybind > keybinds{ };

	struct {
		sdk::vector position{ };
		int scroll_amount{ };

		bool in_params( int x, int y, int w, int h )
		{
			return position.x >= x && position.x <= x + w && position.y >= y && position.y <= y + h;
		}

		bool in_params( sdk::vector position, sdk::vector size )
		{
			return in_params( position.x, position.y, size.x, size.y );
		}
	} mouse;

	void think( UINT uMsg, WPARAM wParam, LPARAM lParam );

	template< auto STATE >
	bool key_state( std::uint8_t key )
	{
		auto& buff_key = keys[ key ];

		std::uint64_t time = GetTickCount64( );

		if ( STATE == key_state_::KEY_RELEASED ) {
			if ( buff_key.state == STATE ) {
				if ( time - buff_key.time <= max_release_time ) {
					return buff_key.state = key_state_::KEY_UP;
				} else {
					return buff_key.state = key_state_::KEY_UP;
				}
			}

			return false;
		} else {
			return buff_key.state == STATE;
		}
	}

	void add_keybind( std::uint8_t key, std::function< void( bool ) > callback );
	void remove_keybind( std::uint8_t key );

	void poll_keybinds( std::function< void( std::uint8_t, bool ) > callback, std::function< void( bool ) > callback_fail = nullptr );
	char* get_key_name( std::uint8_t key );
};

inline input* g_input = new input( );

#endif // HOTWHEELS_TF2_INTERNAL_INPUT_HPP
