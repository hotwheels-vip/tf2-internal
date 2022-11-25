//
// Created by liga on 11/11/2022.
//

#include "menu.hpp"

void menu::run( )
{
	CONFIG( aimbot_mouse_enabled, bool );
	CONFIG( aimbot_mouse_fov, float );
	CONFIG( aimbot_mouse_smoothing, float );
	CONFIG( aimbot_mouse_hitbox_head, bool );
	CONFIG( aimbot_mouse_hitbox_chest, bool );
	CONFIG( aimbot_mouse_hitbox_stomach, bool );
	CONFIG( aimbot_mouse_hitbox_arms, bool );
	CONFIG( aimbot_mouse_hitbox_legs, bool );
	CONFIG( aimbot_mouse_curve_linear, bool );
	CONFIG( aimbot_mouse_curve_quadratic, bool );
	CONFIG( aimbot_mouse_curve_cubic, bool );
	CONFIG( aimbot_mouse_curve_quartic, bool );
	CONFIG( aimbot_mouse_curve_quintic, bool );

	CONFIG( aimbot_silent_enabled, bool );
	CONFIG( aimbot_silent_fov, float );
	CONFIG( aimbot_silent_hitbox_head, bool );
	CONFIG( aimbot_silent_hitbox_chest, bool );
	CONFIG( aimbot_silent_hitbox_stomach, bool );
	CONFIG( aimbot_silent_hitbox_arms, bool );
	CONFIG( aimbot_silent_hitbox_legs, bool );

	CONFIG( aimbot_projectile_enabled, bool );
	CONFIG( aimbot_projectile_invisible, bool );
	CONFIG( aimbot_projectile_feet, bool );
	CONFIG( aimbot_projectile_steps, int );

	CONFIG( menu_animation_speed, float );
	CONFIG( menu_indicator_transparency, float );
	CONFIG( menu_disabled_inputs_mouse, bool );
	CONFIG( menu_disabled_inputs_keyboard, bool );

	//	ImGui::ShowDemoWindow( );

	ImGui::SetNextWindowSize( ImVec2( 600, 400 ) );

	if ( ImGui::Begin( "hotwheels.vip", nullptr, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse ) ) {
		if ( ImGui::BeginTabBar( "TabBar", ImGuiTabBarFlags_Reorderable ) ) {
			if ( ImGui::BeginTabItem( "Aimbot" ) ) {
				if ( ImGui::BeginChild( "Aimbot Child", ImVec2( 0, 0 ), false ) ) {
					auto id = ImGui::GetID( "AimbotDockSpace" );

					static ImGuiID left{ };
					static ImGuiID right{ };
					static ImGuiID right_top{ };
					static ImGuiID right_bottom{ };

					if ( ImGui::DockBuilderGetNode( id ) == nullptr ) {
						ImGui::DockBuilderRemoveNode( id );
						ImGui::DockBuilderAddNode( id, ImGuiDockNodeFlags_DockSpace );
						ImGui::DockBuilderSetNodeSize( id, ImGui::GetContentRegionAvail( ) );

						ImGui::DockBuilderSplitNode( id, ImGuiDir_Left, 0.5f, &left, &right );
						ImGui::DockBuilderSplitNode( right, ImGuiDir_Up, 0.5f, &right_top, &right_bottom );

						ImGui::DockBuilderDockWindow( "Aimbot Mouse", left );
						ImGui::DockBuilderDockWindow( "Aimbot Silent", right_top );
						ImGui::DockBuilderDockWindow( "Aimbot Projectile", right_bottom );

						ImGui::DockBuilderFinish( id );
					}

					ImGui::DockSpace( id, ImVec2( 0, 0 ), ImGuiDockNodeFlags_NoResize );

					ImGui::SetNextWindowSize( ImVec2( 297, 0 ) );

					ImGui::Begin( "Aimbot Mouse", nullptr );
					{
						ImGui::Checkbox( "Enabled ##Mouse Enabled", aimbot_mouse_enabled );
						ImGui::Spacing( );
						ImGui::Text( "Mouse FOV" );
						ImGui::SliderFloat( "##Mouse FOV", aimbot_mouse_fov, 0.f, 180.f, "%.1f" );
						ImGui::Text( "Mouse Smoothing" );
						ImGui::SameLine( );
						ImGui::TextDisabled( "(?)" );
						if ( ImGui::IsItemHovered( ImGuiHoveredFlags_DelayShort ) ) {
							ImGui::BeginTooltip( );
							ImGui::PushTextWrapPos( ImGui::GetFontSize( ) * 35.0f );
							ImGui::TextUnformatted( "Multiplier to the curve." );
							ImGui::PopTextWrapPos( );
							ImGui::EndTooltip( );
						}
						ImGui::SliderFloat( "##Mouse Smoothing", aimbot_mouse_smoothing, 0.f, 1.f, "%.1f" );
						ImGui::Text( "Mouse Hitboxes" );

						auto preview_text = std::string( ) + ( *aimbot_mouse_hitbox_head ? "Head, " : "" ) +
						                    ( *aimbot_mouse_hitbox_chest ? "Chest, " : "" ) + ( *aimbot_mouse_hitbox_stomach ? "Stomach, " : "" ) +
						                    ( *aimbot_mouse_hitbox_legs ? "Legs, " : "" ) + ( *aimbot_mouse_hitbox_arms ? "Arms" : "" );

						if ( ImGui::BeginCombo( "##Mouse Hitboxes", preview_text.c_str( ) ) ) {
							ImGui::Selectable( "Head", aimbot_mouse_hitbox_head, ImGuiSelectableFlags_DontClosePopups );
							ImGui::Selectable( "Chest", aimbot_mouse_hitbox_chest, ImGuiSelectableFlags_DontClosePopups );
							ImGui::Selectable( "Stomach", aimbot_mouse_hitbox_stomach, ImGuiSelectableFlags_DontClosePopups );
							ImGui::Selectable( "Legs", aimbot_mouse_hitbox_legs, ImGuiSelectableFlags_DontClosePopups );
							ImGui::Selectable( "Arms", aimbot_mouse_hitbox_arms, ImGuiSelectableFlags_DontClosePopups );

							ImGui::EndCombo( );
						}

						ImGui::Text( "Mouse Curve" );

						preview_text = std::string( ) + ( *aimbot_mouse_curve_linear ? "Linear" : "" ) +
						               ( *aimbot_mouse_curve_quadratic ? "Quadratic" : "" ) + ( *aimbot_mouse_curve_cubic ? "Cubic" : "" ) +
						               ( *aimbot_mouse_curve_quartic ? "Quartic " : "" ) + ( *aimbot_mouse_curve_quintic ? "Quintic" : "" );

						if ( ImGui::BeginCombo( "##Mouse Curve", preview_text.c_str( ) ) ) {
							if ( ImGui::Selectable( "Linear", aimbot_mouse_curve_linear ) ) {
								*aimbot_mouse_curve_quadratic = false;
								*aimbot_mouse_curve_cubic     = false;
								*aimbot_mouse_curve_quartic   = false;
								*aimbot_mouse_curve_quintic   = false;
							}
							if ( ImGui::Selectable( "Quadratic", aimbot_mouse_curve_quadratic ) ) {
								*aimbot_mouse_curve_linear  = false;
								*aimbot_mouse_curve_cubic   = false;
								*aimbot_mouse_curve_quartic = false;
								*aimbot_mouse_curve_quintic = false;
							}
							if ( ImGui::Selectable( "Cubic", aimbot_mouse_curve_cubic ) ) {
								*aimbot_mouse_curve_quadratic = false;
								*aimbot_mouse_curve_linear    = false;
								*aimbot_mouse_curve_quartic   = false;
								*aimbot_mouse_curve_quintic   = false;
							}
							if ( ImGui::Selectable( "Quartic", aimbot_mouse_curve_quartic ) ) {
								*aimbot_mouse_curve_quadratic = false;
								*aimbot_mouse_curve_cubic     = false;
								*aimbot_mouse_curve_linear    = false;
								*aimbot_mouse_curve_quintic   = false;
							}
							if ( ImGui::Selectable( "Quintic", aimbot_mouse_curve_quintic ) ) {
								*aimbot_mouse_curve_quadratic = false;
								*aimbot_mouse_curve_cubic     = false;
								*aimbot_mouse_curve_quartic   = false;
								*aimbot_mouse_curve_linear    = false;
							}

							ImGui::EndCombo( );
						}

						float values[ 50 ]{ };

						for ( int i = 0; i < 50; i++ ) {
							if ( aimbot_mouse_curve_linear )
								values[ i ] = ( -( LinearInterpolation( i / 50.f ) ) + 1.f ) * *aimbot_mouse_smoothing;

							if ( *aimbot_mouse_curve_quadratic )
								values[ i ] = ( -( QuadraticEaseIn( i / 50.f ) ) + 1.f ) * *aimbot_mouse_smoothing;

							if ( *aimbot_mouse_curve_cubic )
								values[ i ] = ( -( CubicEaseIn( i / 50.f ) ) + 1.f ) * *aimbot_mouse_smoothing;

							if ( *aimbot_mouse_curve_quartic )
								values[ i ] = ( -( QuarticEaseIn( i / 50.f ) ) + 1.f ) * *aimbot_mouse_smoothing;

							if ( *aimbot_mouse_curve_quintic )
								values[ i ] = ( -( QuinticEaseIn( i / 50.f ) ) + 1.f ) * *aimbot_mouse_smoothing;
						}

						ImGui::PlotLines( "##Graph", values, 50, 0, 0, 0, 1 );
					}
					ImGui::End( );

					ImGui::SetNextWindowSize( ImVec2( 297, 0 ) );

					ImGui::Begin( "Aimbot Silent", nullptr );
					{
						ImGui::Checkbox( "Enabled ##Silent Enabled", aimbot_silent_enabled );
						ImGui::Text( "Silent FOV" );
						ImGui::SliderFloat( "##Silent FOV", aimbot_silent_fov, 0.f, 180.f, "%.1f" );

						ImGui::Text( "Silent Hitboxes" );

						auto preview_text = std::string( ) + ( *aimbot_silent_hitbox_head ? "Head, " : "" ) +
						                    ( *aimbot_silent_hitbox_chest ? "Chest, " : "" ) + ( *aimbot_silent_hitbox_stomach ? "Stomach, " : "" ) +
						                    ( *aimbot_silent_hitbox_legs ? "Legs, " : "" ) + ( *aimbot_silent_hitbox_arms ? "Arms" : "" );

						if ( ImGui::BeginCombo( "##Silent Hitboxes", preview_text.c_str( ) ) ) {
							ImGui::Selectable( "Head", aimbot_silent_hitbox_head, ImGuiSelectableFlags_DontClosePopups );
							ImGui::Selectable( "Chest", aimbot_silent_hitbox_chest, ImGuiSelectableFlags_DontClosePopups );
							ImGui::Selectable( "Stomach", aimbot_silent_hitbox_stomach, ImGuiSelectableFlags_DontClosePopups );
							ImGui::Selectable( "Legs", aimbot_silent_hitbox_legs, ImGuiSelectableFlags_DontClosePopups );
							ImGui::Selectable( "Arms", aimbot_silent_hitbox_arms, ImGuiSelectableFlags_DontClosePopups );

							ImGui::EndCombo( );
						}
					}
					ImGui::End( );

					ImGui::SetNextWindowSize( ImVec2( 297, 0 ) );
					ImGui::Begin( "Aimbot Projectile", nullptr );
					{
						ImGui::Checkbox( "Enabled ##Projectile Enabled", aimbot_projectile_enabled );
						ImGui::Checkbox( "Projectile Invisible", aimbot_projectile_invisible );
						ImGui::SameLine( );
						ImGui::TextDisabled( "(?)" );
						if ( ImGui::IsItemHovered( ImGuiHoveredFlags_DelayShort ) ) {
							ImGui::BeginTooltip( );
							ImGui::PushTextWrapPos( ImGui::GetFontSize( ) * 35.0f );
							ImGui::TextUnformatted(
								"Makes your projectile aimbot invisible to spectators when used with silent aim. Often called p-silent." );
							ImGui::PopTextWrapPos( );
							ImGui::EndTooltip( );
						}
						ImGui::Checkbox( "Projectile Feet", aimbot_projectile_feet );
						ImGui::SameLine( );
						ImGui::TextDisabled( "(?)" );
						if ( ImGui::IsItemHovered( ImGuiHoveredFlags_DelayShort ) ) {
							ImGui::BeginTooltip( );
							ImGui::PushTextWrapPos( ImGui::GetFontSize( ) * 35.0f );
							ImGui::TextUnformatted( "Targets feet to ideally send a person higher in the air." );
							ImGui::TextColored( ImVec4( 1.f, 0.f, 0.f, 1.f ), "WARNING: Less chance of hitting projectiles!" );
							ImGui::PopTextWrapPos( );
							ImGui::EndTooltip( );
						}
						ImGui::Text( "Projectile Steps" );
						ImGui::SameLine( );
						ImGui::TextDisabled( "(?)" );
						if ( ImGui::IsItemHovered( ImGuiHoveredFlags_DelayShort ) ) {
							ImGui::BeginTooltip( );
							ImGui::PushTextWrapPos( ImGui::GetFontSize( ) * 35.0f );
							ImGui::TextUnformatted( "Steps the aimbot will take to find the best target." );
							ImGui::TextColored( ImVec4( 1.f, 0.f, 0.f, 1.f ), "WARNING: Higher values will cause more lag!" );
							ImGui::PopTextWrapPos( );
							ImGui::EndTooltip( );
						}
						ImGui::SliderInt( "##Projectile Steps", aimbot_projectile_steps, 1, 50 );
					}
					ImGui::End( );

					ImGui::EndChild( );
				}

				ImGui::EndTabItem( );
			}

			if ( ImGui::BeginTabItem( "Config", nullptr ) ) {
				if ( ImGui::BeginChild( "Config Child", ImVec2( 0, 0 ), false ) ) {
					auto id = ImGui::GetID( "ConfigDockSpace" );

					static ImGuiID left{ };
					static ImGuiID right{ };

					if ( ImGui::DockBuilderGetNode( id ) == nullptr ) {
						ImGui::DockBuilderRemoveNode( id );
						ImGui::DockBuilderAddNode( id, ImGuiDockNodeFlags_DockSpace );
						ImGui::DockBuilderSetNodeSize( id, ImGui::GetWindowSize( ) );

						ImGui::DockBuilderSplitNode( id, ImGuiDir_Left, 0.5f, &left, &right );

						ImGui::DockBuilderDockWindow( "Menu Settings", left );
						ImGui::DockBuilderDockWindow( "Cheat Settings", right );

						ImGui::DockBuilderFinish( id );
					}

					ImGui::DockSpace( id, ImVec2( 0, 0 ), ImGuiDockNodeFlags_NoResize );

					ImGui::SetNextWindowSize( ImVec2( 297, 0 ) );

					ImGui::Begin( "Menu Settings" );
					{
						bool open = ImGui::TreeNode( "Menu Colors" );

						ImGui::SameLine( );
						ImGui::TextDisabled( "(?)" );
						if ( ImGui::IsItemHovered( ImGuiHoveredFlags_DelayShort ) ) {
							ImGui::BeginTooltip( );
							ImGui::PushTextWrapPos( ImGui::GetFontSize( ) * 35.0f );
							ImGui::TextUnformatted( "Only saves to themes" );
							ImGui::PopTextWrapPos( );
							ImGui::EndTooltip( );
						}

						if ( open ) {
							for ( auto& color : ImGui::GetStyle( ).Colors ) {
								const char* name = ImGui::GetStyleColorName( ( int )( &color - ImGui::GetStyle( ).Colors ) );
								float color_array[ 4 ]{ color.x, color.y, color.z, color.w };

								ImGui::ColorEdit4( name, color_array, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview );

								color.x = color_array[ 0 ];
								color.y = color_array[ 1 ];
								color.z = color_array[ 2 ];
								color.w = color_array[ 3 ];
							}

							ImGui::TreePop( );
						}

						auto preview_text =
							std::string( ) + ( *menu_disabled_inputs_mouse ? "Mouse, " : "" ) + ( *menu_disabled_inputs_keyboard ? "Keyboard" : "" );

						ImGui::Spacing( );

						ImGui::Text( "Disabled Inputs" );
						if ( ImGui::BeginCombo( "##Menu Disabled Inputs", preview_text.c_str( ) ) ) {
							ImGui::Selectable( "Mouse", menu_disabled_inputs_mouse, ImGuiSelectableFlags_DontClosePopups );
							ImGui::Selectable( "Keyboard", menu_disabled_inputs_keyboard, ImGuiSelectableFlags_DontClosePopups );

							ImGui::EndCombo( );
						}

						ImGui::Spacing( );

						ImGui::Text( "Animation Speed" );
						ImGui::SliderFloat( "##Menu Animation Speed", menu_animation_speed, 0.1f, 2.0f, "%.1f" );
						ImGui::Text( "Indicator Transparency" );
						ImGui::SliderFloat( "##Menu Indicator Transparency", menu_indicator_transparency, 0.1f, 1.f, "%.1f" );

						ImGui::End( );
					}

					ImGui::SetNextWindowSize( ImVec2( 297, 0 ) );

					ImGui::Begin( "Cheat Settings" );
					{
						static std::string last_config{ };

						ImGui::Text( "Config List" );
						ImGui::SameLine( );
						ImGui::TextDisabled( "(?)" );
						if ( ImGui::IsItemHovered( ImGuiHoveredFlags_DelayShort ) ) {
							ImGui::BeginTooltip( );
							ImGui::PushTextWrapPos( ImGui::GetFontSize( ) * 35.0f );
							ImGui::TextUnformatted( "Right click on the config list / config for actions" );
							ImGui::PopTextWrapPos( );
							ImGui::EndTooltip( );
						}

						if ( ImGui::BeginListBox( "##Configs", ImVec2( 279, 0 ) ) ) {
							if ( ImGui::BeginPopupContextWindow( "##Configs Context" ) ) {
								static char config_name[ 128 ]{ };

								ImGui::PushItemWidth( 272 );
								ImGui::InputText( "##Config Name", config_name, sizeof( config_name ) );
								ImGui::PopItemWidth( );

								if ( ImGui::Button( "Create", ImVec2( 272, 0 ) ) ) {
									if ( !std::filesystem::exists( fmt::format( "C:\\Hotwheels\\Configs\\{}.hw", config_name ) ) ) {
										g_config->save( fmt::format( "C:\\Hotwheels\\Configs\\{}.hw", config_name ) );
										ImGui::CloseCurrentPopup( );
									}
								}

								ImGui::EndPopup( );
							}

							for ( auto entry : std::filesystem::directory_iterator( "C:\\Hotwheels\\Configs" ) ) {
								if ( entry.path( ).extension( ) != ".hw" )
									continue;

								std::string file_name{ entry.path( ).filename( ).string( ) };
								file_name.erase( file_name.end( ) - 3, file_name.end( ) );

								bool selected = last_config.contains( file_name.c_str( ) );

								if ( ImGui::Selectable( file_name.c_str( ), selected ) ) {
									last_config = file_name;
								}

								if ( ImGui::BeginPopupContextItem( fmt::format( "##Config Context {}", file_name ).c_str( ) ) ) {
									if ( ImGui::Button( "Delete" ) ) {
										std::filesystem::remove( entry.path( ).string( ) );

										ImGui::CloseCurrentPopup( );
									}

									ImGui::EndPopup( );
								}
							}
							ImGui::EndListBox( );
						}

						auto config_name_short = last_config;

						if ( config_name_short.length( ) > 8 ) {
							config_name_short.erase( 8, config_name_short.length( ) - 8 );
							config_name_short += "...";
						}

						if ( ImGui::Button( fmt::format( "Load {}", config_name_short ).c_str( ), ImVec2( 135, 0 ) ) ) {
							g_config->load( fmt::format( "C:\\Hotwheels\\Configs\\{}.hw", last_config ) );
						}

						ImGui::SameLine( );

						if ( ImGui::Button( fmt::format( "Save {}", config_name_short ).c_str( ), ImVec2( 136, 0 ) ) ) {
							g_config->save( fmt::format( "C:\\Hotwheels\\Configs\\{}.hw", last_config ) );
						}

						static std::string last_theme{ };

						ImGui::Text( "Theme List" );
						ImGui::SameLine( );
						ImGui::TextDisabled( "(?)" );
						if ( ImGui::IsItemHovered( ImGuiHoveredFlags_DelayShort ) ) {
							ImGui::BeginTooltip( );
							ImGui::PushTextWrapPos( ImGui::GetFontSize( ) * 35.0f );
							ImGui::TextUnformatted( "Right click on the theme list / config for actions" );
							ImGui::PopTextWrapPos( );
							ImGui::EndTooltip( );
						}

						if ( ImGui::BeginListBox( "##Themes", ImVec2( 279, 0 ) ) ) {
							if ( ImGui::BeginPopupContextWindow( "##Themes Context" ) ) {
								static char theme_name[ 128 ]{ };

								ImGui::PushItemWidth( 272 );
								ImGui::InputText( "##Theme Name", theme_name, sizeof( theme_name ) );
								ImGui::PopItemWidth( );

								if ( ImGui::Button( "Create", ImVec2( 272, 0 ) ) ) {
									if ( !std::filesystem::exists( fmt::format( "C:\\Hotwheels\\Themes\\{}.hw", theme_name ) ) ) {
										g_themes->save( fmt::format( "C:\\Hotwheels\\Themes\\{}.hw", theme_name ) );
										ImGui::CloseCurrentPopup( );
									}
								}

								ImGui::EndPopup( );
							}

							for ( auto entry : std::filesystem::directory_iterator( "C:\\Hotwheels\\Themes" ) ) {
								if ( entry.path( ).extension( ) != ".hw" )
									continue;

								std::string file_name{ entry.path( ).filename( ).string( ) };
								file_name.erase( file_name.end( ) - 3, file_name.end( ) );

								bool selected = last_theme.contains( file_name.c_str( ) );

								if ( ImGui::Selectable( file_name.c_str( ), selected ) ) {
									last_theme = file_name;
								}

								if ( ImGui::BeginPopupContextItem( fmt::format( "##Theme Context {}", file_name ).c_str( ) ) ) {
									if ( ImGui::Button( "Delete" ) ) {
										std::filesystem::remove( entry.path( ).string( ) );

										ImGui::CloseCurrentPopup( );
									}

									ImGui::EndPopup( );
								}
							}
							ImGui::EndListBox( );
						}

						auto theme_name_short = last_theme;

						if ( theme_name_short.length( ) > 8 ) {
							theme_name_short.erase( 8, theme_name_short.length( ) - 8 );
							theme_name_short += "...";
						}

						if ( ImGui::Button( fmt::format( "Load {}##theme", theme_name_short ).c_str( ), ImVec2( 135, 0 ) ) ) {
							g_themes->load( fmt::format( "C:\\Hotwheels\\Themes\\{}.hw", last_theme ) );
						}

						ImGui::SameLine( );

						if ( ImGui::Button( fmt::format( "Save {}##theme", theme_name_short ).c_str( ), ImVec2( 136, 0 ) ) ) {
							g_themes->save( fmt::format( "C:\\Hotwheels\\Themes\\{}.hw", last_theme ) );
						}

						ImGui::End( );
					}

					ImGui::EndChild( );
				}

				ImGui::EndTabItem( );
			}

			ImGui::EndTabBar( );
		}

		ImGui::End( );
	}
}
