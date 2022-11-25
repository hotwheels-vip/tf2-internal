#ifndef E01C1CC3_A723_4DB5_9D4C_86FA3700B808
#define E01C1CC3_A723_4DB5_9D4C_86FA3700B808

#include "../../features/menu/menu.hpp"
#include "../../features/indicators/indicators.hpp"
#include "../../helpers/include.hpp"
#include "../hooks.hpp"

#include <Windows.h>
#include <d3dx9.h>
#include <easing/easing.h>
#include <filesystem>
#include <imgui/imgui.h>
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

		ImGui_ImplDX9_Init( g_interfaces->device );
		ImGui_ImplWin32_Init( FindWindowA( "Valve001", nullptr ) );

		//		if ( !std::filesystem::exists( "C:\\Hotwheels\\" ) ) {
		std::filesystem::create_directories( "C:\\Hotwheels\\" );
		std::filesystem::create_directories( "C:\\Hotwheels\\Configs" );
		std::filesystem::create_directories( "C:\\Hotwheels\\Menu" );
		std::filesystem::create_directories( "C:\\Hotwheels\\Themes" );
		//		}

		ImGui::GetIO( ).IniFilename = "C:\\Hotwheels\\Menu\\Config.ini";
		// Rounded Visual Studio style by RedNicStone from ImThemes
		ImGui::GetIO( ).ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGuiStyle& style = ImGui::GetStyle( );

		style.Alpha                     = 1.0f;
		style.DisabledAlpha             = 0.6000000238418579f;
		style.WindowPadding             = ImVec2( 8.0f, 8.0f );
		style.WindowRounding            = 4.0f;
		style.WindowBorderSize          = 0.0f;
		style.WindowMinSize             = ImVec2( 32.0f, 32.0f );
		style.WindowTitleAlign          = ImVec2( 0.0f, 0.5f );
		style.WindowMenuButtonPosition  = ImGuiDir_Left;
		style.ChildRounding             = 0.0f;
		style.ChildBorderSize           = 1.0f;
		style.PopupRounding             = 4.0f;
		style.PopupBorderSize           = 1.0f;
		style.FramePadding              = ImVec2( 4.0f, 3.0f );
		style.FrameRounding             = 2.5f;
		style.FrameBorderSize           = 0.0f;
		style.ItemSpacing               = ImVec2( 8.0f, 4.0f );
		style.ItemInnerSpacing          = ImVec2( 4.0f, 4.0f );
		style.CellPadding               = ImVec2( 4.0f, 2.0f );
		style.IndentSpacing             = 21.0f;
		style.ColumnsMinSpacing         = 6.0f;
		style.ScrollbarSize             = 11.0f;
		style.ScrollbarRounding         = 2.5f;
		style.GrabMinSize               = 10.0f;
		style.GrabRounding              = 2.0f;
		style.TabRounding               = 3.5f;
		style.TabBorderSize             = 0.0f;
		style.TabMinWidthForCloseButton = 0.0f;
		style.ColorButtonPosition       = ImGuiDir_Right;
		style.ButtonTextAlign           = ImVec2( 0.5f, 0.5f );
		style.SelectableTextAlign       = ImVec2( 0.0f, 0.0f );

		style.Colors[ ImGuiCol_Text ]                  = ImVec4( 1.0f, 1.0f, 1.0f, 1.0f );
		style.Colors[ ImGuiCol_TextDisabled ]          = ImVec4( 0.5921568870544434f, 0.5921568870544434f, 0.5921568870544434f, 1.0f );
		style.Colors[ ImGuiCol_WindowBg ]              = ImVec4( 0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f );
		style.Colors[ ImGuiCol_ChildBg ]               = ImVec4( 0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f );
		style.Colors[ ImGuiCol_PopupBg ]               = ImVec4( 0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f );
		style.Colors[ ImGuiCol_Border ]                = ImVec4( 0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f );
		style.Colors[ ImGuiCol_BorderShadow ]          = ImVec4( 0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f );
		style.Colors[ ImGuiCol_FrameBg ]               = ImVec4( 0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f );
		style.Colors[ ImGuiCol_FrameBgHovered ]        = ImVec4( 0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f );
		style.Colors[ ImGuiCol_FrameBgActive ]         = ImVec4( 0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f );
		style.Colors[ ImGuiCol_TitleBg ]               = ImVec4( 0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f );
		style.Colors[ ImGuiCol_TitleBgActive ]         = ImVec4( 0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f );
		style.Colors[ ImGuiCol_TitleBgCollapsed ]      = ImVec4( 0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f );
		style.Colors[ ImGuiCol_MenuBarBg ]             = ImVec4( 0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f );
		style.Colors[ ImGuiCol_ScrollbarBg ]           = ImVec4( 0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f );
		style.Colors[ ImGuiCol_ScrollbarGrab ]         = ImVec4( 0.321568638086319f, 0.321568638086319f, 0.3333333432674408f, 1.0f );
		style.Colors[ ImGuiCol_ScrollbarGrabHovered ]  = ImVec4( 0.3529411852359772f, 0.3529411852359772f, 0.3725490272045135f, 1.0f );
		style.Colors[ ImGuiCol_ScrollbarGrabActive ]   = ImVec4( 0.3529411852359772f, 0.3529411852359772f, 0.3725490272045135f, 1.0f );
		style.Colors[ ImGuiCol_CheckMark ]             = ImVec4( 0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f );
		style.Colors[ ImGuiCol_SliderGrab ]            = ImVec4( 0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f );
		style.Colors[ ImGuiCol_SliderGrabActive ]      = ImVec4( 0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f );
		style.Colors[ ImGuiCol_Button ]                = ImVec4( 0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f );
		style.Colors[ ImGuiCol_ButtonHovered ]         = ImVec4( 0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f );
		style.Colors[ ImGuiCol_ButtonActive ]          = ImVec4( 0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f );
		style.Colors[ ImGuiCol_Header ]                = ImVec4( 0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f );
		style.Colors[ ImGuiCol_HeaderHovered ]         = ImVec4( 0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f );
		style.Colors[ ImGuiCol_HeaderActive ]          = ImVec4( 0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f );
		style.Colors[ ImGuiCol_Separator ]             = ImVec4( 0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f );
		style.Colors[ ImGuiCol_SeparatorHovered ]      = ImVec4( 0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f );
		style.Colors[ ImGuiCol_SeparatorActive ]       = ImVec4( 0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f );
		style.Colors[ ImGuiCol_ResizeGrip ]            = ImVec4( 0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f );
		style.Colors[ ImGuiCol_ResizeGripHovered ]     = ImVec4( 0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f );
		style.Colors[ ImGuiCol_ResizeGripActive ]      = ImVec4( 0.321568638086319f, 0.321568638086319f, 0.3333333432674408f, 1.0f );
		style.Colors[ ImGuiCol_Tab ]                   = ImVec4( 0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f );
		style.Colors[ ImGuiCol_TabHovered ]            = ImVec4( 0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f );
		style.Colors[ ImGuiCol_TabActive ]             = ImVec4( 0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f );
		style.Colors[ ImGuiCol_TabUnfocused ]          = ImVec4( 0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f );
		style.Colors[ ImGuiCol_TabUnfocusedActive ]    = ImVec4( 0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f );
		style.Colors[ ImGuiCol_PlotLines ]             = ImVec4( 0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f );
		style.Colors[ ImGuiCol_PlotLinesHovered ]      = ImVec4( 0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f );
		style.Colors[ ImGuiCol_PlotHistogram ]         = ImVec4( 0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f );
		style.Colors[ ImGuiCol_PlotHistogramHovered ]  = ImVec4( 0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f );
		style.Colors[ ImGuiCol_TableHeaderBg ]         = ImVec4( 0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f );
		style.Colors[ ImGuiCol_TableBorderStrong ]     = ImVec4( 0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f );
		style.Colors[ ImGuiCol_TableBorderLight ]      = ImVec4( 0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f );
		style.Colors[ ImGuiCol_TableRowBg ]            = ImVec4( 0.0f, 0.0f, 0.0f, 0.0f );
		style.Colors[ ImGuiCol_TableRowBgAlt ]         = ImVec4( 1.0f, 1.0f, 1.0f, 0.05999999865889549f );
		style.Colors[ ImGuiCol_TextSelectedBg ]        = ImVec4( 0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f );
		style.Colors[ ImGuiCol_DragDropTarget ]        = ImVec4( 0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f );
		style.Colors[ ImGuiCol_NavHighlight ]          = ImVec4( 0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f );
		style.Colors[ ImGuiCol_NavWindowingHighlight ] = ImVec4( 1.0f, 1.0f, 1.0f, 0.699999988079071f );
		style.Colors[ ImGuiCol_NavWindowingDimBg ]     = ImVec4( 0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f );
		style.Colors[ ImGuiCol_ModalWindowDimBg ]      = ImVec4( 0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f );

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

#endif // E01C1CC3_A723_4DB5_9D4C_86FA3700B808
