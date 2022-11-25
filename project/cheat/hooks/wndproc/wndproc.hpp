//
// Created by liga on 11/11/2022.
//

#ifndef HOTWHEELS_TF2_INTERNAL_WNDPROC_HPP
#define HOTWHEELS_TF2_INTERNAL_WNDPROC_HPP

#include "../../helpers/include.hpp"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <windows.h>

class wndproc
{
public:
	WNDPROC original{ };
	HWND hwnd{ };

	static LRESULT WINAPI detour( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	void run( )
	{
		hwnd     = FindWindowA( "Valve001", nullptr );
		original = ( WNDPROC )SetWindowLong( hwnd, GWL_WNDPROC, ( LONG_PTR )detour );
	}

	void end( )
	{
		SetWindowLong( hwnd, GWL_WNDPROC, ( LONG_PTR )original );
	}
};

inline wndproc* g_wndproc = new wndproc( );

#endif // HOTWHEELS_TF2_INTERNAL_WNDPROC_HPP
