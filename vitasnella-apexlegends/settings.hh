#pragma once

namespace settings {
	inline bool aimbot_enabled;
	inline int aimbot_bind = 6;
	inline int aimbot_silent;
	inline float aimbot_fov;
	inline bool aimbot_visible;
	inline bool aimbot_autofire;
	inline bool aimbot_downed;
	inline int aimbot_smooth = 1;

	inline bool antiaim_enabled;
	inline int antiaim_pitch_type;
	inline int antiaim_yaw_type;

	inline bool visuals_box;
	inline bool visuals_skeleton;
	inline bool visuals_name;
	inline bool visuals_healthbar;
	inline bool visuals_distance;
	inline bool visuals_weapon;
	inline bool visuals_shieldbar;
	inline bool visuals_glow;
	inline bool visuals_offscreen;
	inline bool visuals_glow_healthbased;
	inline int esp_maxdistance = 400;
	inline float visuals_offscreen_size = 15.f;
	inline float visuals_offscreen_radius = 150.f;
	inline float visuals_name_color[4] = { 255.0f, 255.0f, 255.0f, 255.0f };
	inline float visuals_box_color[4] = { 255.0f, 255.0f, 255.0f, 255.0f };
	inline float visuals_skeleton_color[4] = { 255.0f, 255.0f, 255.0f, 255.0f };
	inline float visuals_weapon_color[4] = { 255.0f, 255.0f, 255.0f, 255.0f };
	inline float visuals_shieldbar_color[4] = { 100.f, 149.f, 237.f, 255.0f };
	inline float visuals_offscreen_color[4] = { 255.f, 0.f, 0.f, 255.0f };
	inline float visuals_glow_color[4] = { 255.0f, 0.0f, 0.0f, 255.0f };
	inline bool visuals_loot_glow;
	inline bool visuals_item_esp;
	inline int visuals_item_esp_maxdistance;

	inline bool misc_spoof_game_type;
	inline char misc_spoof_game_type_text[100];
	inline bool misc_chatspam;
	inline int misc_chatspam_delay;
	inline char misc_chatspam_text[100];
	inline bool misc_customfov;
	inline bool misc_speedhack;
	inline int misc_speedhack_key;
	inline bool misc_norecoil;
	inline bool misc_hide_names;
	inline bool misc_remove_fog;
	inline bool misc_darkmode;
	inline bool misc_showfov;
	inline bool misc_bhop, misc_autostrafe;
	inline bool misc_fakelag;
	inline bool misc_thirdperson;
	inline int misc_thirdperson_key;
	inline int misc_fakelagmode;
	inline int misc_fakelagticks = 1;
	inline float misc_customfov_value = 90.f;
	inline bool misc_spectator_list;
	inline float misc_spectator_list_pos[4] = { 500.f, 300.f, 0.0f, 0.0f };
	inline float misc_spectator_list_color[4] = { 0.f, 255.f, 0.0f, 255.0f };

	inline bool skinchanger_enabled;
	inline int skinchanger_id[80];

	inline bool charmchanger_enabled;
	inline int charmchanger_id[80];
}