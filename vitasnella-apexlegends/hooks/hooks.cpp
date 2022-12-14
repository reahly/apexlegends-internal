#include "hooks.hh"
#include <lazy_importer.hh>
#include "../interfaces/interfaces.hh"
#include "library/vmthook.hh"

void hooks::init( ) {
	const auto silent_aim = [ ]( ) {
		auto* const address = utils::find_pattern( _( "F2 0F 11 4C 24 ?? E8 ?? ?? ?? ?? 84 C0" ) ) - 0x22;
		if ( !address )
			return;
		
		BYTE data_fill[0x22] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x89, 0x44, 0x24, 0x28, 0xF3, 0x0F, 0x10, 0x44, 0x24, 0x28, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, };
		DWORD old_protect;
		LI_FN( VirtualProtect ).cached( )( reinterpret_cast<void*>( address ), 0x22, PAGE_EXECUTE_READWRITE, &old_protect );
		LI_FN( memcpy ).cached( )( reinterpret_cast<void*>( address ), data_fill, sizeof data_fill );
		LI_FN( VirtualProtect ).cached( )( reinterpret_cast<void*>( address ), 0x22, old_protect, &old_protect );
	};

	silent_aim( );
	
	vmt_hook( nullptr, interfaces::input ).setup_hook( &original_createmove, createmove, 4 );
	vmt_hook( nullptr, interfaces::file_system ).setup_hook( &original_lookup_file, lookup_file, 80 );
	vmt_hook( nullptr, interfaces::engine_client ).setup_hook( &original_get_player_info, get_player_info, 24 );

	swapchain = *reinterpret_cast<IDXGISwapChain**>( RESOLVE_RVA( utils::find_pattern( _( "4C 8D 0D ? ? ? ? 2B 45" ) ), 7 ) );
	vmt_hook( _( "d3d11" ), *reinterpret_cast<uintptr_t*>( reinterpret_cast<uintptr_t>( swapchain ) + *static_cast<BYTE*>( utils::find_pattern( _( "8B ? ? ? ? ? 48 8B 01 48 8D 55" ), _( "dxgi.dll" ) ) + 2 ) ) ).setup_hook( &original_present, present, 13 );
}