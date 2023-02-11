#include "indicators.hpp"

#include "../../hooks/cl_move/cl_move.hpp"

void indicators::run( )
{
	ImGui::SetNextWindowSize( ImVec2( 170.f, 60.f ), ImGuiCond_::ImGuiCond_Always );

	ImGui::Begin( "double tap", nullptr,
	              ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize );
	{
		auto net_channel = reinterpret_cast< sdk::i_net_channel* >( g_interfaces->engine_client->get_net_channel_info( ) );

		if ( g_cl_move->stored == 0 )
			ImGui::TextDisabled( "no stored ticks" );
		else if ( g_cl_move->charging )
			ImGui::TextColored( ImColor( 149, 215, 153 ), "charging..." );
		else if ( g_cl_move->shifting )
			ImGui::TextColored( ImColor( 149, 215, 153 ), "shifting!" );
		else
			ImGui::TextColored( ImColor( 149, 215, 153 ), "ready for shift" );

		auto buffer_stored = g_cl_move->stored; // prevent the user from falsifying the value

		ImGui::SliderInt( "shiftable ticks", &buffer_stored, 0, 22, "%d", ImGuiSliderFlags_NoInput );
	}
	ImGui::End( );
}
