#include "datamap_manager.hh"
#include <iostream>

uint16_t datamap_manager::find( datamap_t* map, const char* name ) {
	for ( auto i = 0; i < map->num; i++ ) {
		const auto* const field_name = map->data_desc[i].field_name;
		if ( !field_name )
			continue;

		std::cout << field_name << std::endl;
	}
	
	return 0u;
}
