#pragma once

struct prediction_t {
	void set_local_viewangles( const vec3_t angle ) {
		utils::get_vfunc<14, void>( this, angle );
	}
};