#include "indicators.hpp"
#include "../../hooks/cl_move/cl_move.hpp"

void indicators::run( )
{
	ImGui::Begin( "Double Tap", nullptr,
	              ( g_menu->open ? ImGuiWindowFlags_None : ImGuiWindowFlags_NoTitleBar ) | ImGuiWindowFlags_AlwaysAutoResize |
	                  ImGuiWindowFlags_NoResize );
	{
		ImGui::SliderInt( "##Percent", &g_cl_move->stored, 0, 22, "%d", ImGuiSliderFlags_NoInput );
	}
	ImGui::End( );
}
