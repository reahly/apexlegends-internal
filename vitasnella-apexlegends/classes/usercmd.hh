#pragma once
#include <cstdint>
#include "../utilities/vec3.hh"
#include "../utilities/utils.hh"

enum cmd_buttons {
	in_attack = 1 << 0,
	in_jump = 1 << 1,
	in_duck = 1 << 2,
	in_forward = 1 << 3,
	in_sliding = 12,
	in_back = 1 << 4,
	in_left = 1 << 9,
	in_right = 1 << 10,
	in_use = 8224,
};

enum flags {
	fl_ground = 0x1,
	fl_duck = 0x2,
};

struct usercmd {
	int command_number{ };
	int tick_count{ };
	float unk{ };
	vec3_t viewangles{ };
	vec3_t move{ };
	char _pad0[0x14]{ };
	int buttons{ };
};
