#include <lazy_importer.hh>
#include <mutex>
#include <xorstr.hh>
#include <fstream>
#include "../hooks.hh"
#include "../../settings.hh"
#include "../../features/esp.hh"
#include "../../features/skinchanger.hh"
#include "../../features/visuals.hh"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "../../imgui/particles.hh"
#include "../../interfaces/interfaces.hh"
#include "../../utilities/config/config.hh"

WNDPROC owndproc;

__int64 __stdcall hk_wndproc( const HWND hwnd, const UINT msg, const WPARAM param, const LPARAM lparam ) {
	if ( msg == WM_KEYUP && param == VK_INSERT )
		utils::global::menu_open = !utils::global::menu_open;

	return ImGui_ImplWin32_WndProcHandler( hwnd, msg, param, lparam ) && utils::global::menu_open ? 1 : LI_FN( CallWindowProcA ).cached( )( owndproc, hwnd, msg, param, lparam );
}

std::once_flag flag;

void __fastcall hooks::present( void* a1, void* a2 ) {
	static ID3D11Device* device = nullptr;
	static ID3D11DeviceContext* context = nullptr;
	static ID3D11RenderTargetView* render_target_view = nullptr;

	std::call_once( flag, [&]( ) {
		if ( SUCCEEDED( swapchain->GetDevice( __uuidof( device ), reinterpret_cast<void**>( &device ) ) ) )
			device->GetImmediateContext( &context );

		owndproc = reinterpret_cast<WNDPROC>( LI_FN( SetWindowLongPtrA ).cached( )(
			LI_FN( FindWindowW ).cached( )( _( L"Respawn001" ), nullptr ), GWLP_WNDPROC, reinterpret_cast<uintptr_t>( hk_wndproc ) ) );

		ID3D11Texture2D* render_texture = nullptr;
		if ( SUCCEEDED( swapchain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), reinterpret_cast<LPVOID*>( &render_texture )) ) ) {
			D3D11_RENDER_TARGET_VIEW_DESC desc = { };
			memset( &desc, 0, sizeof desc );
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

			device->CreateRenderTargetView( render_texture, &desc, &render_target_view );
			render_texture->Release( );
		}

		ImGui::CreateContext( );
		ImGui_ImplDX11_Init( LI_FN( FindWindowW ).cached( )( _( L"Respawn001" ), nullptr ), device, context );
	} );

	static void* saved_hwnd;
	if ( utils::global::menu_open ) {
		if ( !saved_hwnd )
			std::swap( saved_hwnd, interfaces::input_system->get_window( ) );
	} else {
		if ( saved_hwnd )
			std::swap( saved_hwnd, interfaces::input_system->get_window( ) );
	}

	ImGui::GetIO( ).MouseDrawCursor = utils::global::menu_open;

	context->OMSetRenderTargets( 1, &render_target_view, nullptr );
	const auto io = ImGui::GetIO( );

	ImGui_ImplDX11_NewFrame( );
	ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.0f );
	ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f } );
	ImGui::PushStyleColor( ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f } );
	ImGui::Begin( _( "" ), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs );
	{
		ImGui::SetWindowPos( ImVec2( 0, 0 ), ImGuiCond_Always );
		ImGui::SetWindowSize( ImVec2( io.DisplaySize.x, io.DisplaySize.y ), ImGuiCond_Always );

		esp::init( );
		visuals::init( );
	}
	ImGui::End( );
	ImGui::PopStyleColor( );
	ImGui::PopStyleVar( 2 );

	if ( utils::global::menu_open ) {
		ImGui::SetNextWindowSize( ImVec2( 350, 250 ), ImGuiCond_FirstUseEver );
		ImGui::Begin( _( "Vitasnella [apex]" ), nullptr,
		              ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse );
		{
			{
				if ( ImGui::BeginTabBar( _( "primary_interface_tabbar" ), ImGuiTabBarFlags_NoTooltip ) ) {
					if ( ImGui::BeginTabItem( _( "COMBAT" ) ) ) {
						ImGui::Checkbox( _( "Aimbot Enabled" ), &settings::aimbot_enabled );
						ImGui::SameLine( );
						ImGui::hotkey( _( "###aim_key" ), &settings::aimbot_bind );
						const char* silent_items[]{ "Off", "Client", "Server" };
						ImGui::Combo( _( "Silent Aim" ), &settings::aimbot_silent, silent_items, IM_ARRAYSIZE( silent_items ) );
						ImGui::Checkbox( _( "Visual Check" ), &settings::aimbot_visible );
						ImGui::Checkbox( _( "Autofire" ), &settings::aimbot_autofire );
						ImGui::Checkbox( _( "Ignore Downed" ), &settings::aimbot_downed );
						ImGui::SliderFloat( _( "Fov" ), &settings::aimbot_fov, 0.1f, 180.f, _( "%.1f" ) );
						ImGui::Checkbox( _( "Show Fov" ), &settings::misc_showfov );
						ImGui::SliderInt( _( "Smooth" ), &settings::aimbot_smooth, settings::aimbot_silent == 2 ? 0 : 1, 20 );

						ImGui::EndTabItem( );
					}

					if ( ImGui::BeginTabItem( _( "ANTIAIM" ) ) ) {
						static const char* antiaim_pitch_types[]{ "Down", "Up", "Lisp", "Zero", "Fake up" };
						static const char* antiaim_yaw_types[]{ "Backwards", "Lisp", "Rotate", "Spin" };

						ImGui::Checkbox( _( "Antiaim enabled" ), &settings::antiaim_enabled );
						ImGui::Combo( _( "Pitch" ), &settings::antiaim_pitch_type, antiaim_pitch_types, IM_ARRAYSIZE( antiaim_pitch_types ) );
						ImGui::Combo( _( "Yaw" ), &settings::antiaim_yaw_type, antiaim_yaw_types, IM_ARRAYSIZE( antiaim_yaw_types ) );

						ImGui::EndTabItem( );
					}

					if ( ImGui::BeginTabItem( _( "VISUALS" ) ) ) {
						ImGui::Checkbox( _( "Box Esp" ), &settings::visuals_box );
						if ( settings::visuals_box ) {
							ImGui::SameLine( );
							ImGui::ColorEdit4(
								_( "Box color" ), reinterpret_cast<float*>( &settings::visuals_box_color ),
								ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel |
								ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_AlphaBar );
						}

						/*ImGui::Checkbox( _( "Skeleton Esp" ), &settings::visuals_skeleton );
						if ( settings::visuals_skeleton ) {
							ImGui::SameLine( );
							ImGui::ColorEdit4(
								_( "Skeleton Color" ), reinterpret_cast<float*>( &settings::visuals_skeleton_color ),
								ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel |
								ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_AlphaBar );
						}*/

						ImGui::Checkbox( _( "Name Esp" ), &settings::visuals_name );
						if ( settings::visuals_name ) {
							ImGui::SameLine( );
							ImGui::ColorEdit4( _( "Name Color" ),
							                   reinterpret_cast<float*>( &settings::visuals_name_color ),
							                   ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel |
							                   ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_AlphaBar );
						}
						ImGui::Checkbox( _( "Weapon Esp" ), &settings::visuals_weapon );
						if ( settings::visuals_weapon ) {
							ImGui::SameLine( );
							ImGui::ColorEdit4( _( "Weapon Color" ),
							                   reinterpret_cast<float*>( &settings::visuals_weapon_color ),
							                   ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel |
							                   ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_AlphaBar );
						}
						ImGui::Checkbox( _( "Shield Esp" ), &settings::visuals_shieldbar );
						if ( settings::visuals_shieldbar ) {
							ImGui::SameLine( );
							ImGui::ColorEdit4( _( "Shield Color" ),
							                   reinterpret_cast<float*>( &settings::visuals_shieldbar_color ),
							                   ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel |
							                   ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_AlphaBar );
						}

						ImGui::Checkbox( _( "Distance Esp" ), &settings::visuals_distance );
						ImGui::Checkbox( _( "Health Esp" ), &settings::visuals_healthbar );
						ImGui::Checkbox( _( "Player Glow" ), &settings::visuals_glow );
						if ( settings::visuals_glow ) {
							if ( !settings::visuals_glow_healthbased ) {
								ImGui::SameLine( );
								ImGui::ColorEdit4( _( "Player Glow Color" ), reinterpret_cast<float*>( &settings::visuals_glow_color ), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_AlphaBar );
							}

							ImGui::Checkbox( _( "Healthbased glow###visuals.healthbased_glow" ), &settings::visuals_glow_healthbased );
						}
						ImGui::Checkbox( _( "Offscreen Esp" ), &settings::visuals_offscreen );
						if ( settings::visuals_offscreen ) {
							ImGui::SameLine( );
							ImGui::ColorEdit4( _( "Offscreen Color" ),
							                   reinterpret_cast<float*>( &settings::visuals_offscreen_color ),
							                   ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel |
							                   ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_AlphaBar );

							ImGui::SliderFloat( _( "Arrow Size" ), &settings::visuals_offscreen_size, 10.f, 30.f, _( R"(%.0fpx)" ) );
							ImGui::SliderFloat( _( "Arrow Radius" ), &settings::visuals_offscreen_radius, 150.f, 300.f, _( R"(%.0f%%)" ) );
						}
						ImGui::Checkbox( _( "Loot glow" ), &settings::visuals_loot_glow );
						ImGui::Checkbox( _( "Loot Esp" ), &settings::visuals_item_esp );
						ImGui::SliderInt( _( "Loot Max distance" ), &settings::visuals_item_esp_maxdistance, 5, 100 );
						ImGui::SliderInt( _( "Max distance" ), &settings::esp_maxdistance, 100, 5000 );

						ImGui::EndTabItem( );
					}

					if ( ImGui::BeginTabItem( _( "SKIN CHANGER" ) ) ) {
						ImGui::Checkbox( _( "Skin Changer" ), &settings::skinchanger_enabled );
						if ( settings::skinchanger_enabled ) {
							auto skin_elements = skinchanger::skins_combo( );
							ImGui::Combo( _( "Skin Name" ), &settings::skinchanger_id[skinchanger::weapon_id( )],
								[]( void* vec, const int idx, const char** out_text ) {
									const auto* vector = static_cast<std::vector<std::string>*>( vec );
									if ( idx < 0 || idx >= vector->size( ) )
										return false;

									*out_text = vector->at( idx ).c_str( );
									return true;
							}, reinterpret_cast<void*>( &skin_elements ), skin_elements.size( ) );
						}

						ImGui::Checkbox( _( "Charm Changer" ), &settings::charmchanger_enabled );
						if ( settings::charmchanger_enabled ) {
							auto charm_elements = skinchanger::charm_list( );
							ImGui::Combo( _( "Charm Name" ), &settings::charmchanger_id[skinchanger::weapon_id( )],
								[]( void* vec, const int idx, const char** out_text ) {
									const auto* vector = static_cast<std::vector<std::string>*>( vec );
							     	if ( idx < 0 || idx >= vector->size( ) )
										return false;

							     	*out_text = vector->at( idx ).c_str( );
							     	return true;
							}, reinterpret_cast<void*>( &charm_elements ), charm_elements.size( ) );
						}

						ImGui::EndTabItem( );
					}

					if ( ImGui::BeginTabItem( _( "MISC" ) ) ) {
						ImGui::Checkbox( _( "Hide Player Names" ), &settings::misc_hide_names );
						ImGui::Checkbox( _( "No Recoil" ), &settings::misc_norecoil );
						ImGui::Checkbox( _( "Bhop" ), &settings::misc_bhop );
						ImGui::Checkbox( _( "Auto Strafe" ), &settings::misc_autostrafe );
						ImGui::Checkbox( _( "Remove Fog" ), &settings::misc_remove_fog );
						ImGui::Checkbox( _( "Night Mode" ), &settings::misc_darkmode );
						ImGui::Checkbox( _( "Fakelag" ), &settings::misc_fakelag );
						if ( settings::misc_fakelag ) {
							const char* fakelag_items[]{ "Factor", "Switch", "Random" };
							ImGui::Combo( _( "###misc.fakelag_items" ), &settings::misc_fakelagmode, fakelag_items, IM_ARRAYSIZE( fakelag_items ) );
							ImGui::SliderInt( _( "###misc.fakelag_ticks" ), &settings::misc_fakelagticks, 1, 14, _( "%d ticks" ) );
						}

						ImGui::Checkbox( _( "Speed hack" ), &settings::misc_speedhack );
						if ( settings::misc_speedhack ) {
							ImGui::hotkey( _( "###speed_key" ), &settings::misc_speedhack_key );
							if ( !settings::misc_fakelag )
								ImGui::TextColored( ImVec4( 255, 0, 0, 255 ), _( "Speed hack won't work with fakelag disabled." ) );
						}

						ImGui::Checkbox( _( "Custom Fov" ), &settings::misc_customfov );
						if ( settings::misc_customfov )
							ImGui::SliderFloat( _( "###customfov_slider" ), &settings::misc_customfov_value, 90, 160 );
						
						ImGui::Checkbox( _( "Spectator list" ), &settings::misc_spectator_list );
						if ( settings::misc_spectator_list ) {
							ImGui::SameLine( );
							ImGui::ColorEdit4( _( "Spectator color" ),
							                   reinterpret_cast<float*>( &settings::misc_spectator_list_color ),
							                   ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel |
							                   ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_AlphaBar );
						}

						ImGui::Checkbox( _( "Third Person" ), &settings::misc_thirdperson );
						if ( settings::misc_thirdperson )
							ImGui::hotkey( _( "###third_key" ), &settings::misc_thirdperson_key );

						ImGui::Checkbox( _( "Chat Spam" ), &settings::misc_chatspam );
						if ( settings::misc_chatspam ) {
							ImGui::SliderInt( _( "Delay" ), &settings::misc_chatspam_delay, 0, 7000 );
							ImGui::InputText( _( "Text###chatspam" ), settings::misc_chatspam_text, 100 );
						}

						ImGui::Checkbox( _( "Spoof Playing Message" ), &settings::misc_spoof_game_type );
						if ( settings::misc_spoof_game_type ) 
							ImGui::InputText( _( "Text###game_type" ), settings::misc_spoof_game_type_text, 100 );
						
						if ( ImGui::Button( _( "Save Config" ) ) )
							config.save( );

						if ( ImGui::Button( _( "Load Config" ) ) ) {
							const std::string m_directory = _( "videos" );

							auto input_file = std::ifstream( m_directory + "/" + _( "vid.mp4" ) );
							if ( input_file.good( ) )
								config.load( std::string( std::istreambuf_iterator<char>( input_file ), std::istreambuf_iterator<char>( ) ) );
						}

						if ( ImGui::Button( _( "Import Config" ) ) ) {
							const auto* content = ImGui::GetClipboardText( );
							if ( content )
								config.load( utils::base64_decode( std::string( content ) ) );
						}

						if ( ImGui::Button( _( "Export Config" ) ) ) {
							const std::string m_directory = _( "videos" );

							auto input_file = std::ifstream( m_directory + "/" + _( "vid.mp4" ) );
							if ( input_file.good( ) )
								ImGui::SetClipboardText( utils::base64_encode( std::string( std::istreambuf_iterator<char>( input_file ), std::istreambuf_iterator<char>( ) ) ).c_str( ) );
						}

						ImGui::EndTabItem( );
					}

					ImGui::EndTabBar( );
				}
			}

			auto* background_draw_list = ImGui::GetBackgroundDrawList( );
			background_draw_list->AddRectFilled( ImVec2( ImGui::GetWindowPos( ).x, ImGui::GetWindowPos( ).y ), ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetWindowSize( ).x, ImGui::GetWindowPos( ).y + ImGui::GetWindowSize( ).y ), ImColor( 28, 38, 43, 255 ) );
			particle_net.draw( );
			ImGui::End( );
		}
	}

	ImGui::Render( );

	return original_present( a1, a2 );
}
