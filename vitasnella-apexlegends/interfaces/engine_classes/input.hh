#pragma once
#include "../../classes/usercmd.hh"
#include "../../utilities/utils.hh"

struct input_t {
	usercmd* get_user_cmd( const int slot, const int sequence_number ) {
		return utils::get_vfunc<9, usercmd*>( this, slot, sequence_number );
	}
};
