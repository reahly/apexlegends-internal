#include "netvar_manager.hh"
#include <functional>
#include <iomanip>
#include <ios>
#include <map>
#include <string>
#include "../interfaces/interfaces.hh"

std::map<hash_t, recv_prop*> netvars_map;

void dump_table_recursive( recv_table* table ) {
	for ( auto i = 0; i < table->num_props; ++i ) {
		auto* const prop = table->props[i];
		if ( !prop || isdigit( prop->prop_name[0] ) )
			continue;

		if ( prop->data_table )
			dump_table_recursive( prop->data_table );

		std::string hash_string = table->table_name;
		hash_string.append( _( "->" ) );
		if ( prop->data_table ) {
			hash_string.append( prop->data_table->table_name );
			hash_string.append( _( "->" ) );
		}

		hash_string.append( prop->prop_name );
		netvars_map[HASH( hash_string.c_str( ) )] = prop;
	}
}

void netvar_manager::init( ) {
	for ( const auto* data = interfaces::chl_client->get_all_classes( ); data; data = data->next )
		if ( data->table )
			dump_table_recursive( data->table );
}

void dump_table_to_file_recursive( recv_table* table, const int depth ) {
	const auto str = [ ]( const send_prop_type type ){
		switch ( type ) {
		case send_prop_type::integer:
			return _( "int" );
		case send_prop_type::vector:
			return _( "vector3d" );
		case send_prop_type::string:
			return _( "string" );
		case send_prop_type::floating:
			return _( "float" );
		case send_prop_type::vectorxy:
			return _( "vector2d" );
		case send_prop_type::array:
			return _( "array" );
		case send_prop_type::rotation:
			return _( "rotation" );
		case send_prop_type::bitmask:
			return _( "bitmask" );
		case send_prop_type::cycle:
			return _( "cycle" );
		case send_prop_type::time:
			return _( "time" );
		case send_prop_type::datatable:
			return _( "table" );

		default:
			break;
		}

		return _( "" );
	};

	std::string pre;
	for ( auto i = 0; i < depth; i++ )
		pre.append( _( "\t" ) );

	std::ofstream file( _( "netvars_dump.txt" ) );
	file << pre << table->table_name << _( "\n" );

	for ( auto i = 0; i < table->num_props; ++i ) {
		const auto* const prop = table->props[i];
		if ( !prop || isdigit( prop->prop_name[0] ) )
			continue;

		std::string variable_name = prop->prop_name;
		if ( variable_name.find( _( "baseclass" ) ) == 0 || variable_name.find( '0' ) == 0 || variable_name.find( '1' ) == 0 || variable_name.find( '2' ) == 0 )
			continue;

		file << pre << _( "\t " ) << variable_name << " " << std::setfill( '_' ) << std::setw( 60 - variable_name.length( ) - depth * 4 ) << _( "[0x" ) << std::setfill( '0' ) << std::setw( 8 ) << std::hex << std::uppercase << prop->offset << _( "]" ) << _( "[" ) << str( prop->type ) << _( "]\n" );

		if ( prop->data_table )
			dump_table_to_file_recursive( prop->data_table, depth + 1 );
	}
}

void netvar_manager::dump( ) {
	for ( const auto* data = interfaces::chl_client->get_all_classes( ); data; data = data->next )
		if ( data->table )
			dump_table_to_file_recursive( data->table, 0 );
}

uint16_t netvar_manager::get( const hash_t hash ) {
	if ( !netvars_map[hash] )
		return 0;

	return netvars_map[hash]->offset;
}
