#include "indicators.hpp"

#include "../../hooks/cl_move/cl_move.hpp"

void indicators::run( )
{
	ImGui::SetNextWindowSize( ImVec2( 170.f, 60.f ), ImGuiCond_::ImGuiCond_Always );

	ImGui::Begin( "Double Tap", nullptr,
	              ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize );
	{
		auto net_channel = reinterpret_cast< sdk::i_net_channel* >( g_interfaces->engine_client->get_net_channel_info( ) );

		if ( g_cl_move->stored == 0 )
			ImGui::TextDisabled( "No Stored Ticks" );
		else if ( g_cl_move->charging )
			ImGui::TextColored( ImColor( 149, 215, 153 ), "Charging..." );
		else if ( g_cl_move->shifting )
			ImGui::TextColored( ImColor( 149, 215, 153 ), "Shifting!" );
		else
			ImGui::TextColored( ImColor( 149, 215, 153 ), "Ready For Shift" );

		auto buffer_stored = g_cl_move->stored; // prevent the user from falsifying the value

		ImGui::SliderInt( "Shiftable Ticks", &buffer_stored, 0, 22, "%d", ImGuiSliderFlags_NoInput );
	}
	ImGui::End( );
}
