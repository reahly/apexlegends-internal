#pragma once

struct client_state_t {
	char pad_0000[96]{ }; //0x0000
	void* netchan{ }; //0x0060
	char pad_0068[48]{ }; //0x0068
	int32_t signon_state{ }; //0x0098
	char pad_009C[4]{ }; //0x009C
	double next_cmd_time{ }; //0x00A0
	uint32_t server_count{ }; //0x00A8
	uint32_t current_sequence{ }; //0x00AC
	char pad_00B0[168]{ }; //0x00B0
	int32_t delta_tick{ }; //0x0158
	char pad_015C[12]{ }; //0x015C
	uint32_t player_slot{ }; //0x0168
	char pad_016C[8]{ }; //0x016C
	char map_file_name[64]{ }; //0x0174
	char level_name_short[64]{ }; //0x01B4
	char level_name[260]{ }; //0x01F4
	char pad_02F8[4]{ }; //0x02F8
	int32_t highest_client_index{ }; //0x02FC
	char pad_0300[64]{ }; //0x0300
	int32_t max_clients{ }; //0x0340
	char pad_0344[100748]{ }; //0x0344
	int32_t last_used_command{ }; //0x18CD0
};