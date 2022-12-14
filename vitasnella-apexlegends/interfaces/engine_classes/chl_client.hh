#pragma once
#include "../../classes/client_class.hh"
#include "../../utilities/utils.hh"

struct chl_client_t {
	client_class* get_all_classes( ) {
		return utils::get_vfunc<12, client_class*>( this );
	}
};