#pragma once
#include <cstdint>
#include <fstream>
#include <hash.hh>

namespace netvar_manager {
	void init( );
	void dump( );
	uint16_t get( hash_t );
}

#define NETVAR( type, func, netvar ) type& func() \
{\
    static auto offset = 0;\
    if ( !offset )\
       offset = netvar_manager::get( CT_HASH( netvar ) );\
    return *reinterpret_cast<type*>( reinterpret_cast<uintptr_t>( this ) + offset );\
}