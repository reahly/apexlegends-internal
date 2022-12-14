#pragma once
#include "../utilities/utils.hh"

struct renderable_t {
	bool setup_bones( utils::matrix_t* matrix, const int max_bones, const int bone_mask, const float current_time ) {
		return utils::get_vfunc<16, bool>( this, matrix, max_bones, bone_mask, current_time );
	}

	void get_render_bounds( vec3_t& mins, vec3_t& maxs ) {
		using original_fn = void( __thiscall*)( void*, vec3_t&, vec3_t& );
		( *reinterpret_cast<original_fn**>( this ) )[19]( this, mins, maxs );
	}
};
