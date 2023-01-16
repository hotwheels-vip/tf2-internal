#pragma once

#include "../hooks.hpp"

#include "../../features/indicators/indicators.hpp"
#include "../../features/menu/menu.hpp"
#include "../../features/visuals/visuals.hpp"
#include "../../helpers/include.hpp"

#include <Windows.h>
#include <d3dx9.h>
#include <easing/easing.h>
#include <filesystem>
#include <imgui/fonts.h>
#include <imgui/imgui.h>
#include <imgui/imgui_freetype.h>
#include <imgui/imgui_impl_dx9.h>
#include <imgui/imgui_impl_win32.h>

class end_scene
{
private:
	hook< HRESULT( __stdcall )( IDirect3DDevice9* ), HRESULT > _hook{ };

public:
	IDirect3DStateBlock9* state{ };
	IDirect3DVertexDeclaration9* vertex{ };
	IDirect3DVertexShader9* vertex_shader{ };
	DWORD color_write{ }, srgb_write{ };
	IDirect3DBaseTexture9* texture{ };

	static LONG WINAPI detour( IDirect3DDevice9* device );

	void run( )
	{
		g_input->add_keybind( VK_INSERT, []( bool pressed ) {
			if ( pressed )
				g_menu->open = !g_menu->open;
		} );

		ImGui::CreateContext( );
		ImGui::StyleColorsDark( );

		ImGui_ImplDX9_Init( g_interfaces->device );
		ImGui_ImplWin32_Init( FindWindowA( "Valve001", nullptr ) );

		std::filesystem::create_directories( "C:\\Hotwheels\\" );
		std::filesystem::create_directories( "C:\\Hotwheels\\Configs" );
		std::filesystem::create_directories( "C:\\Hotwheels\\Menu" );
		std::filesystem::create_directories( "C:\\Hotwheels\\Themes" );

		ImGui::GetIO( ).IniFilename = "C:\\Hotwheels\\Menu\\Config.ini";

		auto& style = ImGui::GetStyle( );
		auto& io    = ImGui::GetIO( );

		/* setup styles */
		[ & ]( ) {
			style.WindowRounding    = 5.f;
			style.ChildRounding     = 0.f;
			style.FrameRounding     = 2.f;
			style.GrabRounding      = 3.f;
			style.PopupRounding     = 3.f;
			style.ScrollbarRounding = 0.f;

			style.FrameBorderSize  = 0.f;
			style.WindowBorderSize = 0.f;
			style.PopupBorderSize  = 0.f;
			style.ScrollbarSize    = 8.f;
			style.GrabMinSize      = 0.f;

			style.WindowPadding   = ImVec2( 8, 8 );
			style.FramePadding    = ImVec2( 0, 0 );
			style.ButtonTextAlign = ImVec2( 0.5f, 0.5f );
			style.ItemSpacing     = ImVec2( 8, 8 );

			style.AntiAliasedFill        = true;
			style.AntiAliasedLines       = true;
			style.AntiAliasedLinesUseTex = true;
		}( );

		/* setup colours */
		[ & ]( ) {
			style.Colors[ ImGuiCol_::ImGuiCol_WindowBg ]  = ImVec4( 10 / 255.f, 10 / 255.f, 10 / 255.f, 1.f );
			style.Colors[ ImGuiCol_::ImGuiCol_ChildBg ]   = ImVec4( 15 / 255.f, 15 / 255.f, 15 / 255.f, 1.f );
			style.Colors[ ImGuiCol_::ImGuiCol_PopupBg ]   = ImVec4( 20 / 255.f, 20 / 255.f, 20 / 255.f, 1.f );
			style.Colors[ ImGuiCol_::ImGuiCol_CheckMark ] = ImVec4( 0 / 255.f, 0 / 255.f, 0 / 255.f, 1.f );
			style.Colors[ ImGuiCol_::ImGuiCol_Button ]    = ImVec4( 20 / 255.f, 20 / 255.f, 20 / 255.f, 1.f );

			style.Colors[ ImGuiCol_::ImGuiCol_Border ]       = ImVec4( 0 / 255.f, 0 / 255.f, 0 / 255.f, 0.f );
			style.Colors[ ImGuiCol_::ImGuiCol_BorderShadow ] = ImVec4( 0 / 255.f, 0 / 255.f, 0 / 255.f, 0.f );
		}( );

		ImFontConfig font_config = { };
		font_config.FontBuilderFlags =
			ImGuiFreeTypeBuilderFlags::ImGuiFreeTypeBuilderFlags_Monochrome | ImGuiFreeTypeBuilderFlags::ImGuiFreeTypeBuilderFlags_MonoHinting;

		verdana_11    = io.Fonts->AddFontFromMemoryCompressedTTF( verdana_compressed_data, verdana_compressed_size, 11.f, &font_config );
		verdana_bd_11 = io.Fonts->AddFontFromMemoryCompressedTTF( verdana_bold_compressed_data, verdana_bold_compressed_size, 11.f, &font_config );

		static const ImWchar second_icon_font_ranges[] = { ICON_MIN_FK, ICON_MAX_FK, 0 };

		second_icon_20 = io.Fonts->AddFontFromMemoryCompressedTTF( second_icon_font_compressed_data, second_icon_font_compressed_size, 20.f, 0,
		                                                           second_icon_font_ranges );

		static const ImWchar first_icon_font_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

		first_icon_14 =
			io.Fonts->AddFontFromMemoryCompressedTTF( icon_font_compressed_data, icon_font_compressed_size, 14.f, 0, first_icon_font_ranges );

		icon_20 = io.Fonts->AddFontFromMemoryCompressedTTF( icon_font_compressed_data, icon_font_compressed_size, 20.f, 0, first_icon_font_ranges );

		ImGuiFreeType::BuildFontAtlas( io.Fonts, 0x0 );

		_hook.create( g_virtuals->get_virtual_function( g_interfaces->device, 42 ), detour, "end_scene" );
	}

	void end( )
	{
		_hook.disable( );

		ImGui_ImplWin32_Shutdown( );
		ImGui_ImplDX9_Shutdown( );

		ImGui::DestroyContext( );

		_hook.remove( );
	}
};

inline end_scene* g_end_scene = new end_scene( );
