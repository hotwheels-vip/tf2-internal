#include "input.hpp"

void input::think( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	std::uint8_t key = 0;
	key_state_ state = KEY_UP;

	mouse.scroll_amount = 0;

	switch ( uMsg ) {
	case WM_KEYDOWN:
		key   = wParam;
		state = key_state_::KEY_DOWN;
		break;
	case WM_KEYUP:
		key   = wParam;
		state = key_state_::KEY_UP;
		break;
	case WM_LBUTTONDOWN:
		key   = VK_LBUTTON;
		state = key_state_::KEY_DOWN;
		break;
	case WM_LBUTTONUP:
		key   = VK_LBUTTON;
		state = key_state_::KEY_UP;
		break;
	case WM_LBUTTONDBLCLK:
		key   = VK_LBUTTON;
		state = key_state_::KEY_DOWN;
		break;
	case WM_RBUTTONDOWN:
		key   = VK_RBUTTON;
		state = key_state_::KEY_DOWN;
		break;
	case WM_RBUTTONUP:
		key   = VK_RBUTTON;
		state = key_state_::KEY_UP;
		break;
	case WM_RBUTTONDBLCLK:
		key   = VK_RBUTTON;
		state = key_state_::KEY_DOWN;
		break;
	case WM_MBUTTONDOWN:
		key   = VK_MBUTTON;
		state = key_state_::KEY_DOWN;
		break;
	case WM_MBUTTONUP:
		key   = VK_MBUTTON;
		state = key_state_::KEY_UP;
		break;
	case WM_MBUTTONDBLCLK:
		key   = VK_MBUTTON;
		state = key_state_::KEY_DOWN;
		break;
	case WM_XBUTTONDOWN:
		key   = GET_XBUTTON_WPARAM( wParam ) == XBUTTON1 ? XBUTTON1 : XBUTTON2;
		state = key_state_::KEY_DOWN;
		break;
	case WM_XBUTTONUP:
		key   = GET_XBUTTON_WPARAM( wParam ) == XBUTTON1 ? XBUTTON1 : XBUTTON2;
		state = key_state_::KEY_UP;
		break;
	case WM_XBUTTONDBLCLK:
		key   = GET_XBUTTON_WPARAM( wParam ) == XBUTTON1 ? XBUTTON1 : XBUTTON2;
		state = key_state_::KEY_DOWN;
		break;
	case WM_MOUSEMOVE:
		mouse.position = sdk::vector( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );
		break;
	case WM_MOUSEWHEEL:
		mouse.scroll_amount = -( GET_WHEEL_DELTA_WPARAM( wParam ) / ( WHEEL_DELTA / 4 ) );
		break;
	case WM_KILLFOCUS:
	case WM_SETFOCUS:
		for ( auto& key : keys )
			key.state = key_state_::KEY_UP;
		break;
	default:
		break;
	}

	std::uint64_t iTime = GetTickCount64( );

	if ( key ) {
		if ( state == key_state_::KEY_UP && keys[ key ].state == key_state_::KEY_DOWN ) {
			keys[ key ] = { key_state_::KEY_RELEASED, iTime };
		} else {
			keys[ key ] = { state, iTime };
		}

		for ( auto& i : keybinds ) {
			if ( i.awaiting_input ) {
				if ( key != VK_ESCAPE && key != VK_LBUTTON && key != VK_RBUTTON && key != VK_MBUTTON ) {
					i.poll_callback( key, state == key_state_::KEY_UP ? false : state == key_state_::KEY_DOWN );
				} else {
					i.callback( state == key_state_::KEY_UP ? false : state == key_state_::KEY_DOWN );
				}
			}

			if ( i.key == key ) {
				i.callback( state == key_state_::KEY_UP ? false : state == key_state_::KEY_DOWN );
			}
		}
	}
}

void input::add_keybind( std::uint8_t key, std::function< void( bool ) > callback )
{
	keybinds.push_back( { false, nullptr, key, callback } );
}

void input::remove_keybind( std::uint8_t key )
{
	for ( auto it = keybinds.begin( ); it != keybinds.end( ); ) {
		if ( it->key == key ) {
			keybinds.erase( it );
		} else {
			it++;
		}
	}
}

void input::poll_keybinds( std::function< void( std::uint8_t, bool ) > callback, std::function< void( bool ) > callback_fail )
{
	keybinds.push_back( { true, callback, 0, callback_fail } );
}

char* input::get_key_name( std::uint8_t key )
{
	const char* key_names[] = {
		"Unknown",
		"LBUTTON",
		"RBUTTON",
		"CANCEL",
		"MBUTTON",
		"XBUTTON1",
		"XBUTTON2",
		"Unknown",
		"BACK",
		"TAB",
		"Unknown",
		"Unknown",
		"CLEAR",
		"RETURN",
		"Unknown",
		"Unknown",
		"SHIFT",
		"CONTROL",
		"MENU",
		"PAUSE",
		"CAPITAL",
		"KANA",
		"Unknown",
		"JUNJA",
		"FINAL",
		"KANJI",
		"Unknown",
		"ESCAPE",
		"CONVERT",
		"NONCONVERT",
		"ACCEPT",
		"MODECHANGE",
		"SPACE",
		"PRIOR",
		"NEXT",
		"END",
		"HOME",
		"LEFT",
		"UP",
		"RIGHT",
		"DOWN",
		"SELECT",
		"PRINT",
		"EXECUTE",
		"SNAPSHOT",
		"INSERT",
		"DELETE",
		"HELP",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"LWIN",
		"RWIN",
		"APPS",
		"Unknown",
		"SLEEP",
		"NUMPAD0",
		"NUMPAD1",
		"NUMPAD2",
		"NUMPAD3",
		"NUMPAD4",
		"NUMPAD5",
		"NUMPAD6",
		"NUMPAD7",
		"NUMPAD8",
		"NUMPAD9",
		"MULTIPLY",
		"ADD",
		"SEPARATOR",
		"SUBTRACT",
		"DECIMAL",
		"DIVIDE",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",
		"F13",
		"F14",
		"F15",
		"F16",
		"F17",
		"F18",
		"F19",
		"F20",
		"F21",
		"F22",
		"F23",
		"F24",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"NUMLOCK",
		"SCROLL",
		"OEM_NEC_EQUAL",
		"OEM_FJ_MASSHOU",
		"OEM_FJ_TOUROKU",
		"OEM_FJ_LOYA",
		"OEM_FJ_ROYA",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"LSHIFT",
		"RSHIFT",
		"LCONTROL",
		"RCONTROL",
		"LMENU",
		"RMENU",
	};

	return const_cast< char* >( key_names[ key ] );
}
