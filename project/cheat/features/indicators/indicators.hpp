#pragma once

#include "../../helpers/include.hpp"
#include "../menu/menu.hpp"

#include <easing/easing.h>
#include <filesystem>
#include <fmt/format.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

class indicators
{
public:
	void run( );
};

inline indicators* g_indicators = new indicators( );
