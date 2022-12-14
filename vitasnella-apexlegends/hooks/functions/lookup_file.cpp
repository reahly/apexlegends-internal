#include "../hooks.hh"
#include <fstream>
#include <filesystem>

std::string dirnameOf(const std::string& fname)
{
	const size_t pos = fname.find_last_of("\\/");
	return (std::string::npos == pos)
		? ""
		: fname.substr(0, pos);
}

bool __fastcall hooks::lookup_file( void* rcx, const char* file, const uintptr_t a3 ) {
	const auto ret = original_lookup_file( rcx, file, a3 );
	if ( !a3 )
		return ret;

	const auto def = *reinterpret_cast<uintptr_t*>( a3 + 0x10 );
	if ( !def )
		return ret;

	if ( std::string( file ).find( "nut" ) == std::string::npos || !std::filesystem::exists( file ) )
		return ret;

	printf( "overwriting %s.. ", file );

	std::ifstream file_stream( file );
	if ( file_stream.good( ) ) {
		const std::string content( ( std::istreambuf_iterator<char>( file_stream ) ), ( std::istreambuf_iterator<char>( ) ) );
		strcpy( *reinterpret_cast<char**>( *reinterpret_cast<uintptr_t*>( a3 + 0x10 ) ), content.c_str( ) );

		printf( "done! \n" );
	}
	
	return ret;
}
