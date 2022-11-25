//
// Created by liga on 11/11/2022.
//

#ifndef HOTWHEELS_TF2_INTERNAL_MENU_HPP
#define HOTWHEELS_TF2_INTERNAL_MENU_HPP

#include "../../helpers/include.hpp"
#include <easing/easing.h>
#include <filesystem>
#include <fmt/format.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

class menu
{
public:
	bool open    = true;
	float alpha = 0.f;

	void run( );
};

inline menu* g_menu = new menu( );

#endif // HOTWHEELS_TF2_INTERNAL_MENU_HPP
