#pragma once

inline int vmt_filled_records = 0;
inline void* vmthook_data[10000];

class vmt_hook {
public:
	template <typename T>
	__forceinline vmt_hook( const char* module, T class_ ) {
		const auto module_base = reinterpret_cast<DWORD64>( LI_FN( GetModuleHandleA ).cached( )( module ) );
		if ( !module_base )
			return;

		size = 0;
		auto* const vftable = *reinterpret_cast<PVOID**>( class_ );
		auto* const header = reinterpret_cast<PIMAGE_NT_HEADERS>( module_base + reinterpret_cast<PIMAGE_DOS_HEADER>( module_base )->e_lfanew );
		while ( in_memory( vftable[size], module_base, header ) )
			size++;

		auto* const new_vft = static_cast<PVOID*>( &vmthook_data[vmt_filled_records] );
		__movsq( reinterpret_cast<PDWORD64>( new_vft ), reinterpret_cast<const PDWORD64>( vftable ), size );
		*reinterpret_cast<PVOID**>( class_ ) = new_vft;
		tbl_encrypted = static_cast<PVOID*>( new_vft );
		vmt_filled_records += size;
	}

	template <typename T>
	__forceinline void setup_hook( T* original, const PVOID hook, const int index ) {
		auto* const table = static_cast<PVOID*>( tbl_encrypted );
		*original = reinterpret_cast<T>( table[index] );
		table[index] = hook;
	}

private:
	PVOID* tbl_encrypted = nullptr;
	DWORD size = 0;

	static bool in_memory( PVOID addr, const DWORD64 base, PIMAGE_NT_HEADERS headers ) {
		auto* sect = IMAGE_FIRST_SECTION( headers );
		for ( DWORD cnt = 0; cnt < headers->FileHeader.NumberOfSections; cnt++, sect++ ) {
			if ( sect->Characteristics & IMAGE_SCN_MEM_EXECUTE &&
				reinterpret_cast<DWORD64>( addr ) >= base + sect->VirtualAddress &&
				reinterpret_cast<DWORD64>( addr ) < base + sect->VirtualAddress + sect->Misc.VirtualSize )
				return true;
		}
		return false;
	}
};
