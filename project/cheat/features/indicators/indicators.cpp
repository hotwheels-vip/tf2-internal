#include "indicators.hpp"

#include "../../hooks/cl_move/cl_move.hpp"

void indicators::run( )
{
	ImGui::SetNextWindowSize( ImVec2( 150.f, 40.f ), ImGuiCond_::ImGuiCond_Always );

	ImGui::Begin( "Double Tap", nullptr,
	              ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize );
	{
		auto net_channel = ( sdk::i_net_channel* )g_interfaces->engine_client->get_net_channel_info( );

		if ( net_channel && net_channel->get_drop_number( ) > 3 )
			ImGui::TextColored( ImColor( 255, 98, 98 ), "High Packet Loss!" );

		if ( net_channel && net_channel->get_latency( 0 ) > 90 )
			ImGui::TextColored( ImColor( 255, 234, 115 ), "High Ping!" );

		auto buffer_stored = g_cl_move->stored; // prevent the user from falsifying the value

		ImGui::SliderInt( "Shiftable Ticks", &buffer_stored, 0, 22, "%d", ImGuiSliderFlags_NoInput );
	}
	ImGui::End( );
}
