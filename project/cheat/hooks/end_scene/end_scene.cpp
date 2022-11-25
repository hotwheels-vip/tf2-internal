#include "end_scene.hpp"

LONG end_scene::detour( IDirect3DDevice9* device )
{
	static auto multicore_rendering = _ReturnAddress( );

	if ( multicore_rendering != _ReturnAddress( ) )
		return g_end_scene->_hook.call( device );

	DWORD color_write{ }, srgb_write{ };

	device->GetRenderState( D3DRS_SRGBWRITEENABLE, &srgb_write );
	device->GetRenderState( D3DRS_COLORWRITEENABLE, &color_write );

	device->SetRenderState( D3DRS_SRGBWRITEENABLE, false );
	device->SetRenderState( D3DRS_COLORWRITEENABLE, 0xFFFFFFFF );

	// g_interfaces->device->CreateStateBlock( D3DSBT_PIXELSTATE, &g_end_scene->state );
	// g_end_scene->state->Capture( );
	// g_interfaces->device->GetVertexDeclaration( &g_end_scene->vertex );
	// g_interfaces->device->GetVertexShader( &g_end_scene->vertex_shader );

	// g_interfaces->device->SetVertexShader( nullptr );
	// g_interfaces->device->SetPixelShader( nullptr );
	// g_interfaces->device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
	// g_interfaces->device->SetRenderState( D3DRS_LIGHTING, false );
	// g_interfaces->device->SetRenderState( D3DRS_FOGENABLE, false );
	// g_interfaces->device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	// g_interfaces->device->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

	// g_interfaces->device->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
	// g_interfaces->device->SetRenderState( D3DRS_SCISSORTESTENABLE, true );
	// g_interfaces->device->SetRenderState( D3DRS_ZWRITEENABLE, false );
	// g_interfaces->device->SetRenderState( D3DRS_STENCILENABLE, false );

	// g_interfaces->device->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, false );
	// g_interfaces->device->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, true );

	// g_interfaces->device->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
	// g_interfaces->device->SetRenderState( D3DRS_ALPHATESTENABLE, false );
	// g_interfaces->device->SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE, true );
	// g_interfaces->device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	// g_interfaces->device->SetRenderState( D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA );
	// g_interfaces->device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	// g_interfaces->device->SetRenderState( D3DRS_DESTBLENDALPHA, D3DBLEND_ONE );

	// g_interfaces->device->SetRenderState( D3DRS_SRGBWRITEENABLE, false );
	// g_interfaces->device->SetRenderState( D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE |
	//                                                                   D3DCOLORWRITEENABLE_ALPHA );

	// g_interfaces->device->GetTexture( 0, &g_end_scene->texture );
	// g_interfaces->device->SetTexture( 0, nullptr );

	// g_interfaces->device->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	// g_interfaces->device->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	// g_interfaces->device->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	// g_interfaces->device->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	// g_interfaces->device->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	// g_interfaces->device->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

	// g_interfaces->device->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	// g_interfaces->device->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	ImGui_ImplDX9_NewFrame( );
	ImGui_ImplWin32_NewFrame( );

	ImGui::NewFrame( );

	CONFIG( menu_animation_speed, float );
	CONFIG( menu_indicator_transparency, float );

	auto increment_per_frame = 1.f / ( 0.2f / ( 1.f / ImGui::GetIO( ).Framerate ) ) * *menu_animation_speed;
	g_menu->alpha            = std::clamp( g_menu->alpha + ( g_menu->open ? increment_per_frame : -increment_per_frame ), 0.f, 1.f );
	auto ease_animation      = QuadraticEaseInOut( g_menu->alpha );

	ImGui::PushStyleVar( ImGuiStyleVar_Alpha, ease_animation );

	if ( g_menu->open || ease_animation > increment_per_frame * 2 )
		g_menu->run( );

	ImGui::PopStyleVar( );

	ImGui::PushStyleVar( ImGuiStyleVar_Alpha, *menu_indicator_transparency );

	g_indicators->run( );

	ImGui::PopStyleVar( );

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
