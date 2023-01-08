#include "indicators.hpp"
#include "../../hooks/cl_move/cl_move.hpp"

void indicators::run( )
{
	ImGui::SetNextWindowSize( ImVec2( 150.f, 40.f ), ImGuiCond_::ImGuiCond_Always );

	ImGui::Begin( "Double Tap", nullptr,
	              ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize );
	{
		auto buffer_stored = g_cl_move->stored; // prevent the user from falsifying the value

		ImGui::SliderInt( "Shiftable Ticks", &buffer_stored, 0, 22, "%d", ImGuiSliderFlags_NoInput );
	}
	ImGui::End( );
}
