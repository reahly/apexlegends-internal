#pragma once
#include <cstdint>

struct datamap_t;

struct typedescription_t {
	int32_t field_type;
	uint32_t _pad0;
	char* field_name;
	int field_offset[2];
	char* external_name;
	uint64_t pad_0014[5];
	datamap_t* td;
};

struct datamap_t {
	typedescription_t* data_desc;
	int32_t num;
	uint32_t _pad0;
	char* class_name;
	uint64_t _unk0;
	uint64_t _unk1;
	datamap_t* base_map;
};

namespace datamap_manager {
	uint16_t find( datamap_t*, const char* );
};