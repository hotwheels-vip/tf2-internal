//
// Created by liga on 11/11/2022.
//

#include "menu.hpp"

void menu::run( )
{
	CONFIG( aimbot_mouse_enabled, bool );
	CONFIG( aimbot_mouse_fov, float );
	CONFIG( aimbot_mouse_smoothing, float );
	CONFIG( aimbot_mouse_hitboxes, int );
	CONFIG( aimbot_mouse_curve_a, ImVec2 );
	CONFIG( aimbot_mouse_curve_b, ImVec2 );

	CONFIG( aimbot_silent_enabled, bool );
	CONFIG( aimbot_silent_fov, float );
	CONFIG( aimbot_silent_hitboxes, int );

	CONFIG( aimbot_projectile_enabled, bool );
	CONFIG( aimbot_projectile_invisible, bool );
	CONFIG( aimbot_projectile_feet, bool );
	CONFIG( aimbot_projectile_steps, int );

	CONFIG( menu_disabled_inputs_mouse, bool );
	CONFIG( menu_disabled_inputs_keyboard, bool );

	//	ImGui::ShowDemoWindow( );

	ImGuiStyle& style = ImGui::GetStyle( );

	/* loader ui*/
	{
		constexpr auto background_height = 25.f;

		ImGui::SetNextWindowSize( ImVec2( 588.f, 559.f ), ImGuiCond_::ImGuiCond_Always );

		ImGui::Begin( "hotwheels-ui", 0,
		              ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse |
		                  ImGuiWindowFlags_::ImGuiWindowFlags_NoResize );
		{
			const auto window = ImGui::GetCurrentWindow( );

			const auto draw_list = window->DrawList;

			const auto size     = window->Size;
			const auto position = window->Pos;

			static int tab_number = 0;

			/* render title */
			[ & ]( ) {
				/* render background */
				ImGui::PushClipRect( ImVec2( position.x, position.y ), ImVec2( position.x + size.x, position.y + background_height ), false );
				draw_list->AddRectFilled( ImVec2( position.x, position.y ), ImVec2( position.x + size.x, position.y + background_height ),
				                          ImColor( 25 / 255.f, 25 / 255.f, 25 / 255.f ), style.WindowRounding, ImDrawFlags_RoundCornersTop );
				ImGui::PopClipRect( );

				/* render gradient */
				RenderFadedGradientLine( draw_list, ImVec2( position.x, position.y + background_height - 1.f ), ImVec2( size.x, 1.f ),
				                         ImColor( Accent[ 0 ], Accent[ 1 ], Accent[ 2 ] ) );

				constexpr const char* title_text = "hotwheels";
				const auto title_text_size       = verdana_bd_11->CalcTextSizeA( verdana_bd_11->FontSize, FLT_MAX, 0.f, title_text );

				constexpr const char* vip_title_text = ".vip";
				const auto vip_title_text_size       = verdana_bd_11->CalcTextSizeA( verdana_bd_11->FontSize, FLT_MAX, 0.f, vip_title_text );

				draw_list->AddText( verdana_bd_11, verdana_bd_11->FontSize,
				                    ImVec2( position.x + ( ( size.x - title_text_size.x - vip_title_text_size.x ) / 2.f ),
				                            position.y + ( ( background_height - title_text_size.y ) / 2.f ) ),
				                    ImColor( 1.f, 1.f, 1.f ), title_text );

				draw_list->AddText( verdana_bd_11, verdana_bd_11->FontSize,
				                    ImVec2( position.x + ( ( size.x + title_text_size.x - vip_title_text_size.x ) / 2.f ),
				                            position.y + ( ( background_height - title_text_size.y ) / 2.f ) ),
				                    ImColor( Accent[ 0 ], Accent[ 1 ], Accent[ 2 ] ), vip_title_text );
			}( );

			/* render tabs */
			[ & ]( ) {
				/* render background */
				ImGui::PushClipRect( ImVec2( position.x, position.y + size.y - background_height ),
				                     ImVec2( position.x + size.x, position.y + size.y ), false );
				draw_list->AddRectFilled( ImVec2( position.x, position.y + size.y - background_height ),
				                          ImVec2( position.x + size.x, position.y + size.y ), ImColor( 25 / 255.f, 25 / 255.f, 25 / 255.f ),
				                          style.WindowRounding, ImDrawFlags_RoundCornersBottom );
				ImGui::PopClipRect( );

				/* render gradient */
				RenderFadedGradientLine( draw_list, ImVec2( position.x, position.y + size.y - background_height ), ImVec2( size.x, 1.f ),
				                         ImColor( Accent[ 0 ], Accent[ 1 ], Accent[ 2 ] ) );

				/* tab logic */
				std::vector< const char* > tab_names = { "aimbot", "visuals", "movement", "misc", "settings" };
				for ( int iterator = { }; iterator < tab_names.size( ); iterator++ ) {
					if ( !( iterator < tab_names.size( ) ) )
						break;

					const char* const tab_name = tab_names[ iterator ];

					const auto hashed_tab_name = ImHashStr( tab_name );

					const auto text_size = verdana_bd_11->CalcTextSizeA( verdana_bd_11->FontSize, FLT_MAX, 0.f, tab_name );

					const int tab_width    = ( size.x / static_cast< int >( tab_names.size( ) ) );
					const int tab_center_x = ( tab_width * iterator ) + ( tab_width / 2 );

					const auto text_position =
						ImVec2( tab_center_x - ( text_size.x / 2 ), ( size.y - ( background_height + text_size.y ) / 2.f ) - 1.f );

					const bool hovered = ImGui::IsMouseHoveringRect(
						ImVec2( position.x + text_position.x, position.y + text_position.y ),
						ImVec2( position.x + text_position.x + text_size.x, position.y + text_position.y + text_size.y ) );

					const bool selected = iterator == tab_number;

					auto hovered_text_animation =
						ImAnimationHelper( hashed_tab_name + ImHashStr( "hovered-text-animation" ), ImGui::GetIO( ).DeltaTime );
					hovered_text_animation.Update( 2.f, hovered ? 2.f : -2.f, 0.5f );

					auto selected_animation = ImAnimationHelper( hashed_tab_name + ImHashStr( "selected-animation" ), ImGui::GetIO( ).DeltaTime );
					selected_animation.Update( 2.f, selected ? 2.f : -2.f );

					draw_list->AddText( verdana_bd_11, verdana_bd_11->FontSize, ImVec2( position.x + text_position.x, position.y + text_position.y ),
					                    ImColor::Blend( ImColor( 1.f, 1.f, 1.f, hovered_text_animation.AnimationData->second ),
					                                    ImColor( Accent[ 0 ], Accent[ 1 ], Accent[ 2 ] ), selected_animation.AnimationData->second ),
					                    tab_name );

					if ( hovered && ImGui::IsMouseClicked( ImGuiMouseButton_Left ) )
						tab_number = iterator;
				}
			}( );

			/* set next working position for the elements */
			ImGui::SetCursorPosY( ImGui::GetCursorPosY( ) + 25.f );

			switch ( tab_number ) {
			// aimbart
			case 0: {
				if ( ImGui::BeginChild(
						 "mouse aimbot",
						 ImVec2( ImGui::GetContentRegionAvail( ).x / 2.f, ( ImGui::GetContentRegionAvail( ).y / 2.f ) - background_height - 20.f ),
						 true, 0, true ) ) {
					// err, head, chest, pelvis, limbs
					std::vector< bool > buffer_hitboxes = { ( bool )( *aimbot_mouse_hitboxes & 1 << sdk::hitbox_head ),
						                                    ( bool )( *aimbot_mouse_hitboxes & 1 << sdk::hitbox_chest ),
						                                    ( bool )( *aimbot_mouse_hitboxes & 1 << sdk::hitbox_pelvis ),
						                                    ( bool )( *aimbot_mouse_hitboxes & 1 << sdk::hitbox_right_thigh ) };

					ImGui::Checkbox( "mouse enabled", aimbot_mouse_enabled );
					ImGui::SliderFloat( "mouse fov", aimbot_mouse_fov, 0.f, 180.f, "%.1f" );
					ImGui::SliderFloat( "mouse smoothing", aimbot_mouse_smoothing, 0.f, 1.f, "%.2f" );
					ImGui::MultiCombo( "mouse hitboxes", buffer_hitboxes, { "head", "chest", "pelvis", "limbs" }, buffer_hitboxes.size( ) );

					if ( buffer_hitboxes[ 0 ] ) {
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_head;
					} else {
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_head );
					}
					if ( buffer_hitboxes[ 1 ] ) {
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_lower_chest;
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_chest;
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_upper_chest;
					} else {
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_lower_chest );
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_chest );
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_upper_chest );
					}
					if ( buffer_hitboxes[ 2 ] ) {
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_pelvis;
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_stomach;
					} else {
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_pelvis );
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_stomach );
					}
					if ( buffer_hitboxes[ 3 ] ) {
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_right_thigh;
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_left_thigh;
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_right_calf;
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_left_calf;
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_right_foot;
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_left_foot;
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_right_hand;
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_left_hand;
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_right_upper_arm;
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_right_forearm;
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_left_upper_arm;
						*aimbot_mouse_hitboxes |= 1 << sdk::hitbox_left_forearm;
					} else {
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_right_thigh );
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_left_thigh );
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_right_calf );
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_left_calf );
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_right_foot );
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_left_foot );
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_right_hand );
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_left_hand );
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_right_upper_arm );
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_right_forearm );
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_left_upper_arm );
						*aimbot_mouse_hitboxes &= ~( 1 << sdk::hitbox_left_forearm );
					}

					Points_t points = { *aimbot_mouse_curve_a, *aimbot_mouse_curve_b };

					if ( ImGui::CurveEditor( "mouse curve", &points, mouse_curve, 50 ) ) {
						*aimbot_mouse_curve_a = points.PointA;
						*aimbot_mouse_curve_b = points.PointB;
					}

					ImGui::EndChild( );
				}

				ImGui::SameLine( );
				ImGui::SetCursorPosY( ImGui::GetCursorPosY( ) - 20.f );

				if ( ImGui::BeginChild(
						 "silent aimbot",
						 ImVec2( ImGui::GetContentRegionAvail( ).x, ( ImGui::GetContentRegionAvail( ).y / 2.f ) - background_height - 20.f ), true, 0,
						 true ) ) {
					// err, head, chest, pelvis, limbs
					std::vector< bool > buffer_hitboxes = { ( bool )( *aimbot_silent_hitboxes & 1 << sdk::hitbox_head ),
						                                    ( bool )( *aimbot_silent_hitboxes & 1 << sdk::hitbox_chest ),
						                                    ( bool )( *aimbot_silent_hitboxes & 1 << sdk::hitbox_pelvis ),
						                                    ( bool )( *aimbot_silent_hitboxes & 1 << sdk::hitbox_right_thigh ) };

					ImGui::Checkbox( "silent enabled", aimbot_silent_enabled );
					ImGui::SliderFloat( "silent fov", aimbot_silent_fov, 0.f, 180.f, "%.1f" );
					ImGui::MultiCombo( "silent hitboxes", buffer_hitboxes, { "head", "chest", "pelvis", "limbs" }, buffer_hitboxes.size( ) );

					if ( buffer_hitboxes[ 0 ] ) {
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_head;
					} else {
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_head );
					}
					if ( buffer_hitboxes[ 1 ] ) {
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_lower_chest;
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_chest;
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_upper_chest;
					} else {
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_lower_chest );
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_chest );
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_upper_chest );
					}
					if ( buffer_hitboxes[ 2 ] ) {
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_pelvis;
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_stomach;
					} else {
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_pelvis );
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_stomach );
					}
					if ( buffer_hitboxes[ 3 ] ) {
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_right_thigh;
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_left_thigh;
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_right_calf;
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_left_calf;
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_right_foot;
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_left_foot;
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_right_hand;
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_left_hand;
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_right_upper_arm;
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_right_forearm;
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_left_upper_arm;
						*aimbot_silent_hitboxes |= 1 << sdk::hitbox_left_forearm;
					} else {
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_right_thigh );
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_left_thigh );
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_right_calf );
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_left_calf );
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_right_foot );
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_left_foot );
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_right_hand );
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_left_hand );
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_right_upper_arm );
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_right_forearm );
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_left_upper_arm );
						*aimbot_silent_hitboxes &= ~( 1 << sdk::hitbox_left_forearm );
					}

					ImGui::EndChild( );
				}

				if ( ImGui::BeginChild(
						 "projectile aimbot",
						 ImVec2( ImGui::GetContentRegionAvail( ).x / 2.f, ( ImGui::GetContentRegionAvail( ).y ) - background_height - 20.f ), true, 0,
						 true ) ) {
					ImGui::Checkbox( "projectile enabled", aimbot_projectile_enabled );
					ImGui::Checkbox( "projectile invisible", aimbot_projectile_invisible );
					ImGui::SliderInt( "projectile steps", aimbot_projectile_steps, 0, 100, "%d" );

					int buffer_target = *aimbot_projectile_feet ? 1 : 0;

					ImGui::Combo( "projectile target", &buffer_target, "best\0feet\0" );

					if ( buffer_target == 0 ) {
						*aimbot_projectile_feet = false;
					} else {
						*aimbot_projectile_feet = true;
					}

					ImGui::EndChild( );
				}

				ImGui::SameLine( );
				ImGui::SetCursorPosY( ImGui::GetCursorPosY( ) - 20.f );

				if ( ImGui::BeginChild( "other aimbot",
				                        ImVec2( ImGui::GetContentRegionAvail( ).x, ( ImGui::GetContentRegionAvail( ).y ) - background_height - 20.f ),
				                        true, 0, true ) ) {
					ImGui::EndChild( );
				}

				break;
			}
			}
		}
	}

	ImGui::End( );
}
