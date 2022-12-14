#include "vec3.hh"
#include "utils.hh"

void vec3_t::normalize( ) {
	x = utils::normalized_angle( x );
	y = utils::normalized_angle( y );
	z = utils::normalized_angle( z );
}
