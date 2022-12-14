#include <cstdio>
#include <thread>
#include <Windows.h>
#include "hooks/hooks.hh"
#include "interfaces/interfaces.hh"
#include "utilities/netvar_manager.hh"
#include "utilities/config/config.hh"

bool __stdcall DllMain( const HMODULE module, const DWORD reason, LPVOID ) {
	if ( reason != DLL_PROCESS_ATTACH )
		return false;

	AllocConsole( );
	FILE* fp;
	freopen_s( &fp, _( "CONOUT$" ), _( "w" ), stdout );

	config.init( );
	interfaces::init( );
	netvar_manager::init( );
	hooks::init( );

	return true;
}
