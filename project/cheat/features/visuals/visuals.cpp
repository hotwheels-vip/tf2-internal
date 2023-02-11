#include "visuals.hpp"
#include <imgui/imgui.h>

void draw_image( const int index, const unsigned char* data, const int data_size, const ImVec2 pos, const ImVec2 size, const ImColor color )
{
	static std::map< unsigned int, PDIRECT3DTEXTURE9 > texture_cache{ };

	if ( !texture_cache[ index ] ) {
		PDIRECT3DTEXTURE9 buffer{ };

		if ( D3DXCreateTextureFromFileInMemory( g_interfaces->device, data, data_size, &buffer ) != S_OK )
			return;

		texture_cache[ index ] = buffer;
	}

	const auto draw_list = ImGui::GetBackgroundDrawList( );

	draw_list->AddImage( texture_cache[ index ], pos, { pos.x + size.x, pos.y + size.y }, { 0.f, 0.f }, { 1.f, 1.f }, color );
}

void draw_weapon_icon( sdk::c_tf_player* player, ImVec2 position, ImVec2 size )
{
	if ( !player )
		return;

	auto weapon_handle = player->active_weapon( );

	if ( !weapon_handle.index )
		return;

	auto weapon = reinterpret_cast< sdk::c_tf_weapon_base* >( g_interfaces->entity_list->get_client_entity_from_handle( weapon_handle ) );

	if ( !weapon )
		return;

	auto type = weapon->get_weapon_id( );

	switch ( type ) {
	case sdk::tf_weapon_scattergun:
		return draw_image( HASH( "scattergun" ), icon_scattergun.data( ), icon_scattergun.size( ), position, size, ImColor( 255, 255, 255 ) );
	default:
		return;
		// return draw_image( HASH( "default" ), icon_.data( ), Killicon_golden_frying_pan.size( ), position, size,
		//                    ImColor( 255, 255, 255 ) );
	}
}

std::pair< ImVec4, bool > bounding_box( sdk::c_tf_player* player )
{
	auto on_screen         = false;
	const auto screen_size = ImGui::GetIO( ).DisplaySize;

	const sdk::vector mins = player->mins( );
	const sdk::vector maxs = player->maxs( );

	const sdk::matrix_3x4 transform = player->rgfl_coordinate_frame( );

	const sdk::vector points[] = { sdk::vector( mins.x, mins.y, mins.z ), sdk::vector( mins.x, maxs.y, mins.z ),
		                           sdk::vector( maxs.x, maxs.y, mins.z ), sdk::vector( maxs.x, mins.y, mins.z ),
		                           sdk::vector( maxs.x, maxs.y, maxs.z ), sdk::vector( mins.x, maxs.y, maxs.z ),
		                           sdk::vector( mins.x, mins.y, maxs.z ), sdk::vector( maxs.x, mins.y, maxs.z ) };

	sdk::vector translated_points[ 8 ];

	for ( int i = 0; i < 8; i++ )
		translated_points[ i ] = math::vector_transform( points[ i ], transform );

	ImVec2 screen_points[ 8 ];

	on_screen = false;

	for ( int i = 0; i < 8; i++ ) {
		const auto [ screen_point, on_screen_ ] = math::world_to_screen( translated_points[ i ] );

		screen_points[ i ] = screen_point;

		if ( on_screen_ && screen_point.x >= 0 && screen_point.y >= 0 && screen_point.x <= screen_size.x && screen_point.y <= screen_size.y )
			on_screen = true;
	}

	if ( !on_screen )
		return { };

	float top    = screen_points[ 0 ].y;
	float left   = screen_points[ 0 ].x;
	float right  = screen_points[ 0 ].x;
	float bottom = screen_points[ 0 ].y;

	for ( int i = 1; i < 8; i++ ) {
		if ( left > screen_points[ i ].x )
			left = screen_points[ i ].x;
		if ( top > screen_points[ i ].y )
			top = screen_points[ i ].y;
		if ( right < screen_points[ i ].x )
			right = screen_points[ i ].x;
		if ( bottom < screen_points[ i ].y )
			bottom = screen_points[ i ].y;
	}

	return std::make_pair( ImVec4( floor( left ), floor( top ), floor( right ), floor( bottom ) ), on_screen );
}

void render_visuals( sdk::c_tf_player* entity )
{
	CONFIG( visuals_player_box, bool );
	CONFIG( visuals_player_box_color, ImVec4 );
	CONFIG( visuals_player_box_outline_color, ImVec4 );
	CONFIG( visuals_player_name, bool );
	CONFIG( visuals_player_name_color, ImVec4 );
	CONFIG( visuals_player_name_outline_color, ImVec4 );
	CONFIG( visuals_player_health_bar, bool );
	CONFIG( visuals_player_health_bar_color, ImVec4 );
	CONFIG( visuals_player_health_bar_outline_color, ImVec4 );
	CONFIG( visuals_player_health_bar_thickness, int );
	CONFIG( visuals_player_health_text, bool );
	CONFIG( visuals_player_health_text_color, ImVec4 );
	CONFIG( visuals_player_health_text_outline_color, ImVec4 );
	CONFIG( visuals_player_health_text_minimum, int );
	CONFIG( visuals_player_class, bool );
	CONFIG( visuals_player_class_color, ImVec4 );
	CONFIG( visuals_player_class_outline_color, ImVec4 );

	const auto [ bb, on_screen ] = bounding_box( entity );

	if ( !on_screen )
		return;

	const auto draw = ImGui::GetBackgroundDrawList( );

	std::vector< std::pair< std::string, std::pair< ImColor, ImColor > > > text;

	if ( *visuals_player_box ) {
		draw->AddRect( ImVec2( bb.x - 1, bb.y - 1 ), ImVec2( bb.z + 1, bb.w + 1 ), ImColor( *visuals_player_box_outline_color ) );
		draw->AddRect( ImVec2( bb.x + 1, bb.y + 1 ), ImVec2( bb.z - 1, bb.w - 1 ), ImColor( *visuals_player_box_outline_color ) );
		draw->AddRect( ImVec2( bb.x, bb.y ), ImVec2( bb.z, bb.w ), ImColor( *visuals_player_box_color ) );
	}

	if ( *visuals_player_name ) {
		const auto name_size = verdana_bd_11->CalcTextSizeA( 11.f, FLT_MAX, -1.f, entity->name( ).c_str( ) );

		draw->AddText( verdana_bd_11, 11.f, ImVec2( ( bb.x + bb.z ) / 2.f - name_size.x / 2.f + 1, bb.y - name_size.y - 1 ),
		               ImColor( *visuals_player_name_outline_color ), entity->name( ).c_str( ) );
		draw->AddText( verdana_bd_11, 11.f, ImVec2( ( bb.x + bb.z ) / 2.f - name_size.x / 2.f, bb.y - name_size.y - 2 ),
		               ImColor( *visuals_player_name_color ), entity->name( ).c_str( ) );
	}

	if ( *visuals_player_health_bar ) {
		const auto health     = static_cast< float >( entity->health( ) );
		const auto max_health = static_cast< float >( entity->max_health( ) );

		const auto health_size  = ( bb.w - bb.y ) * ( health / max_health );
		const auto health_color = ImColor( *visuals_player_health_bar_color );

		float h{ }, s{ }, v{ };
		float r{ }, g{ }, b{ };

		ImGui::ColorConvertRGBtoHSV( health_color.Value.x, health_color.Value.y, health_color.Value.z, h, s, v );

		h -= 0.3f * ( -( health / max_health ) + 1.f );

		ImGui::ColorConvertHSVtoRGB( h, s, v, r, g, b );

		draw->AddRectFilled( ImVec2( bb.x - ( 4 + *visuals_player_health_bar_thickness ), bb.y - 1 ), ImVec2( bb.x - 2, bb.w + 1 ),
		                     ImColor( *visuals_player_health_bar_outline_color ) );
		draw->AddRectFilled( ImVec2( bb.x - ( 3 + *visuals_player_health_bar_thickness ), bb.w - health_size ), ImVec2( bb.x - 3, bb.w ),
		                     ImColor( r, g, b ) );
	}

	if ( *visuals_player_health_text ) {
		const auto health     = static_cast< float >( entity->health( ) );
		const auto max_health = static_cast< float >( entity->max_health( ) );

		if ( *visuals_player_health_text_minimum >= health - max_health ) {
			const auto health_size  = ( bb.w - bb.y ) * ( health / max_health );
			const auto health_color = ImColor( *visuals_player_health_text_color );
			float h{ }, s{ }, v{ };
			float r{ }, g{ }, b{ };

			ImGui::ColorConvertRGBtoHSV( health_color.Value.x, health_color.Value.y, health_color.Value.z, h, s, v );

			h -= 0.3f * ( -( health / max_health ) + 1.f );

			ImGui::ColorConvertHSVtoRGB( h, s, v, r, g, b );

			const auto text_size = verdana_bd_11->CalcTextSizeA( 11.f, FLT_MAX, -1.f, std::to_string( static_cast< int >( health ) ).c_str( ) );

			if ( *visuals_player_health_bar ) {
				draw->AddText(
					verdana_bd_11, 11.f,
					ImVec2( bb.x - ( 3 + *visuals_player_health_bar_thickness ) - text_size.x / 2.f + 1, bb.w - health_size - text_size.y / 2.f + 1 ),
					ImColor( *visuals_player_health_text_outline_color ), std::to_string( static_cast< int >( health ) ).c_str( ) );

				draw->AddText(
					verdana_bd_11, 11.f,
					ImVec2( bb.x - ( 3 + *visuals_player_health_bar_thickness ) - text_size.x / 2.f - 1, bb.w - health_size - text_size.y / 2.f + 1 ),
					ImColor( *visuals_player_health_text_outline_color ), std::to_string( static_cast< int >( health ) ).c_str( ) );

				draw->AddText(
					verdana_bd_11, 11.f,
					ImVec2( bb.x - ( 3 + *visuals_player_health_bar_thickness ) - text_size.x / 2.f + 1, bb.w - health_size - text_size.y / 2.f - 1 ),
					ImColor( *visuals_player_health_text_outline_color ), std::to_string( static_cast< int >( health ) ).c_str( ) );

				draw->AddText(
					verdana_bd_11, 11.f,
					ImVec2( bb.x - ( 3 + *visuals_player_health_bar_thickness ) - text_size.x / 2.f - 1, bb.w - health_size - text_size.y / 2.f - 1 ),
					ImColor( *visuals_player_health_text_outline_color ), std::to_string( static_cast< int >( health ) ).c_str( ) );

				draw->AddText(
					verdana_bd_11, 11.f,
					ImVec2( bb.x - ( 3 + *visuals_player_health_bar_thickness ) - text_size.x / 2.f, bb.w - health_size - text_size.y / 2.f ),
					ImColor( r, g, b ), std::to_string( static_cast< int >( health ) ).c_str( ) );
			}
		}
	}

	if ( *visuals_player_class ) {
		const auto class_name = entity->class_name( );

		text.push_back(
			std::make_pair( class_name, std::make_pair( ImColor( *visuals_player_class_outline_color ), ImColor( *visuals_player_class_color ) ) ) );
	}

	if ( true ) {
		draw_weapon_icon( entity, { bb.x, bb.w }, { 60, 20 } );
	}

	auto offset = 0.f;

	for ( const auto& indicator : text ) {
		const auto text_size = verdana_bd_11->CalcTextSizeA( 11.f, FLT_MAX, -1.f, indicator.first.c_str( ) );

		draw->AddText( verdana_bd_11, 11.f, ImVec2( bb.z + 2, bb.y + offset + 1 ), indicator.second.first, indicator.first.c_str( ) );
		draw->AddText( verdana_bd_11, 11.f, ImVec2( bb.z + 2, bb.y + offset ), indicator.second.second, indicator.first.c_str( ) );

		offset += text_size.y + 1;
	}
}

void visuals::run( )
{
	CONFIG( visuals_player_enabled, bool );
	CONFIG( visuals_player_teams, int );

	if ( !g_local )
		return;

	if ( *visuals_player_enabled ) {
		if ( *visuals_player_teams & 1 << 0 ) {
			for ( const auto entity : g_entity_list->team ) {
				if ( !entity )
					continue;

				render_visuals( entity );
			}
		}

		if ( *visuals_player_teams & 1 << 1 ) {
			for ( const auto entity : g_entity_list->enemy ) {
				if ( !entity )
					continue;

				render_visuals( entity );
			}
		}
	}
}
