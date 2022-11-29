//
// Created by liga on 11/11/2022.
//

#include "wndproc.hpp"
#include "../cheat/features/menu/menu.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

LRESULT wndproc::detour( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if ( g_menu->open )
		ImGui_ImplWin32_WndProcHandler( hWnd, uMsg, wParam, lParam );

	g_input->think( uMsg, wParam, lParam );

	return CallWindowProc( g_wndproc->original, hWnd, uMsg, wParam, lParam );
}
