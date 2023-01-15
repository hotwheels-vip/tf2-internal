#pragma once

#include "../../helpers/include.hpp"

#include <easing/easing.h>
#include <filesystem>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

constexpr int color_picker_alpha_flags = ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreviewHalf |
                                         ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoInputs |
                                         ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar |
                                         ImGuiColorEditFlags_NoBorder;

constexpr int color_picker_no_alpha_flags = ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_InputRGB |
                                            ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop |
                                            ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder;

class menu
{
public:
	bool open                = true;
	float alpha              = 0.f;
	ImVec2 mouse_curve[ 50 ] = { };

	void run( );
};

inline menu* g_menu = new menu( );
