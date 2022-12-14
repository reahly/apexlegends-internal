#pragma once
#include <cstdint>
#include "../utilities/vec3.hh"

struct mstudiobone_t {
	int32_t name_index;         // 0x0000
	int32_t parent;             // 0x0004
	int32_t bonecontroller[6];  // 0x0008
	vec3_t N00001D0F;      // 0x0020
	char pad_002C[136];         // 0x002C
};

struct mstudiobbox_t {
	int32_t bone{ }; // 0x0000
	int32_t group{ }; // 0x0004
	vec3_t min; // 0x0008
	vec3_t max; // 0x0014
	int32_t hitbox_name_id{ }; // 0x0020
	char pad_0024[4]{ }; // 0x0024
	int32_t hitbox_name_id_{ }; // 0x0028
};

struct mstudiohitboxset_t {
	int32_t hitbox_set_name_index; // 0x0000
	int32_t num_hitboxes; // 0x0004
	int32_t hitbox_index; // 0x0008
};

struct studiohdr_t {
	int32_t id{ }; // 0x0000
	int32_t version{ }; // 0x0004
	char pad_0008[8]{ }; // 0x0008
	char name[64]{ }; // 0x0010
	int32_t length{ }; // 0x0050
	char pad_0054[24]{ }; // 0x0054
	vec3_t min; // 0x006C
	vec3_t max; // 0x0078
	char pad_0084[24]{ }; // 0x0084
	uint32_t flags{ }; // 0x009C
	int32_t num_bones{ }; // 0x00A0
	int32_t bone_index{ }; // 0x00A4
	int32_t num_bone_controllers{ }; // 0x00A8
	int32_t bone_controller_index{ }; // 0x00AC
	int32_t num_hitbox_sets{ }; // 0x00B0
	int32_t hitbox_set_index{ }; // 0x00B4

	[[nodiscard]] mstudiobone_t* get( const int i ) const {
		return reinterpret_cast<mstudiobone_t*>( reinterpret_cast<uintptr_t>( this ) + bone_index ) + i;
	}
};
