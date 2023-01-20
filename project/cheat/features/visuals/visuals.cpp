#include "visuals.hpp"
#include <imgui/imgui.h>

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

	const auto [ bb, on_screen ] = bounding_box( entity );

	if ( !on_screen )
		return;

	const auto draw = ImGui::GetBackgroundDrawList( );

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
		const float health      = entity->health( );
		const float max_health  = entity->max_health( );
		const auto health_size  = ( bb.w - bb.y ) * ( health / max_health );
		const auto health_color = ImColor( *visuals_player_health_bar_color );
		float h{ }, s{ }, v{ };
		float r{ }, g{ }, b{ };

		ImGui::ColorConvertRGBtoHSV( health_color.Value.x, health_color.Value.y, health_color.Value.z, h, s, v );

		h -= 0.3f * ( -( health / max_health ) + 1.f );

		ImGui::ColorConvertHSVtoRGB( h, s, v, r, g, b );

		draw->AddRectFilled( ImVec2( bb.x - 6, bb.y - 1 ), ImVec2( bb.x - 2, bb.w + 1 ), ImColor( *visuals_player_health_bar_outline_color ) );
		draw->AddRectFilled( ImVec2( bb.x - 5, bb.w - health_size ), ImVec2( bb.x - 3, bb.w ), ImColor( r, g, b ) );
	}
}

void visuals::run( )
{
	CONFIG( visuals_player_enabled, bool );
	CONFIG( visuals_player_teams, int );

	if ( !g_entity_list->local )
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
