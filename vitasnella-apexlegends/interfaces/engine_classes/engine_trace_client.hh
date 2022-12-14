#pragma once
#include "../utilities/vec3.hh"

struct cplane_t {
	vec3_t surfaceN;
	float distance{ };
};

struct surface_t {
	char* name; //0x0000
	int16_t surface_prop; //0x0004
	uint16_t flags; //0x0006
};

struct trace_t {
	vec3_t start; //0x0000
	char pad_000C[4]{ }; //0x000C
	vec3_t end; //0x0010
	char pad_001C[4]{ }; //0x001C
	cplane_t plane; //0x0020
	float fraction{ }; //0x0030
	int32_t contents{ }; //0x0034
	uint16_t disp_flags{ }; //0x0038
	bool all_solid{ }; //0x003A
	bool start_solid{ }; //0x003B
	char pad_003C[4]{ }; //0x003C
	float fraction_left_solid{ }; //0x0040
	char pad_0044[4]{ }; //0x0044
	surface_t surface{ }; //0x0048
	int32_t hitgroup{ }; //0x0050
	int16_t physics_bone{ }; //0x0054
	uint16_t world_surface_index{ }; //0x0056
	void* ent{ }; //0x0058
	int32_t hitbox{ }; //0x005C
	char pad_0060[288]{ }; //0x0060
};

struct ray_t {
	vec3_t m_start;
	char unk01[0x4];
	vec3_t m_delta;
	char unk02[0x4];
	vec3_t m_startoffset;
	char unk03[0x20];
	void* m_worldaxistransform = nullptr;
	char unk04[0x3];
	bool m_isray;
	bool m_isswept;
	char unk05[0x3];

	void init( const vec3_t& start, const vec3_t& end ) {
		m_start = start;
		m_delta = end - start;
		m_isswept = m_delta.length( ) != 0;
		m_startoffset = vec3_t( 0, 0, 0 );
		m_isray = true;
		m_worldaxistransform = nullptr;
	}
};

struct engine_trace_client_t {
	void trace_ray( const ray_t& ray, const unsigned int mask, trace_t* trace ) {
		return utils::get_vfunc<4, void>( this, ray, mask, trace );
	}
};
