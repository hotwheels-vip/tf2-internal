#include "end_scene.hpp"
#include "../../helpers/entity_list/entity_list.hpp"

LONG end_scene::detour( IDirect3DDevice9* device )
{
	static auto multicore_rendering = _ReturnAddress( );

	if ( multicore_rendering != _ReturnAddress( ) )
		return g_end_scene->_hook.call( device );

	if ( !g_interfaces->engine_client->is_in_game( ) || !g_interfaces->engine_client->is_connected( ) )
		g_entity_list->clear( );

	DWORD color_write{ }, srgb_write{ };

	device->GetRenderState( D3DRS_SRGBWRITEENABLE, &srgb_write );
	device->GetRenderState( D3DRS_COLORWRITEENABLE, &color_write );

	device->SetRenderState( D3DRS_SRGBWRITEENABLE, false );
	device->SetRenderState( D3DRS_COLORWRITEENABLE, 0xFFFFFFFF );

	ImGui_ImplDX9_NewFrame( );
	ImGui_ImplWin32_NewFrame( );

	ImGui::NewFrame( );

	const auto increment_per_frame = 1.f / ( 0.2f / ImGui::GetIO( ).DeltaTime );
	g_menu->alpha                  = std::clamp( g_menu->alpha + ( g_menu->open ? increment_per_frame : -increment_per_frame ), 0.f, 1.f );
	const auto ease_animation      = g_menu->alpha;

	ImGui::PushStyleVar( ImGuiStyleVar_Alpha, ease_animation );

	if ( g_menu->open || ease_animation > increment_per_frame * 2 )
		g_menu->run( );

	ImGui::PopStyleVar( );

	g_indicators->run( );

	g_visuals->run( );

	ImGui::EndFrame( );

	ImGui::Render( );

	ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );

	// g_end_scene->state->Apply( );
	// g_end_scene->state->Release( );

	// g_interfaces->device->SetVertexDeclaration( g_end_scene->vertex );
	// g_interfaces->device->SetVertexShader( g_end_scene->vertex_shader );
	// g_interfaces->device->SetTexture( 0, g_end_scene->texture );

	device->SetRenderState( D3DRS_COLORWRITEENABLE, color_write );
	device->SetRenderState( D3DRS_SRGBWRITEENABLE, srgb_write );

	return g_end_scene->_hook.call( device );
}
