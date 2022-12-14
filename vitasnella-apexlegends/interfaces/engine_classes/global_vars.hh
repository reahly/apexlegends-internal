#pragma once

struct global_vars_t {
	double realtime; //0x0000 
	__int32 framecount; //0x0008 
	float absoluteframetime; //0x000C 
	float curtime; //0x0010 
	float frametime; //0x0014
	float unk0; // 0x0018
	float interval_per_tick; // 0x001C
};
