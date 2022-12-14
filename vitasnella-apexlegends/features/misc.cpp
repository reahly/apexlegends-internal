#include "misc.hh"
#include <lazy_importer.hh>
#include "../settings.hh"
#include "../classes/entity.hh"
#include "../interfaces/interfaces.hh"
#include "../utilities/utils.hh"

void bhop( usercmd* cmd ) {
	auto* local_player = entity_t::get_local_player( );
	if ( !settings::misc_bhop || !local_player || !local_player->alive( ) )
		return;

	if ( cmd->buttons & in_jump && !( local_player->flags( ) & fl_ground ) )
		cmd->buttons &= ~in_jump;
}

void autostrafe( usercmd* cmd ) {
	auto* local_player = entity_t::get_local_player( );
	if ( !settings::misc_autostrafe || !local_player || !local_player->alive( ) )
		return;

	if ( !( cmd->buttons & in_jump ) || local_player->flags( ) & fl_ground )
		return;

	const auto velocity = local_player->velocity( );
	const auto m_speed = velocity.length_2d( );

	auto m_ideal = m_speed > 0.f ? RAD2DEG( std::asin( 15.f / m_speed ) ) : 90.f;
	auto m_ideal2 = m_speed > 0.f ? RAD2DEG( std::asin( 30.f / m_speed ) ) : 90.f;

	m_ideal = std::clamp( m_ideal, 0.f, 90.f );
	m_ideal2 = std::clamp( m_ideal2, 0.f, 90.f );

	static auto m_switch_value = 0.f;
	m_switch_value *= -1.f;

	cmd->move.x = 0.f;

	const auto delta = utils::normalized_angle( cmd->viewangles.y );
	const auto abs_delta = std::abs( delta );

	if ( delta > 0.f )
		cmd->move.y = -450.f;

	else if ( delta < 0.f )
		cmd->move.y = 450.f;

	auto velocity_angle = float( );
	auto correct = float( );
	if ( abs_delta <= m_ideal || abs_delta >= 30.f ) {
		velocity_angle = RAD2DEG( std::atan2( velocity.y, velocity.x ) );
		const auto velocity_delta = utils::normalized_angle( cmd->viewangles.y - velocity_angle );

		correct = m_ideal2 * 2.f;
		if ( velocity_delta <= correct || m_speed <= 15.f ) {
			if ( -correct <= velocity_delta || m_speed <= 15.f ) {
				cmd->viewangles.y += m_ideal * m_switch_value;
				cmd->move.y = 450.f * m_switch_value;
			} else {
				cmd->viewangles.y = velocity_angle - correct;
				cmd->move.y = 450.f;
			}
		}

	} else {
		cmd->viewangles.y = velocity_angle + correct;
		cmd->move.y = -450.f;
	}
}

void fakelag( usercmd* cmd ) {
	auto* local_player = entity_t::get_local_player( );
	if ( !settings::misc_fakelag || !local_player || !local_player->alive( ) )
		return;

	const auto factor = std::clamp( settings::misc_fakelagticks, 1, 14 );
	auto wish_ticks = 0;

	switch ( settings::misc_fakelagmode ) {
	case 0:
		wish_ticks = factor;

		break;

	case 1:
		if ( cmd->tick_count % 30 < 15 )
			wish_ticks = factor;

		break;

	case 2:
		wish_ticks = utils::random_int( 1, factor );

		break;

	default: break;
	}

	static auto chocked = 0;
	if ( cmd->buttons & in_attack || local_player->velocity( ).empty( ) ) {
		utils::global::send_packet = true;
		chocked = 0;

		return;
	}

	utils::global::send_packet = chocked >= wish_ticks;
	if ( utils::global::send_packet )
		chocked = 0;
	else
		chocked++;
}

void norecoil( ) {
	auto* local_player = entity_t::get_local_player( );
	if ( !settings::misc_norecoil || !local_player || !local_player->alive( ) )
		return;

	static vec3_t old_aimpunch, new_view;

	const auto aimpunch = local_player->aimpunch( );
	const auto current_view = local_player->viewangles( );

	new_view.x = current_view.x + old_aimpunch.x - aimpunch.x;
	new_view.y = current_view.y + old_aimpunch.y - aimpunch.y;

	local_player->viewangles( ) = new_view;

	old_aimpunch = aimpunch;
}

void thirdperson( ) {
	auto* local_player = entity_t::get_local_player( );
	if ( !local_player || !local_player->alive( ) )
		return;

	auto* const third_person = interfaces::convar->find_var( _( "thirdperson_override" ) );
	if ( !third_person )
		return;

	static auto reset = false;
	if ( !settings::misc_thirdperson ) {
		if ( reset ) {
			third_person->value = 0;
			reset = false;
		}

		return;
	}

	if ( !settings::misc_thirdperson_key ) {
		third_person->value = true;
		reset = true;
	} else {
		static auto toggle = false;
		static auto last_press = uintptr_t( );
		if ( LI_FN( GetAsyncKeyState ).cached( )( settings::misc_thirdperson_key ) & 1 && LI_FN( GetTickCount64 ).cached( )( ) - last_press > 300 ) {
			last_press = LI_FN( GetTickCount64 ).cached( )( );
			toggle = !toggle;
		}

		third_person->value = toggle;
		reset = true;
	}
}

void remove_fog( ) {
	auto* const world = entity_t::get_client_entity( 0 );
	if ( !world )
		return;
	
	*reinterpret_cast<bool*>( world + 0xAD9 ) = !settings::misc_remove_fog; // m_bStartDark + 1
}

void nightmode( ) {
	static uint8_t* addr = nullptr;
	if ( !addr )
		addr = utils::find_pattern( _( "F3 0F 11 05 ? ? ? ? C3 CC CC CC CC CC CC CC F3 0F 11 05 ? ? ? ? C3 CC CC CC CC CC CC CC C6 05 ? ? ? ? ?" ) );

	if ( !addr )
		return;
	
	reinterpret_cast<void( __fastcall* )( float )>( addr )( settings::misc_darkmode ? -6.5f : 0.f );
}

void speed_hack( ) {	
	auto* local_player = entity_t::get_local_player( );
	if ( !local_player || !local_player->alive( ) )
		return;
	
	static auto addr = uintptr_t( );
	if ( !addr )
		addr = reinterpret_cast<uintptr_t>( utils::find_pattern( _( "0F 2E C8 7A 02 74 26" ) ) );
	
	if ( !addr )
		return;
	
	const auto final_addr = addr + 7 + *reinterpret_cast<uint32_t*>( addr + 11 ) + 8;
	if ( local_player->velocity( ).length( ) <= 0 || !settings::misc_speedhack || settings::misc_speedhack_key != 0 && !LI_FN( GetAsyncKeyState ).cached( )( settings::misc_speedhack_key ) ) {
		*reinterpret_cast<float*>( final_addr ) = 1.f;
		return;
	}

	if ( !utils::global::send_packet )
		*reinterpret_cast<float*>( final_addr ) = 2.0f;
}

void custom_fov( ) {
	if ( !settings::misc_customfov )
		return;

	if ( static auto once = false; !once ) {
		static auto addr = uintptr_t( );
		if ( !addr )
			addr = RESOLVE_RVA( utils::find_pattern( _( "F3 0F 5D 1D ? ? ? ? F3 41 0F 59 DD ? ? ? ? ?" ) ) + 0x1 );

		if ( !addr )
			return;
		
		auto old = DWORD( );
		LI_FN( VirtualProtect ).cached( )( reinterpret_cast<void*>( addr ), 0x1, PAGE_EXECUTE_READWRITE, &old );
		*reinterpret_cast<float*>( addr ) = 300.f;
		LI_FN( VirtualProtect ).cached( )( reinterpret_cast<void*>( addr ), 0x1, old, &old );

		once = true;
	}
}

void chatspam( ) {
	if ( !settings::misc_chatspam )
		return;
	
	static uint8_t* addr = nullptr;
	if ( !addr )
		addr = utils::find_pattern( _( "40 53 48 81 EC ? ? ? ? 48 8B D9 48 85 C9 0F 84 ? ? ? ? 80 39 00 0F 84 ? ? ? ? 48 8B 0D ? ? ? ?" ) );

	if ( !addr )
		return;
	
	static auto last_spammed = DWORD( );
	if ( LI_FN( GetTickCount ).cached( )( ) - last_spammed > settings::misc_chatspam_delay ) {
		reinterpret_cast<void*( __fastcall* )( const char* )>( addr )( settings::misc_chatspam_text );

		last_spammed = LI_FN( GetTickCount ).cached( )( );
	}
}

void misc::init( usercmd* cmd ) {
	bhop( cmd );
	autostrafe( cmd );
	fakelag( cmd );
	norecoil( );
	thirdperson( );
	remove_fog( );
	nightmode( );
	speed_hack( );
	custom_fov( );
	chatspam( );
}
