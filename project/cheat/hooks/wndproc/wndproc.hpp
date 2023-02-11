#pragma once

#include "../../helpers/include.hpp"

#include <imgui/imgui.h>
#include <windows.h>

class wndproc
{
public:
	WNDPROC original{ };
	HWND hwnd{ };

	static LRESULT WINAPI detour( const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam );

	void run( )
	{
		hwnd     = FindWindowA( "Valve001", nullptr );
		original = reinterpret_cast< WNDPROC >( SetWindowLong( hwnd, GWL_WNDPROC, reinterpret_cast< LONG_PTR >( detour ) ) );
	}

	void end( )
	{
		SetWindowLong( hwnd, GWL_WNDPROC, reinterpret_cast< LONG_PTR >( original ) );
	}
};

inline wndproc* g_wndproc = new wndproc( );
