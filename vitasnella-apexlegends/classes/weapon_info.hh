#pragma once
#include "../utilities/vec3.hh"

enum class eActiveInventorySlot : std::uint32_t {};
enum class eWeaponBallisticType : std::uint32_t {};
enum class eWeaponCooldownType : std::uint32_t {};
enum class eWeaponDamageFalloffType : std::uint32_t {};
enum class eWeaponFireMode : std::uint32_t {};
enum class eWeaponHolsterType : std::uint32_t {};

class weapon_info_t {
public:
	char const *printname;                                      // 0x0000, size 8
	char const *shortprintname;                                 // 0x0008, size 8
	char const *description;                                    // 0x0010, size 8
	float fire_rate;                                            // 0x0018, size 4
	float fire_rate_max;                                        // 0x001C, size 4
	float fire_rate_max_time_speedup;                           // 0x0020, size 4
	float fire_rate_max_time_cooldown;                          // 0x0024, size 4
	bool fire_rate_max_use_ads;                                 // 0x0028, size 1
	char unk_0[3];                                              // 0x0029
	float fire_duration;                                        // 0x002C, size 4
	bool net_bullet_fix;                                        // 0x0030, size 1
	char unk_1[3];                                              // 0x0031
	int burst_fire_count;                                       // 0x0034, size 4
	float burst_fire_delay;                                     // 0x0038, size 4
	float red_crosshair_range;                                  // 0x003C, size 4
	bool ui1_enable;                                            // 0x0040, size 1
	bool ui2_enable;                                            // 0x0041, size 1
	bool ui3_enable;                                            // 0x0042, size 1
	bool ui4_enable;                                            // 0x0043, size 1
	bool ui5_enable;                                            // 0x0044, size 1
	bool ui6_enable;                                            // 0x0045, size 1
	bool ui7_enable;                                            // 0x0046, size 1
	bool ui8_enable;                                            // 0x0047, size 1
	bool ui9_enable;                                            // 0x0048, size 1
	bool ui10_enable;                                           // 0x0049, size 1
	bool ui11_enable;                                           // 0x004A, size 1
	bool ui12_enable;                                           // 0x004B, size 1
	bool ui13_enable;                                           // 0x004C, size 1
	bool ui14_enable;                                           // 0x004D, size 1
	bool ui15_enable;                                           // 0x004E, size 1
	bool ui16_enable;                                           // 0x004F, size 1
	bool ui17_enable;                                           // 0x0050, size 1
	bool ui18_enable;                                           // 0x0051, size 1
	bool ui19_enable;                                           // 0x0052, size 1
	bool ui20_enable;                                           // 0x0053, size 1
	bool ui21_enable;                                           // 0x0054, size 1
	bool ui22_enable;                                           // 0x0055, size 1
	bool ui23_enable;                                           // 0x0056, size 1
	bool ui24_enable;                                           // 0x0057, size 1
	bool ui25_enable;                                           // 0x0058, size 1
	bool ui26_enable;                                           // 0x0059, size 1
	bool ui27_enable;                                           // 0x005A, size 1
	bool ui28_enable;                                           // 0x005B, size 1
	bool ui29_enable;                                           // 0x005C, size 1
	bool ui30_enable;                                           // 0x005D, size 1
	bool ui31_enable;                                           // 0x005E, size 1
	bool ui32_enable;                                           // 0x005F, size 1
	bool ui1_draw_cloaked;                                      // 0x0060, size 1
	bool ui2_draw_cloaked;                                      // 0x0061, size 1
	bool ui3_draw_cloaked;                                      // 0x0062, size 1
	bool ui4_draw_cloaked;                                      // 0x0063, size 1
	bool ui5_draw_cloaked;                                      // 0x0064, size 1
	bool ui6_draw_cloaked;                                      // 0x0065, size 1
	bool ui7_draw_cloaked;                                      // 0x0066, size 1
	bool ui8_draw_cloaked;                                      // 0x0067, size 1
	bool ui9_draw_cloaked;                                      // 0x0068, size 1
	bool ui10_draw_cloaked;                                     // 0x0069, size 1
	bool ui11_draw_cloaked;                                     // 0x006A, size 1
	bool ui12_draw_cloaked;                                     // 0x006B, size 1
	bool ui13_draw_cloaked;                                     // 0x006C, size 1
	bool ui14_draw_cloaked;                                     // 0x006D, size 1
	bool ui15_draw_cloaked;                                     // 0x006E, size 1
	bool ui16_draw_cloaked;                                     // 0x006F, size 1
	bool ui17_draw_cloaked;                                     // 0x0070, size 1
	bool ui18_draw_cloaked;                                     // 0x0071, size 1
	bool ui19_draw_cloaked;                                     // 0x0072, size 1
	bool ui20_draw_cloaked;                                     // 0x0073, size 1
	bool ui21_draw_cloaked;                                     // 0x0074, size 1
	bool ui22_draw_cloaked;                                     // 0x0075, size 1
	bool ui23_draw_cloaked;                                     // 0x0076, size 1
	bool ui24_draw_cloaked;                                     // 0x0077, size 1
	bool ui25_draw_cloaked;                                     // 0x0078, size 1
	bool ui26_draw_cloaked;                                     // 0x0079, size 1
	bool ui27_draw_cloaked;                                     // 0x007A, size 1
	bool ui28_draw_cloaked;                                     // 0x007B, size 1
	bool ui29_draw_cloaked;                                     // 0x007C, size 1
	bool ui30_draw_cloaked;                                     // 0x007D, size 1
	bool ui31_draw_cloaked;                                     // 0x007E, size 1
	bool ui32_draw_cloaked;                                     // 0x007F, size 1
	char const *ui1_mesh_override;                              // 0x0080, size 8
	char const *ui2_mesh_override;                              // 0x0088, size 8
	char const *ui3_mesh_override;                              // 0x0090, size 8
	char const *ui4_mesh_override;                              // 0x0098, size 8
	char const *ui5_mesh_override;                              // 0x00A0, size 8
	char const *ui6_mesh_override;                              // 0x00A8, size 8
	char const *ui7_mesh_override;                              // 0x00B0, size 8
	char const *ui8_mesh_override;                              // 0x00B8, size 8
	char const *ui9_mesh_override;                              // 0x00C0, size 8
	char const *ui10_mesh_override;                             // 0x00C8, size 8
	char const *ui11_mesh_override;                             // 0x00D0, size 8
	char const *ui12_mesh_override;                             // 0x00D8, size 8
	char const *ui13_mesh_override;                             // 0x00E0, size 8
	char const *ui14_mesh_override;                             // 0x00E8, size 8
	char const *ui15_mesh_override;                             // 0x00F0, size 8
	char const *ui16_mesh_override;                             // 0x00F8, size 8
	char const *ui17_mesh_override;                             // 0x0100, size 8
	char const *ui18_mesh_override;                             // 0x0108, size 8
	char const *ui19_mesh_override;                             // 0x0110, size 8
	char const *ui20_mesh_override;                             // 0x0118, size 8
	char const *ui21_mesh_override;                             // 0x0120, size 8
	char const *ui22_mesh_override;                             // 0x0128, size 8
	char const *ui23_mesh_override;                             // 0x0130, size 8
	char const *ui24_mesh_override;                             // 0x0138, size 8
	char const *ui25_mesh_override;                             // 0x0140, size 8
	char const *ui26_mesh_override;                             // 0x0148, size 8
	char const *ui27_mesh_override;                             // 0x0150, size 8
	char const *ui28_mesh_override;                             // 0x0158, size 8
	char const *ui29_mesh_override;                             // 0x0160, size 8
	char const *ui30_mesh_override;                             // 0x0168, size 8
	char const *ui31_mesh_override;                             // 0x0170, size 8
	char const *ui32_mesh_override;                             // 0x0178, size 8
	bool silenced;                                              // 0x0180, size 1
	bool is_semi_auto;                                          // 0x0181, size 1
	bool fast_swap_to;                                          // 0x0182, size 1
	bool fast_swap_from;                                        // 0x0183, size 1
	bool instant_swap_to;                                       // 0x0184, size 1
	bool instant_swap_from;                                     // 0x0185, size 1
	bool offhand_switch_force_draw;                             // 0x0186, size 1
	bool primary_fire_does_not_block_sprint;                    // 0x0187, size 1
	bool bypass_semiauto_hold_protection;                       // 0x0188, size 1
	bool aimassist_disable_hipfire;                             // 0x0189, size 1
	bool aimassist_disable_ads;                                 // 0x018A, size 1
	bool aimassist_disable_hipfire_titansonly;                  // 0x018B, size 1
	bool aimassist_disable_ads_titansonly;                      // 0x018C, size 1
	bool aimassist_disable_hipfire_humansonly;                  // 0x018D, size 1
	bool aimassist_disable_ads_humansonly;                      // 0x018E, size 1
	char unk_2[1];                                              // 0x018F
	std::uint32_t aimassist_adspull_weaponclass;                // 0x0190, size 4
	float aimassist_adspull_zoomStart;                          // 0x0194, size 4
	float aimassist_adspull_zoomEnd;                            // 0x0198, size 4
	bool gamepad_use_yaw_speed_for_pitch_ads;                   // 0x019C, size 1
	bool allow_empty_fire;                                      // 0x019D, size 1
	bool allow_headshots;                                       // 0x019E, size 1
	bool npc_use_ads_move_speed_scale;                          // 0x019F, size 1
	bool locks_weapon_change;                                   // 0x01A0, size 1
	char unk_3[3];                                              // 0x01A1
	float ads_move_speed_scale;                                 // 0x01A4, size 4
	float move_speed_modifier;                                  // 0x01A8, size 4
	float move_speed_modifier_when_out_of_ammo;                 // 0x01AC, size 4
	bool offhand_blocks_sprint;                                 // 0x01B0, size 1
	char unk_4[3];                                              // 0x01B1
	float ads_fov_zoomfrac_start;                               // 0x01B4, size 4
	float ads_fov_zoomfrac_end;                                 // 0x01B8, size 4
	bool attack_button_presses_melee;                           // 0x01BC, size 1
	bool attack_button_presses_ads;                             // 0x01BD, size 1
	bool alt_fire_alternates_viewkick_yaw;                      // 0x01BE, size 1
	char unk_5[1];                                              // 0x01BF
	int offhand_default_inventory_slot;                         // 0x01C0, size 4
	int give_command_forced_inventory_slot;                     // 0x01C4, size 4
	std::uint32_t damage_flags;                                 // 0x01C8, size 4
	std::uint32_t explosion_damage_flags;                       // 0x01CC, size 4
	std::uint32_t weapon_type_flags;                            // 0x01D0, size 4
	int alt_fire_anim_count;                                    // 0x01D4, size 4
	float zoomfrac_autoattack;                                  // 0x01D8, size 4
	char unk_6[4];                                              // 0x01DC
	char const *alt_hand_3p_attach_name;                        // 0x01E0, size 8
	char const *activitymodifier1p;                             // 0x01E8, size 8
	char unk_7[8];                                              // 0x01F0
	char const *activitymodifier3p;                             // 0x01F8, size 8
	char unk_8[2];                                              // 0x0200
	bool ads_force_firstperson;                                 // 0x0202, size 1
	char unk_9[1];                                              // 0x0203
	vec3_t viewmodel_offset_hip;                           // 0x0204, size 12
	vec3_t viewmodel_offset_ads;                           // 0x0210, size 12
	float viewmodel_offset_zoom_frac_start;                     // 0x021C, size 4
	float viewmodel_offset_zoom_frac_end;                       // 0x0220, size 4
	float viewmodel_offset_offhand_scale;                       // 0x0224, size 4
	char const *viewmodel_ads_centerpoint_attachment;           // 0x0228, size 8
	char const *viewmodel_ads_rui_bottomleft_attachment;        // 0x0230, size 8
	bool viewmodel_offset_ads_by_centerpoint;                   // 0x0238, size 1
	char unk_10[3];                                             // 0x0239
	float melee_lunge_time;                                     // 0x023C, size 4
	float melee_lunge_target_range;                             // 0x0240, size 4
	float melee_lunge_target_angle;                             // 0x0244, size 4
	float melee_lunge_no_target_range;                          // 0x0248, size 4
	bool melee_can_hit_humansized;                              // 0x024C, size 1
	bool melee_can_hit_titans;                                  // 0x024D, size 1
	char unk_11[2];                                             // 0x024E
	int melee_damage;                                           // 0x0250, size 4
	int melee_damage_heavyarmor;                                // 0x0254, size 4
	float melee_knockback_velocity_magnitude;                   // 0x0258, size 4
	float melee_range;                                          // 0x025C, size 4
	float melee_angle;                                          // 0x0260, size 4
	char unk_12[4];                                             // 0x0264
	char const *melee_rumble_on_hit;                            // 0x0268, size 8
	char const *melee_rumble_on_hit_partial;                    // 0x0270, size 8
	float melee_freezelook_on_hit;                              // 0x0278, size 4
	float melee_attack_animtime;                                // 0x027C, size 4
	float melee_raise_recovery_animtime_normal;                 // 0x0280, size 4
	float melee_raise_recovery_animtime_quick;                  // 0x0284, size 4
	char const *melee_sound_attack_1p;                          // 0x0288, size 8
	char const *melee_sound_attack_3p;                          // 0x0290, size 8
	int melee_anim_1p_number;                                   // 0x0298, size 4
	char unk_13[4];                                             // 0x029C
	char const *melee_anim_3p;                                  // 0x02A0, size 8
	char const *fire_rumble;                                    // 0x02A8, size 8
	bool has_linked_anims;                                      // 0x02B0, size 1
	bool offhand_interupts_weapon_anims;                        // 0x02B1, size 1
	bool offhand_raise_is_interrupt_resumable;                  // 0x02B2, size 1
	bool offhand_hold_enabled;                                  // 0x02B3, size 1
	bool offhand_deploy_requires_input;                         // 0x02B4, size 1
	bool offhand_activates_on_zoom;                             // 0x02B5, size 1
	bool hide_holstered_sidearm_when_active;                    // 0x02B6, size 1
	bool offhand_transition_has_attach_detach_anim_events;      // 0x02B7, size 1
	bool offhand_toss_hold_is_resumable;                        // 0x02B8, size 1
	bool offhand_toss_activates_on_attack;                      // 0x02B9, size 1
	bool toss_has_post_loop;                                    // 0x02BA, size 1
	bool offhand_switch_on_attack;                              // 0x02BB, size 1
	bool offhand_hybrid_switch_on_attack;                       // 0x02BC, size 1
	bool offhand_hybrid_switch_on_lower;                        // 0x02BD, size 1
	bool offhand_hybrid_block_switch_if_empty;                  // 0x02BE, size 1
	bool offhand_hybrid_alt_hand_uses_attack_button;            // 0x02BF, size 1
	bool offhand_hybrid_tracks_projectiles;                     // 0x02C0, size 1
	bool offhand_hidden_for_fullscreen_ads;                     // 0x02C1, size 1
	bool offhand_uses_hud_ammo_status;                          // 0x02C2, size 1
	bool offhand_holds_on_tactical;                             // 0x02C3, size 1
	bool offhand_deactivate_on_jump_toggle_or_release;          // 0x02C4, size 1
	bool fire_in_real_world_while_phased;                       // 0x02C5, size 1
	bool fire_to_redirect_projectile_mid_flight;                // 0x02C6, size 1
	bool projectile_trail_start_from_origin;                    // 0x02C7, size 1
	float bolt_hitsize;                                         // 0x02C8, size 4
	float bolt_hitsize_grow1_time;                              // 0x02CC, size 4
	float bolt_hitsize_grow1_size;                              // 0x02D0, size 4
	float bolt_hitsize_grow2_time;                              // 0x02D4, size 4
	float bolt_hitsize_grow2_size;                              // 0x02D8, size 4
	float bolt_hitsize_growfinal_lerptime;                      // 0x02DC, size 4
	float bolt_hitsize_growfinal_size;                          // 0x02E0, size 4
	float bolt_bounce_frac;                                     // 0x02E4, size 4
	bool bolt_gravity_enabled;                                  // 0x02E8, size 1
	char unk_14[3];                                             // 0x02E9
	float bolt_zero_distance;                                   // 0x02EC, size 4
	int projectiles_per_shot;                                   // 0x02F0, size 4
	std::uint32_t blast_pattern;                                // 0x02F4, size 4
	float blast_pattern_default_scale;                          // 0x02F8, size 4
	float blast_pattern_npc_scale;                              // 0x02FC, size 4
	float blast_pattern_zero_distance;                          // 0x0300, size 4
	std::uint32_t ammo_suck_behavior;                           // 0x0304, size 4
	int ammo_clip_size;                                         // 0x0308, size 4
	int ammo_stockpile_max;                                     // 0x030C, size 4
	int ammo_default_total;                                     // 0x0310, size 4
	int ammo_clip_reload_max;                                   // 0x0314, size 4
	int ammo_per_shot;                                          // 0x0318, size 4
	int ammo_min_to_fire;                                       // 0x031C, size 4
	bool rapid_fire_overrides_min_ammo;                         // 0x0320, size 1
	char unk_15[3];                                             // 0x0321
	float ammo_clip_random_loss_on_npc_drop;                    // 0x0324, size 4
	int ammo_clip_random_loss_on_npc_drop_chunksize;            // 0x0328, size 4
	bool ammo_min_to_fire_autoreloads;                          // 0x032C, size 1
	char unk_16[3];                                             // 0x032D
	int ammo_size_segmented_reload;                             // 0x0330, size 4
	bool ammo_no_remove_from_clip;                              // 0x0334, size 1
	bool ammo_no_remove_from_stockpile;                         // 0x0335, size 1
	bool ammo_regen_takes_from_stockpile;                       // 0x0336, size 1
	bool ammo_display_as_clips;                                 // 0x0337, size 1
	bool ammo_drains_to_empty_on_fire;                          // 0x0338, size 1
	char unk_17[7];                                             // 0x0339
	char const *ammo_display;                                   // 0x0340, size 8
	bool uses_ammo_pool;                                        // 0x0348, size 1
	bool destroy_on_all_ammo_take;                              // 0x0349, size 1
	char unk_18[2];                                             // 0x034A
	float low_ammo_fraction;                                    // 0x034C, size 4
	int lifetime_shots_default;                                 // 0x0350, size 4
	float chance_for_bonus_last_shot_in_clip;                   // 0x0354, size 4
	float regen_ammo_refill_rate;                               // 0x0358, size 4
	float regen_ammo_refill_start_delay;                        // 0x035C, size 4
	float regen_ammo_stockpile_max_fraction;                    // 0x0360, size 4
	float regen_ammo_stockpile_drain_rate_when_charging;        // 0x0364, size 4
	bool regen_ammo_while_firing;                               // 0x0368, size 1
	char unk_19[3];                                             // 0x0369
	int regen_ammo_sound_range_start_1;                         // 0x036C, size 4
	int regen_ammo_sound_range_start_2;                         // 0x0370, size 4
	int regen_ammo_sound_range_start_3;                         // 0x0374, size 4
	char const *regen_ammo_sound_range_name_1;                  // 0x0378, size 8
	char const *regen_ammo_sound_range_name_2;                  // 0x0380, size 8
	char const *regen_ammo_sound_range_name_3;                  // 0x0388, size 8
	int shared_energy_cost;                                     // 0x0390, size 4
	int shared_energy_charge_cost;                              // 0x0394, size 4
	float damage_near_distance;                                 // 0x0398, size 4
	float damage_far_distance;                                  // 0x039C, size 4
	float damage_very_far_distance;                             // 0x03A0, size 4
	float damage_inverse_distance;                              // 0x03A4, size 4
	int damage_near_value;                                      // 0x03A8, size 4
	int damage_near_value_titanarmor;                           // 0x03AC, size 4
	int damage_far_value;                                       // 0x03B0, size 4
	int damage_far_value_titanarmor;                            // 0x03B4, size 4
	int damage_very_far_value;                                  // 0x03B8, size 4
	int damage_very_far_value_titanarmor;                       // 0x03BC, size 4
	int damage_rodeo;                                           // 0x03C0, size 4
	int damage_additional_bullets;                              // 0x03C4, size 4
	int damage_additional_bullets_titanarmor;                   // 0x03C8, size 4
	float damage_headshot_scale;                                // 0x03CC, size 4
	float damage_unshielded_scale;                              // 0x03D0, size 4
	float damage_shield_scale;                                  // 0x03D4, size 4
	int pass_through_depth;                                     // 0x03D8, size 4
	float pass_through_damage_preserved_scale;                  // 0x03DC, size 4
	int explosion_damage;                                       // 0x03E0, size 4
	int explosion_damage_heavy_armor;                           // 0x03E4, size 4
	int npc_explosion_damage;                                   // 0x03E8, size 4
	int npc_explosion_damage_heavy_armor;                       // 0x03EC, size 4
	float impulse_force;                                        // 0x03F0, size 4
	float impulse_force_explosions;                             // 0x03F4, size 4
	bool critical_hit;                                          // 0x03F8, size 1
	char unk_20[3];                                             // 0x03F9
	float critical_hit_damage_scale;                            // 0x03FC, size 4
	bool titanarmor_critical_hit_required;                      // 0x0400, size 1
	char unk_21[3];                                             // 0x0401
	float explosion_inner_radius;                               // 0x0404, size 4
	float explosionradius;                                      // 0x0408, size 4
	bool explosion_damages_owner;                               // 0x040C, size 1
	char unk_22[3];                                             // 0x040D
	float grenade_bounce_vel_frac_shallow;                      // 0x0410, size 4
	float grenade_bounce_vel_frac_sharp;                        // 0x0414, size 4
	float grenade_bounce_vel_frac_along_normal;                 // 0x0418, size 4
	float grenade_bounce_randomness;                            // 0x041C, size 4
	float grenade_bounce_extra_vertical_randomness;             // 0x0420, size 4
	bool grenade_can_roll;                                      // 0x0424, size 1
	char unk_23[3];                                             // 0x0425
	float grenade_roll_vel_frac_per_second;                     // 0x0428, size 4
	float grenade_radius_vertical;                              // 0x042C, size 4
	float grenade_radius_horizontal;                            // 0x0430, size 4
	vec3_t grenade_hull_mins;                              // 0x0434, size 12
	vec3_t grenade_hull_maxs;                              // 0x0440, size 12
	vec3_t grenade_view_launch_offset;                     // 0x044C, size 12
	float grenade_fuse_time;                                    // 0x0458, size 4
	float grenade_ignition_time;                                // 0x045C, size 4
	bool grenade_orient_to_velocity;                            // 0x0460, size 1
	bool grenade_arc_indicator_show_from_hip;                   // 0x0461, size 1
	bool grenade_arc_indicator_show_on_raise_if_ready;          // 0x0462, size 1
	bool grenade_arc_indicator_show_in_sprint_if_ready;         // 0x0463, size 1
	bool grenade_arc_indicator_show_during_toss;                // 0x0464, size 1
	bool grenade_arc_indicator_show_while_airborne;             // 0x0465, size 1
	char unk_24[2];                                             // 0x0466
	float grenade_arc_indicator_max_duration;                   // 0x0468, size 4
	int grenade_arc_indicator_bounce_count;                     // 0x046C, size 4
	bool grenade_arc_indicator_ignore_base_velocity;            // 0x0470, size 1
	bool grenade_arc_indicator_show_landing_position;           // 0x0471, size 1
	bool grenade_arc_indicator_smooth;                          // 0x0472, size 1
	char unk_25[1];                                             // 0x0473
	float grenade_arc_indicator_smooth_radius;                  // 0x0474, size 4
	float grenade_death_drop_velocity_scale;                    // 0x0478, size 4
	float grenade_death_drop_velocity_extraUp;                  // 0x047C, size 4
	bool grenade_touch_triggers_on_impact;                      // 0x0480, size 1
	bool grenade_ignore_friendly_players;                       // 0x0481, size 1
	bool grenade_use_mask_ability;                              // 0x0482, size 1
	bool grenade_mover_destroy_when_planted;                    // 0x0483, size 1
	bool grenade_drop_to_ground_on_bounce;                      // 0x0484, size 1
	char unk_26[3];                                             // 0x0485
	float grenade_drop_to_ground_bounce_vel_frac;               // 0x0488, size 4
	float grenade_drop_velocity;                                // 0x048C, size 4
	bool show_grenade_indicator;                                // 0x0490, size 1
	bool show_grenade_indicator_to_owner;                       // 0x0491, size 1
	char unk_27[2];                                             // 0x0492
	float projectile_inherit_owner_velocity_scale;              // 0x0494, size 4
	float projectile_inherit_base_velocity_scale;               // 0x0498, size 4
	float projectile_first_person_offset_fraction;              // 0x049C, size 4
	float projectile_launch_speed;                              // 0x04A0, size 4
	float projectile_launch_pitch_offset;                       // 0x04A4, size 4
	float projectile_gravity_scale;                             // 0x04A8, size 4
	float projectile_air_friction;                              // 0x04AC, size 4
	float projectile_drag_coefficient;                          // 0x04B0, size 4
	int projectile_max_deployed;                                // 0x04B4, size 4
	float projectile_gravity_scale_time_2;                      // 0x04B8, size 4
	float projectile_gravity_scale_2;                           // 0x04BC, size 4
	float projectile_air_friction_2;                            // 0x04C0, size 4
	float projectile_gravity_scale_time_final;                  // 0x04C4, size 4
	float projectile_gravity_scale_final;                       // 0x04C8, size 4
	float projectile_air_friction_final;                        // 0x04CC, size 4
	float explosion_shake_radius;                               // 0x04D0, size 4
	float explosion_shake_amplitude;                            // 0x04D4, size 4
	float explosion_shake_frequency;                            // 0x04D8, size 4
	float explosion_shake_duration;                             // 0x04DC, size 4
	float reload_time;                                          // 0x04E0, size 4
	float reload_time_late1;                                    // 0x04E4, size 4
	float reload_time_late2;                                    // 0x04E8, size 4
	float reload_time_late3;                                    // 0x04EC, size 4
	float reload_time_late4;                                    // 0x04F0, size 4
	float reload_time_late5;                                    // 0x04F4, size 4
	float reloadempty_time;                                     // 0x04F8, size 4
	float reloadempty_time_late1;                               // 0x04FC, size 4
	float reloadempty_time_late2;                               // 0x0500, size 4
	float reloadempty_time_late3;                               // 0x0504, size 4
	float reloadempty_time_late4;                               // 0x0508, size 4
	float reloadempty_time_late5;                               // 0x050C, size 4
	float reloadsegment_time_loop;                              // 0x0510, size 4
	float reloadsegment_time_end;                               // 0x0514, size 4
	float reloadsegmentempty_time_end;                          // 0x0518, size 4
	bool reload_is_segmented;                                   // 0x051C, size 1
	bool reload_allow_ads;                                      // 0x051D, size 1
	bool reload_no_auto_if_ads_pressed;                         // 0x051E, size 1
	bool reload_alt_anim;                                       // 0x051F, size 1
	bool auto_reload_no_ammo;                                   // 0x0520, size 1
	bool disable_zoomed_rechamber;                              // 0x0521, size 1
	bool enable_highlight_networking_on_creation;               // 0x0522, size 1
	char unk_28[1];                                             // 0x0523
	float rechamber_time;                                       // 0x0524, size 4
	float rechamber_time_late1;                                 // 0x0528, size 4
	float rechamber_time_late2;                                 // 0x052C, size 4
	float rechamber_time_late3;                                 // 0x0530, size 4
	float vortex_drain;                                         // 0x0534, size 4
	float charge_time;                                          // 0x0538, size 4
	float charge_cooldown_time;                                 // 0x053C, size 4
	float charge_cooldown_delay;                                // 0x0540, size 4
	float charge_overheat_cooldown_time;                        // 0x0544, size 4
	float charge_overheat_cooldown_time_late1;                  // 0x0548, size 4
	float charge_overheat_cooldown_time_late2;                  // 0x054C, size 4
	float charge_overheat_cooldown_time_late3;                  // 0x0550, size 4
	float charge_overheat_cooldown_delay;                       // 0x0554, size 4
	float charge_attack_min_charge_required;                    // 0x0558, size 4
	int charge_levels;                                          // 0x055C, size 4
	int charge_level_base;                                      // 0x0560, size 4
	bool charge_is_triggered_by_ADS;                            // 0x0564, size 1
	char unk_29[3];                                             // 0x0565
	float charge_delay_when_triggered_by_ADS;                   // 0x0568, size 4
	bool charge_require_input;                                  // 0x056C, size 1
	bool charge_allow_midway_charge;                            // 0x056D, size 1
	bool charge_allow_melee;                                    // 0x056E, size 1
	bool charge_end_forces_fire;                                // 0x056F, size 1
	bool charge_maintained_until_fired;                         // 0x0570, size 1
	bool charge_remain_full_when_fired;                         // 0x0571, size 1
	bool charge_overheats_when_full;                            // 0x0572, size 1
	bool charge_allow_hold_when_full;                           // 0x0573, size 1
	bool charge_weapon_fires_while_charging;                    // 0x0574, size 1
	bool charge_fraction_scales_anim_rate;                      // 0x0575, size 1
	bool charge_finish_primary_attack_on_cancel;                // 0x0576, size 1
	char unk_30[1];                                             // 0x0577
	float charge_additional_damage_multiplier;                  // 0x0578, size 4
	char unk_31[4];                                             // 0x057C
	char const *charge_sound_1p;                                // 0x0580, size 8
	char const *charge_sound_3p;                                // 0x0588, size 8
	char const *charge_full_sound_1p;                           // 0x0590, size 8
	char const *charge_full_sound_3p;                           // 0x0598, size 8
	char const *charge_drain_sound_1p;                          // 0x05A0, size 8
	char const *charge_drain_sound_3p;                          // 0x05A8, size 8
	bool charge_sound_stop_when_full;                           // 0x05B0, size 1
	bool charge_sound_seek_to_charge_fraction;                  // 0x05B1, size 1
	bool charge_drain_sound_stop_when_empty;                    // 0x05B2, size 1
	bool charge_drain_sound_seek_to_charge_fraction;            // 0x05B3, size 1
	char unk_32[4];                                             // 0x05B4
	char const *charge_effect_attachment;                       // 0x05B8, size 8
	char const *charge_effect2_attachment;                      // 0x05C0, size 8
	char const *charge_effect_attachment_scoped;                // 0x05C8, size 8
	char const *charge_effect2_attachment_scoped;               // 0x05D0, size 8
	bool charge_effect_show_during_drain;                       // 0x05D8, size 1
	char unk_33[3];                                             // 0x05D9
	int charge_rumble_min;                                      // 0x05DC, size 4
	int charge_rumble_max;                                      // 0x05E0, size 4
	char unk_34[4];                                             // 0x05E4
	std::uint64_t player_hands_effect;                          // 0x05E8, size 8
	char const *player_hands_attachment;                        // 0x05F0, size 8
	float core_duration;                                        // 0x05F8, size 4
	float core_build_time;                                      // 0x05FC, size 4
	float sustained_discharge_duration;                         // 0x0600, size 4
	bool sustained_discharge_require_input;                     // 0x0604, size 1
	bool sustained_discharge_allow_melee;                       // 0x0605, size 1
	char unk_35[2];                                             // 0x0606
	float sustained_discharge_pulse_frequency;                  // 0x0608, size 4
	bool sustained_discharge_want_pulse_callbacks;              // 0x060C, size 1
	bool sustained_discharge_updates_charge;                    // 0x060D, size 1
	bool sustained_discharge_ends_in_primary_attack;            // 0x060E, size 1
	bool sustained_laser_enabled;                               // 0x060F, size 1
	float sustained_laser_radius;                               // 0x0610, size 4
	int sustained_laser_radial_iterations;                      // 0x0614, size 4
	int sustained_laser_radial_step;                            // 0x0618, size 4
	float sustained_laser_range;                                // 0x061C, size 4
	char const *sustained_laser_attachment;                     // 0x0620, size 8
	char const *sustained_laser_attachment_scoped;              // 0x0628, size 8
	bool sustained_laser_effect_loops;                          // 0x0630, size 1
	bool sustained_laser_impact_effect_loops;                   // 0x0631, size 1
	char unk_36[2];                                             // 0x0632
	float sustained_laser_impact_distance;                      // 0x0634, size 4
	bool sustained_laser_use_deferred_traces;                   // 0x0638, size 1
	char unk_37[3];                                             // 0x0639
	float sustained_laser_damage_scale;                         // 0x063C, size 4
	std::uint32_t sustained_laser_spread_pattern;               // 0x0640, size 4
	bool targeting_laser_enabled;                               // 0x0644, size 1
	char unk_38[3];                                             // 0x0645
	char const *targeting_laser_attachment_1p;                  // 0x0648, size 8
	char const *targeting_laser_attachment_3p;                  // 0x0650, size 8
	float targeting_laser_range;                                // 0x0658, size 4
	vec3_t holster_offset;                                 // 0x065C, size 12
	float holster_time;                                         // 0x0668, size 4
	float deploy_time;                                          // 0x066C, size 4
	float deployfirst_time;                                     // 0x0670, size 4
	float deploycatch_time;                                     // 0x0674, size 4
	float lower_time;                                           // 0x0678, size 4
	float raise_time;                                           // 0x067C, size 4
	float raise_from_sprint_time;                               // 0x0680, size 4
	float sprintcycle_time;                                     // 0x0684, size 4
	bool sprint_fractional_anims;                               // 0x0688, size 1
	char unk_39[3];                                             // 0x0689
	float tossholdsprintcycle_time;                             // 0x068C, size 4
	float max_cook_time;                                        // 0x0690, size 4
	float toss_time;                                            // 0x0694, size 4
	float toss_overhead_time;                                   // 0x0698, size 4
	float toss_pullout_time;                                    // 0x069C, size 4
	float cooldown_time;                                        // 0x06A0, size 4
	std::uint32_t viewkick_spring;                              // 0x06A4, size 4
	std::uint32_t viewkick_spring_hot;                          // 0x06A8, size 4
	float viewkick_spring_heatpershot;                          // 0x06AC, size 4
	float viewkick_spring_cooldown_holdtime;                    // 0x06B0, size 4
	float viewkick_spring_cooldown_fadetime;                    // 0x06B4, size 4
	std::uint32_t viewmodel_spring_jolt;                        // 0x06B8, size 4
	float viewmodel_jolt_scale;                                 // 0x06BC, size 4
	float viewmodel_jolt_backwardPerShot;                       // 0x06C0, size 4
	vec3_t viewmodel_jolt_side;                            // 0x06C4, size 12
	vec3_t viewmodel_jolt_roll;                            // 0x06D0, size 12
	float viewkick_spring_velocityScalePerShot;                 // 0x06DC, size 4
	std::uint32_t viewkick_pattern;                             // 0x06E0, size 4
	float viewkick_pitch_base;                                  // 0x06E4, size 4
	float viewkick_pitch_random;                                // 0x06E8, size 4
	float viewkick_pitch_random_innerexclude;                   // 0x06EC, size 4
	float viewkick_pitch_softScale;                             // 0x06F0, size 4
	float viewkick_pitch_hardScale;                             // 0x06F4, size 4
	float viewkick_yaw_base;                                    // 0x06F8, size 4
	float viewkick_yaw_random;                                  // 0x06FC, size 4
	float viewkick_yaw_random_innerexclude;                     // 0x0700, size 4
	float viewkick_yaw_softScale;                               // 0x0704, size 4
	float viewkick_yaw_hardScale;                               // 0x0708, size 4
	float viewkick_roll_base;                                   // 0x070C, size 4
	float viewkick_roll_randomMin;                              // 0x0710, size 4
	float viewkick_roll_randomMax;                              // 0x0714, size 4
	float viewkick_roll_softScale;                              // 0x0718, size 4
	float viewkick_roll_hardScale;                              // 0x071C, size 4
	float viewkick_hipfire_weaponFraction;                      // 0x0720, size 4
	float viewkick_hipfire_weaponFraction_vmScale;              // 0x0724, size 4
	float viewkick_ads_weaponFraction;                          // 0x0728, size 4
	float viewkick_ads_weaponFraction_vmScale;                  // 0x072C, size 4
	float viewkick_scale_firstshot_hipfire;                     // 0x0730, size 4
	float viewkick_scale_firstshot_ads;                         // 0x0734, size 4
	float viewkick_scale_min_hipfire;                           // 0x0738, size 4
	float viewkick_scale_max_hipfire;                           // 0x073C, size 4
	float viewkick_scale_min_ads;                               // 0x0740, size 4
	float viewkick_scale_max_ads;                               // 0x0744, size 4
	float viewkick_scale_valuePerShot;                          // 0x0748, size 4
	float viewkick_pattern_valuePerShot;                        // 0x074C, size 4
	float viewkick_scale_pitch_valueLerpStart;                  // 0x0750, size 4
	float viewkick_scale_yaw_valueLerpStart;                    // 0x0754, size 4
	float viewkick_scale_pitch_valueLerpEnd;                    // 0x0758, size 4
	float viewkick_scale_yaw_valueLerpEnd;                      // 0x075C, size 4
	float viewkick_scale_valueDecayDelay;                       // 0x0760, size 4
	float viewkick_scale_valueDecayRate;                        // 0x0764, size 4
	float viewkick_duck_scale;                                  // 0x0768, size 4
	float viewkick_hover_scale;                                 // 0x076C, size 4
	float viewkick_move_scale;                                  // 0x0770, size 4
	float viewkick_air_scale_ads;                               // 0x0774, size 4
	float viewkick_perm_pitch_base;                             // 0x0778, size 4
	float viewkick_perm_pitch_random;                           // 0x077C, size 4
	float viewkick_perm_pitch_random_innerexclude;              // 0x0780, size 4
	float viewkick_perm_yaw_base;                               // 0x0784, size 4
	float viewkick_perm_yaw_random;                             // 0x0788, size 4
	float viewkick_perm_yaw_random_innerexclude;                // 0x078C, size 4
	float viewkick_pc_yaw_scale;                                // 0x0790, size 4
	float viewkick_pc_pitch_scale;                              // 0x0794, size 4
	float cooldown_viewkick_pitch_base;                         // 0x0798, size 4
	float cooldown_viewkick_pitch_random;                       // 0x079C, size 4
	float cooldown_viewkick_pitch_random_innerexclude;          // 0x07A0, size 4
	float cooldown_viewkick_yaw_base;                           // 0x07A4, size 4
	float cooldown_viewkick_yaw_random;                         // 0x07A8, size 4
	float cooldown_viewkick_yaw_random_innerexclude;            // 0x07AC, size 4
	float cooldown_viewkick_softScale;                          // 0x07B0, size 4
	float cooldown_viewkick_hardScale;                          // 0x07B4, size 4
	float cooldown_viewkick_adsScale;                           // 0x07B8, size 4
	float viewdrift_hipfire_stand_scale_pitch;                  // 0x07BC, size 4
	float viewdrift_hipfire_crouch_scale_pitch;                 // 0x07C0, size 4
	float viewdrift_hipfire_air_scale_pitch;                    // 0x07C4, size 4
	float viewdrift_hipfire_speed_pitch;                        // 0x07C8, size 4
	float viewdrift_hipfire_stand_scale_yaw;                    // 0x07CC, size 4
	float viewdrift_hipfire_crouch_scale_yaw;                   // 0x07D0, size 4
	float viewdrift_hipfire_air_scale_yaw;                      // 0x07D4, size 4
	float viewdrift_hipfire_speed_yaw;                          // 0x07D8, size 4
	float viewdrift_ads_stand_scale_pitch;                      // 0x07DC, size 4
	float viewdrift_ads_crouch_scale_pitch;                     // 0x07E0, size 4
	float viewdrift_ads_air_scale_pitch;                        // 0x07E4, size 4
	float viewdrift_ads_speed_pitch;                            // 0x07E8, size 4
	float viewdrift_ads_stand_scale_yaw;                        // 0x07EC, size 4
	float viewdrift_ads_crouch_scale_yaw;                       // 0x07F0, size 4
	float viewdrift_ads_air_scale_yaw;                          // 0x07F4, size 4
	float viewdrift_ads_speed_yaw;                              // 0x07F8, size 4
	float viewdrift_ads_delay;                                  // 0x07FC, size 4
	float spread_stand_hip;                                     // 0x0800, size 4
	float spread_stand_hip_run;                                 // 0x0804, size 4
	float spread_stand_hip_sprint;                              // 0x0808, size 4
	float spread_stand_ads;                                     // 0x080C, size 4
	float spread_crouch_hip;                                    // 0x0810, size 4
	float spread_crouch_ads;                                    // 0x0814, size 4
	float spread_air_hip;                                       // 0x0818, size 4
	float spread_air_ads;                                       // 0x081C, size 4
	float spread_wallrunning;                                   // 0x0820, size 4
	float spread_wallhanging;                                   // 0x0824, size 4
	float spread_moving_decay_rate;                             // 0x0828, size 4
	float spread_moving_increase_rate;                          // 0x082C, size 4
	float npc_attack_cone_angle;                                // 0x0830, size 4
	float spread_kick_on_fire_stand_hip;                        // 0x0834, size 4
	float spread_kick_on_fire_stand_ads;                        // 0x0838, size 4
	float spread_kick_on_fire_crouch_hip;                       // 0x083C, size 4
	float spread_kick_on_fire_crouch_ads;                       // 0x0840, size 4
	float spread_kick_on_fire_air_hip;                          // 0x0844, size 4
	float spread_kick_on_fire_air_ads;                          // 0x0848, size 4
	float spread_min_kick;                                      // 0x084C, size 4
	float spread_max_kick_stand_hip;                            // 0x0850, size 4
	float spread_max_kick_stand_ads;                            // 0x0854, size 4
	float spread_max_kick_crouch_hip;                           // 0x0858, size 4
	float spread_max_kick_crouch_ads;                           // 0x085C, size 4
	float spread_max_kick_air_hip;                              // 0x0860, size 4
	float spread_max_kick_air_ads;                              // 0x0864, size 4
	float spread_decay_rate;                                    // 0x0868, size 4
	float spread_decay_delay;                                   // 0x086C, size 4
	float spread_time_to_max;                                   // 0x0870, size 4
	bool primary_attack_ignores_spread;                         // 0x0874, size 1
	char unk_40[11];                                            // 0x0875
	bool looping_sounds;                                        // 0x0880, size 1
	char unk_41[7];                                             // 0x0881
	char const *readymessage;                                   // 0x0888, size 8
	char const *readyhint;                                      // 0x0890, size 8
	char const *fire_sound_1;                                   // 0x0898, size 8
	char const *fire_sound_2;                                   // 0x08A0, size 8
	char const *fire_sound_3;                                   // 0x08A8, size 8
	char const *fire_sound_first_shot;                          // 0x08B0, size 8
	char const *fire_sound_1_npc;                               // 0x08B8, size 8
	char const *fire_sound_2_npc;                               // 0x08C0, size 8
	char const *fire_sound_3_npc;                               // 0x08C8, size 8
	char const *fire_sound_first_shot_npc;                      // 0x08D0, size 8
	char const *fire_sound_1_player_1p;                         // 0x08D8, size 8
	char const *fire_sound_2_player_1p;                         // 0x08E0, size 8
	char const *fire_sound_3_player_1p;                         // 0x08E8, size 8
	char const *fire_sound_first_shot_player_1p;                // 0x08F0, size 8
	char const *fire_sound_1_player_3p;                         // 0x08F8, size 8
	char const *fire_sound_2_player_3p;                         // 0x0900, size 8
	char const *fire_sound_3_player_3p;                         // 0x0908, size 8
	char const *fire_sound_first_shot_player_3p;                // 0x0910, size 8
	char const *fire_sound_partial_burst_player_1p;             // 0x0918, size 8
	char const *fire_sound_partial_burst_player_3p;             // 0x0920, size 8
	char const *burst_or_looping_fire_sound_start;              // 0x0928, size 8
	char const *burst_or_looping_fire_sound_middle;             // 0x0930, size 8
	char const *burst_or_looping_fire_sound_end;                // 0x0938, size 8
	char const *burst_or_looping_fire_sound_start_npc;          // 0x0940, size 8
	char const *burst_or_looping_fire_sound_resume_npc;         // 0x0948, size 8
	char const *burst_or_looping_fire_sound_middle_npc;         // 0x0950, size 8
	char const *burst_or_looping_fire_sound_end_npc;            // 0x0958, size 8
	char const *burst_or_looping_fire_sound_start_1p;           // 0x0960, size 8
	char const *burst_or_looping_fire_sound_resume_1p;          // 0x0968, size 8
	char const *burst_or_looping_fire_sound_middle_1p;          // 0x0970, size 8
	char const *burst_or_looping_fire_sound_end_1p;             // 0x0978, size 8
	char const *burst_or_looping_fire_sound_start_3p;           // 0x0980, size 8
	char const *burst_or_looping_fire_sound_resume_3p;          // 0x0988, size 8
	char const *burst_or_looping_fire_sound_middle_3p;          // 0x0990, size 8
	char const *burst_or_looping_fire_sound_end_3p;             // 0x0998, size 8
	char const *idle_sound_player_1p;                           // 0x09A0, size 8
	char const *low_ammo_sound_name_1;                          // 0x09A8, size 8
	char const *low_ammo_sound_name_2;                          // 0x09B0, size 8
	char const *low_ammo_sound_name_3;                          // 0x09B8, size 8
	char const *low_ammo_sound_name_4;                          // 0x09C0, size 8
	char const *low_ammo_sound_name_5;                          // 0x09C8, size 8
	char const *low_ammo_sound_name_6;                          // 0x09D0, size 8
	char const *low_ammo_sound_name_7;                          // 0x09D8, size 8
	char const *low_ammo_sound_name_8;                          // 0x09E0, size 8
	char const *low_ammo_sound_name_9;                          // 0x09E8, size 8
	char const *low_ammo_sound_name_10;                         // 0x09F0, size 8
	char const *low_ammo_sound_name_11;                         // 0x09F8, size 8
	char const *low_ammo_sound_name_12;                         // 0x0A00, size 8
	char const *low_ammo_sound_name_13;                         // 0x0A08, size 8
	char const *low_ammo_sound_name_14;                         // 0x0A10, size 8
	char const *low_ammo_sound_name_15;                         // 0x0A18, size 8
	int low_ammo_sound_range_start_1;                           // 0x0A20, size 4
	int low_ammo_sound_range_start_2;                           // 0x0A24, size 4
	int low_ammo_sound_range_start_3;                           // 0x0A28, size 4
	char unk_42[4];                                             // 0x0A2C
	char const *low_ammo_sound_range_name_1;                    // 0x0A30, size 8
	char const *low_ammo_sound_range_name_2;                    // 0x0A38, size 8
	char const *low_ammo_sound_range_name_3;                    // 0x0A40, size 8
	int body_skin;                                              // 0x0A48, size 4
	int bodygroup1_set;                                         // 0x0A4C, size 4
	int bodygroup2_set;                                         // 0x0A50, size 4
	int bodygroup3_set;                                         // 0x0A54, size 4
	int bodygroup4_set;                                         // 0x0A58, size 4
	int bodygroup5_set;                                         // 0x0A5C, size 4
	int bodygroup6_set;                                         // 0x0A60, size 4
	int bodygroup7_set;                                         // 0x0A64, size 4
	int bodygroup8_set;                                         // 0x0A68, size 4
	int bodygroup9_set;                                         // 0x0A6C, size 4
	int bodygroup10_set;                                        // 0x0A70, size 4
	int bodygroup11_set;                                        // 0x0A74, size 4
	int bodygroup12_set;                                        // 0x0A78, size 4
	int bodygroup13_set;                                        // 0x0A7C, size 4
	int bodygroup14_set;                                        // 0x0A80, size 4
	int bodygroup15_set;                                        // 0x0A84, size 4
	int bodygroup16_set;                                        // 0x0A88, size 4
	int bodygroup17_set;                                        // 0x0A8C, size 4
	int bodygroup18_set;                                        // 0x0A90, size 4
	int bodygroup19_set;                                        // 0x0A94, size 4
	int bodygroup20_set;                                        // 0x0A98, size 4
	int bodygroup21_set;                                        // 0x0A9C, size 4
	int bodygroup22_set;                                        // 0x0AA0, size 4
	int bodygroup23_set;                                        // 0x0AA4, size 4
	int bodygroup24_set;                                        // 0x0AA8, size 4
	int bodygroup25_set;                                        // 0x0AAC, size 4
	int bodygroup26_set;                                        // 0x0AB0, size 4
	int bodygroup27_set;                                        // 0x0AB4, size 4
	int bodygroup28_set;                                        // 0x0AB8, size 4
	int bodygroup29_set;                                        // 0x0ABC, size 4
	int bodygroup30_set;                                        // 0x0AC0, size 4
	int bodygroup31_set;                                        // 0x0AC4, size 4
	int bodygroup32_set;                                        // 0x0AC8, size 4
	int bodygroup_ads_scope_set;                                // 0x0ACC, size 4
	int bodygroup_ammo_index_count;                             // 0x0AD0, size 4
	int zoomed_convar_sensitivity_index;                        // 0x0AD4, size 4
	int zoomed_convar_toggle_sensitivity_index;                 // 0x0AD8, size 4
	int npc_min_burst;                                          // 0x0ADC, size 4
	int npc_max_burst;                                          // 0x0AE0, size 4
	int npc_min_burst_min_precision;                            // 0x0AE4, size 4
	int npc_max_burst_min_precision;                            // 0x0AE8, size 4
	int npc_min_burst_max_precision;                            // 0x0AEC, size 4
	int npc_max_burst_max_precision;                            // 0x0AF0, size 4
	bool npc_refresh_burst_location_per_shot;                   // 0x0AF4, size 1
	char unk_43[3];                                             // 0x0AF5
	int npc_burst_secondary;                                    // 0x0AF8, size 4
	bool npc_miss_fast_player;                                  // 0x0AFC, size 1
	bool npc_full_auto_vs_heavy_armor;                          // 0x0AFD, size 1
	bool npc_use_strict_muzzle_dir;                             // 0x0AFE, size 1
	bool npc_aim_at_feet;                                       // 0x0AFF, size 1
	bool npc_aim_at_feet_vs_heavy_armor;                        // 0x0B00, size 1
	bool npc_vortex_block;                                      // 0x0B01, size 1
	bool npc_self_explosion_safety;                             // 0x0B02, size 1
	bool npc_dangerous_to_normal_armor;                         // 0x0B03, size 1
	bool npc_dangerous_to_heavy_armor;                          // 0x0B04, size 1
	bool npc_suppress_lsp_allowed;                              // 0x0B05, size 1
	bool npc_suppress_abs_position;                             // 0x0B06, size 1
	bool npc_clear_charge_if_not_fired;                         // 0x0B07, size 1
	bool npc_lead_projectiles;                                  // 0x0B08, size 1
	bool npc_compensate_gravity;                                // 0x0B09, size 1
	char unk_44[2];                                             // 0x0B0A
	float npc_lead_projectiles_fraction_min_precision;          // 0x0B0C, size 4
	float npc_lead_projectiles_fraction_max_precision;          // 0x0B10, size 4
	float npc_rest_time_between_bursts_min;                     // 0x0B14, size 4
	float npc_rest_time_between_bursts_max;                     // 0x0B18, size 4
	float npc_min_rest_time_between_bursts_min_precision;       // 0x0B1C, size 4
	float npc_max_rest_time_between_bursts_min_precision;       // 0x0B20, size 4
	float npc_min_rest_time_between_bursts_max_precision;       // 0x0B24, size 4
	float npc_max_rest_time_between_bursts_max_precision;       // 0x0B28, size 4
	float npc_charge_time_min;                                  // 0x0B2C, size 4
	float npc_charge_time_max;                                  // 0x0B30, size 4
	float npc_min_range;                                        // 0x0B34, size 4
	float npc_max_range;                                        // 0x0B38, size 4
	float npc_min_range_secondary;                              // 0x0B3C, size 4
	float npc_max_range_secondary;                              // 0x0B40, size 4
	float npc_damage_near_distance;                             // 0x0B44, size 4
	float npc_damage_far_distance;                              // 0x0B48, size 4
	float npc_damage_very_far_distance;                         // 0x0B4C, size 4
	int npc_damage_near_value;                                  // 0x0B50, size 4
	int npc_damage_near_value_titanarmor;                       // 0x0B54, size 4
	int npc_damage_far_value;                                   // 0x0B58, size 4
	int npc_damage_far_value_titanarmor;                        // 0x0B5C, size 4
	int npc_damage_very_far_value;                              // 0x0B60, size 4
	int npc_damage_very_far_value_titanarmor;                   // 0x0B64, size 4
	float npc_min_engage_range;                                 // 0x0B68, size 4
	float npc_max_engage_range;                                 // 0x0B6C, size 4
	float npc_min_engage_range_heavy_armor;                     // 0x0B70, size 4
	float npc_max_engage_range_heavy_armor;                     // 0x0B74, size 4
	float npc_rest_time_between_bursts_expedite;                // 0x0B78, size 4
	float npc_rest_time_secondary;                              // 0x0B7C, size 4
	float npc_pre_fire_delay;                                   // 0x0B80, size 4
	float npc_pre_fire_delay_interval;                          // 0x0B84, size 4
	float npc_directed_fire_ang_limit;                          // 0x0B88, size 4
	float npc_fire_at_enemy_defense_time;                       // 0x0B8C, size 4
	int npc_reload_enabled;                                     // 0x0B90, size 4
	float npc_accuracy_multiplier_heavy_armor;                  // 0x0B94, size 4
	float npc_accuracy_multiplier_pilot;                        // 0x0B98, size 4
	float npc_accuracy_multiplier_npc;                          // 0x0B9C, size 4
	float npc_use_short_duration;                               // 0x0BA0, size 4
	float npc_use_long_duration;                                // 0x0BA4, size 4
	float npc_use_min_damage;                                   // 0x0BA8, size 4
	float npc_use_max_damage;                                   // 0x0BAC, size 4
	float npc_use_min_projectile_damage;                        // 0x0BB0, size 4
	float npc_lob_shot_pitch;                                   // 0x0BB4, size 4
	float npc_burst_radius_min_precision;                       // 0x0BB8, size 4
	float npc_burst_radius_max_precision;                       // 0x0BBC, size 4
	float npc_burst_radius_distribution_bias_min_precision;     // 0x0BC0, size 4
	float npc_burst_radius_distribution_bias_max_precision;     // 0x0BC4, size 4
	float npc_spread_cone_min_precision;                        // 0x0BC8, size 4
	float npc_spread_cone_max_precision;                        // 0x0BCC, size 4
	float npc_spread_cone_distribution_bias_min_precision;      // 0x0BD0, size 4
	float npc_spread_cone_distribution_bias_max_precision;      // 0x0BD4, size 4
	float npc_spread_cone_focus_time;                           // 0x0BD8, size 4
	float npc_spread_defocused_cone_multiplier;                 // 0x0BDC, size 4
	float npc_spread_pattern_focus_time;                        // 0x0BE0, size 4
	float npc_spread_pattern_not_in_fov_time;                   // 0x0BE4, size 4
	float npc_spread_pattern_not_in_fov_factor;                 // 0x0BE8, size 4
	float proficiency_poor_spreadscale;                         // 0x0BEC, size 4
	float proficiency_poor_bias;                                // 0x0BF0, size 4
	float proficiency_poor_additional_rest;                     // 0x0BF4, size 4
	float proficiency_average_spreadscale;                      // 0x0BF8, size 4
	float proficiency_average_bias;                             // 0x0BFC, size 4
	float proficiency_average_additional_rest;                  // 0x0C00, size 4
	float proficiency_good_spreadscale;                         // 0x0C04, size 4
	float proficiency_good_bias;                                // 0x0C08, size 4
	float proficiency_good_additional_rest;                     // 0x0C0C, size 4
	float proficiency_very_good_spreadscale;                    // 0x0C10, size 4
	float proficiency_very_good_bias;                           // 0x0C14, size 4
	float proficiency_very_good_additional_rest;                // 0x0C18, size 4
	float proficiency_perfect_spreadscale;                      // 0x0C1C, size 4
	float proficiency_perfect_bias;                             // 0x0C20, size 4
	float proficiency_perfect_additional_rest;                  // 0x0C24, size 4
	float smart_ammo_search_angle;                              // 0x0C28, size 4
	float smart_ammo_search_distance;                           // 0x0C2C, size 4
	float smart_ammo_new_target_delay;                          // 0x0C30, size 4
	bool smart_ammo_apply_new_target_delay_to_first_target;     // 0x0C34, size 1
	char unk_45[3];                                             // 0x0C35
	float smart_ammo_target_max_locks_normal;                   // 0x0C38, size 4
	float smart_ammo_target_max_locks_heavy;                    // 0x0C3C, size 4
	float smart_ammo_target_npc_lock_factor;                    // 0x0C40, size 4
	float smart_ammo_alert_npc_fraction;                        // 0x0C44, size 4
	int smart_ammo_max_targets;                                 // 0x0C48, size 4
	int smart_ammo_max_targeted_burst;                          // 0x0C4C, size 4
	bool smart_ammo_alt_lock_style;                             // 0x0C50, size 1
	bool smart_ammo_allow_ads_lock;                             // 0x0C51, size 1
	bool smart_ammo_allow_hip_fire_lock;                        // 0x0C52, size 1
	bool smart_ammo_allow_search_while_firing;                  // 0x0C53, size 1
	bool smart_ammo_allow_search_while_inactive;                // 0x0C54, size 1
	bool smart_ammo_only_search_on_charge;                      // 0x0C55, size 1
	bool smart_ammo_always_do_burst;                            // 0x0C56, size 1
	bool smart_ammo_track_cloaked_targets;                      // 0x0C57, size 1
	float smart_ammo_targeting_time_min;                        // 0x0C58, size 4
	float smart_ammo_targeting_time_max;                        // 0x0C5C, size 4
	float smart_ammo_targeting_time_min_npc;                    // 0x0C60, size 4
	float smart_ammo_targeting_time_max_npc;                    // 0x0C64, size 4
	float smart_ammo_targeting_time_modifier_cloaked;           // 0x0C68, size 4
	float smart_ammo_targeting_time_modifier_projectile;        // 0x0C6C, size 4
	float smart_ammo_targeting_time_modifier_projectile_owner;  // 0x0C70, size 4
	float smart_ammo_unlock_debounce_time;                      // 0x0C74, size 4
	bool smart_ammo_draw_acquisition_lines;                     // 0x0C78, size 1
	char unk_46[7];                                             // 0x0C79
	char const *smart_ammo_target_confirmed_sound;              // 0x0C80, size 8
	char const *smart_ammo_target_confirming_sound;             // 0x0C88, size 8
	char const *smart_ammo_target_found_sound;                  // 0x0C90, size 8
	char const *smart_ammo_target_lost_sound;                   // 0x0C98, size 8
	char const *smart_ammo_looping_sound_acquiring;             // 0x0CA0, size 8
	char const *smart_ammo_looping_sound_locked;                // 0x0CA8, size 8
	bool smart_ammo_search_npcs;                                // 0x0CB0, size 1
	bool smart_ammo_search_players;                             // 0x0CB1, size 1
	bool smart_ammo_stick_to_fully_locked_targets;              // 0x0CB2, size 1
	char unk_47[1];                                             // 0x0CB3
	float smart_ammo_hold_and_reset_after_all_locks;            // 0x0CB4, size 4
	float smart_ammo_active_shot_time;                          // 0x0CB8, size 4
	bool smart_ammo_active_shot_on_first_lock_only;             // 0x0CBC, size 1
	char unk_48[3];                                             // 0x0CBD
	float smart_ammo_active_shot_damage_multiplier;             // 0x0CC0, size 4
	bool smart_ammo_player_targets_must_be_tracked;             // 0x0CC4, size 1
	bool smart_ammo_npc_targets_must_be_tracked;                // 0x0CC5, size 1
	bool smart_ammo_other_targets_must_be_tracked;              // 0x0CC6, size 1
	bool smart_ammo_tracked_targets_check_visibility;           // 0x0CC7, size 1
	int smart_ammo_max_trackers_per_target;                     // 0x0CC8, size 4
	bool smart_ammo_tracker_status_effects;                     // 0x0CCC, size 1
	char unk_49[3];                                             // 0x0CCD
	char const *smart_ammo_lock_effect_attachment;              // 0x0CD0, size 8
	char const *smart_ammo_lock_effect2_attachment;             // 0x0CD8, size 8
	bool smart_ammo_search_friendly_team;                       // 0x0CE0, size 1
	bool smart_ammo_search_enemy_team;                          // 0x0CE1, size 1
	bool smart_ammo_search_neutral_team;                        // 0x0CE2, size 1
	bool smart_ammo_search_phase_shift;                         // 0x0CE3, size 1
	bool zoom_effects;                                          // 0x0CE4, size 1
	char unk_50[3];                                             // 0x0CE5
	float zoom_time_in;                                         // 0x0CE8, size 4
	float zoom_time_out;                                        // 0x0CEC, size 4
	float zoom_toggle_lerp_time;                                // 0x0CF0, size 4
	float zoom_fov;                                             // 0x0CF4, size 4
	float zoom_toggle_fov;                                      // 0x0CF8, size 4
	float zoom_fov_viewmodel;                                   // 0x0CFC, size 4
	float zoom_scope_frac_start;                                // 0x0D00, size 4
	float zoom_scope_frac_end;                                  // 0x0D04, size 4
	float zoom_angle_shift_pitch;                               // 0x0D08, size 4
	float zoom_angle_shift_yaw;                                 // 0x0D0C, size 4
	char const *sound_zoom_in;                                  // 0x0D10, size 8
	char const *sound_zoom_out;                                 // 0x0D18, size 8
	float dof_nearDepthStart;                                   // 0x0D20, size 4
	float dof_nearDepthEnd;                                     // 0x0D24, size 4
	float dof_zoom_nearDepthStart;                              // 0x0D28, size 4
	float dof_zoom_nearDepthEnd;                                // 0x0D2C, size 4
	float dof_zoom_focusArea_Horizontal;                        // 0x0D30, size 4
	float dof_zoom_focusArea_Top;                               // 0x0D34, size 4
	float dof_zoom_focusArea_Bottom;                            // 0x0D38, size 4
	int anim_alt_idleAttack;                                    // 0x0D3C, size 4
	float minimap_reveal_distance;                              // 0x0D40, size 4
	bool breaks_cloak;                                          // 0x0D44, size 1
	char unk_51[3];                                             // 0x0D45
	int rui_crosshair_index;                                    // 0x0D48, size 4
	int active_crosshair_count;                                 // 0x0D4C, size 4
	int ordnance_crosshair_always_on_start_index;               // 0x0D50, size 4
	bool crosshair_force_sprint_fade_disabled;                  // 0x0D54, size 1
	bool projectile_visible_to_smart_ammo;                      // 0x0D55, size 1
	bool projectile_do_predict_impact_effects;                  // 0x0D56, size 1
	bool is_burn_mod;                                           // 0x0D57, size 1
	float variable_sights_offset_range_1;                       // 0x0D58, size 4
	float variable_sights_offset_range_2;                       // 0x0D5C, size 4
	float variable_sights_offset_range_3;                       // 0x0D60, size 4
	float variable_sights_offset_range_4;                       // 0x0D64, size 4
	float projectile_drift_windiness;                           // 0x0D68, size 4
	float projectile_drift_intensity;                           // 0x0D6C, size 4
	float projectile_straight_time_min;                         // 0x0D70, size 4
	float projectile_straight_time_max;                         // 0x0D74, size 4
	float projectile_straight_radius_min;                       // 0x0D78, size 4
	float projectile_straight_radius_max;                       // 0x0D7C, size 4
	float projectile_speed_decay;                               // 0x0D80, size 4
	float projectile_lifetime;                                  // 0x0D84, size 4
	float projectile_bounce_damage_reduction_scale;             // 0x0D88, size 4
	float projectile_speed_reduction_factor;                    // 0x0D8C, size 4
	float projectile_collide_with_owner_grace_time;             // 0x0D90, size 4
	int projectile_ricochet_max_count;                          // 0x0D94, size 4
	bool projectile_damages_owner;                              // 0x0D98, size 1
	bool projectile_airburst_on_death;                          // 0x0D99, size 1
	char unk_52[6];                                             // 0x0D9A
	char const *projectile_death_sound;                         // 0x0DA0, size 8
	char const *projectile_flight_sound;                        // 0x0DA8, size 8
	float projectile_flamethrower_status_effect_range;          // 0x0DB0, size 4
	float projectile_flamethrower_status_effect_duration;       // 0x0DB4, size 4
	float grenade_angle_dependant_throw_min_speed;              // 0x0DB8, size 4
	float grenade_angle_dependant_throw_max_speed_angle;        // 0x0DBC, size 4
	float grenade_angle_dependant_throw_min_speed_angle;        // 0x0DC0, size 4
	char unk_53[4];                                             // 0x0DC4
	std::uint64_t zipline_station_model_ground;                 // 0x0DC8, size 8
	std::uint64_t zipline_station_model_wall;                   // 0x0DD0, size 8
	std::uint64_t zipline_station_model_ledge;                  // 0x0DD8, size 8
	char const *zipline_station_attachment_ground;              // 0x0DE0, size 8
	char const *zipline_station_attachment_wall;                // 0x0DE8, size 8
	char const *zipline_station_attachment_ledge;               // 0x0DF0, size 8
	char const *zipline_station_animation_begin;                // 0x0DF8, size 8
	char const *zipline_station_animation_ground;               // 0x0E00, size 8
	char const *zipline_station_animation_wall;                 // 0x0E08, size 8
	char const *zipline_station_animation_ledge;                // 0x0E10, size 8
	bool zipline_grenade;                                       // 0x0E18, size 1
	char unk_54[3];                                             // 0x0E19
	float zipline_grenade_auto_detach_distance;                 // 0x0E1C, size 4
	float zipline_grenade_snap_distance;                        // 0x0E20, size 4
	float zipline_grenade_snap_angle;                           // 0x0E24, size 4
	float zipline_distance_min;                                 // 0x0E28, size 4
	float zipline_distance_max;                                 // 0x0E2C, size 4
	char unk_55[88];                                            // 0x0E30
	bool object_placer;                                         // 0x0E88, size 1
	char unk_56[7];                                             // 0x0E89
	std::uint64_t object_placement_model;                       // 0x0E90, size 8
	float object_placement_distance_max;                        // 0x0E98, size 4
	float object_placement_hill_angle_max;                      // 0x0E9C, size 4
	float object_placement_clearance_behind;                    // 0x0EA0, size 4
	float object_placement_last_good_distance_max;              // 0x0EA4, size 4
	float object_placement_last_good_angle_max;                 // 0x0EA8, size 4
	float object_placement_drop_to_ground_offset_max;           // 0x0EAC, size 4
	float object_placement_distance_to_ground_max;              // 0x0EB0, size 4
	float object_placement_percent_off_ledge_max;               // 0x0EB4, size 4
	float object_placement_ground_penetration_max;              // 0x0EB8, size 4
	bool object_placement_use_top_trace;                        // 0x0EBC, size 1
	char unk_57[3];                                             // 0x0EBD
	float object_placement_top_side_percent_pierce_max;         // 0x0EC0, size 4
	float object_placement_top_distance_pierce_max;             // 0x0EC4, size 4
	bool object_placement_trace_through_turrets;                // 0x0EC8, size 1
	char unk_58[3];                                             // 0x0EC9
	int object_placement_vehicle_attachment_index;              // 0x0ECC, size 4
	vec3_t object_placement_vehicle_offset;                // 0x0ED0, size 12
	bool projectile_killreplay_enabled;                         // 0x0EDC, size 1
	char unk_59[3];                                             // 0x0EDD
	float projectile_chasecamDistanceMax;                       // 0x0EE0, size 4
	float projectile_chasecamMaxOrbitDepth;                     // 0x0EE4, size 4
	float projectile_chasecamMaxPitchUp;                        // 0x0EE8, size 4
	float projectile_chasecamOffsetUp;                          // 0x0EEC, size 4
	float projectile_chasecamOffsetRight;                       // 0x0EF0, size 4
	float projectile_chasecamOffsetForward;                     // 0x0EF4, size 4
	char const *challeng_req;                                   // 0x0EF8, size 8
	int challenge_tier;                                         // 0x0F00, size 4
	bool loadout_selectable;                                    // 0x0F04, size 1
	char unk_60[3];                                             // 0x0F05
	char const *loadout_type;                                   // 0x0F08, size 8
	char const *loadout_parent_ref;                             // 0x0F10, size 8
	char const *loadout_child_ref;                              // 0x0F18, size 8
	char const *mod_print_name;                                 // 0x0F20, size 8
	char const *mod_short_print_name;                           // 0x0F28, size 8
	char const *mod_description;                                // 0x0F30, size 8
	float stat_damage;                                          // 0x0F38, size 4
	float stat_accuracy;                                        // 0x0F3C, size 4
	float stat_range;                                           // 0x0F40, size 4
	float stat_rof;                                             // 0x0F44, size 4
	float headshot_distance;                                    // 0x0F48, size 4
	float damage_leg_scale;                                     // 0x0F4C, size 4
	char const *menu_image;                                     // 0x0F50, size 8
	char const *menu_icon;                                      // 0x0F58, size 8
	char const *menu_alt_icon;                                  // 0x0F60, size 8
	bool never_drop;                                            // 0x0F68, size 1
	bool destroy_on_drop;                                       // 0x0F69, size 1
	bool clear_fx_on_new_view_model;                            // 0x0F6A, size 1
	bool thirdperson_fire_from_mount_point;                     // 0x0F6B, size 1
	bool custom_bool_0;                                         // 0x0F6C, size 1
	bool custom_bool_1;                                         // 0x0F6D, size 1
	bool custom_bool_2;                                         // 0x0F6E, size 1
	bool custom_bool_3;                                         // 0x0F6F, size 1
	bool custom_bool_4;                                         // 0x0F70, size 1
	bool custom_bool_5;                                         // 0x0F71, size 1
	bool custom_bool_6;                                         // 0x0F72, size 1
	bool custom_bool_7;                                         // 0x0F73, size 1
	int custom_int_0;                                           // 0x0F74, size 4
	int custom_int_1;                                           // 0x0F78, size 4
	int custom_int_2;                                           // 0x0F7C, size 4
	int custom_int_3;                                           // 0x0F80, size 4
	int custom_int_4;                                           // 0x0F84, size 4
	int custom_int_5;                                           // 0x0F88, size 4
	int custom_int_6;                                           // 0x0F8C, size 4
	int custom_int_7;                                           // 0x0F90, size 4
	float custom_float_0;                                       // 0x0F94, size 4
	float custom_float_1;                                       // 0x0F98, size 4
	float custom_float_2;                                       // 0x0F9C, size 4
	float custom_float_3;                                       // 0x0FA0, size 4
	float custom_float_4;                                       // 0x0FA4, size 4
	float custom_float_5;                                       // 0x0FA8, size 4
	float custom_float_6;                                       // 0x0FAC, size 4
	float custom_float_7;                                       // 0x0FB0, size 4
	bool reload_enabled;                                        // 0x0FB4, size 1
	bool cycle_to_next_when_out_of_ammo;                        // 0x0FB5, size 1
	char unk_61[2];                                             // 0x0FB6
	char const *sound_disabledfire;                             // 0x0FB8, size 8
	char const *sound_dryfire;                                  // 0x0FC0, size 8
	char const *sound_pickup;                                   // 0x0FC8, size 8
	char const *sound_weapon_ready;                             // 0x0FD0, size 8
	char const *sound_cook_warning;                             // 0x0FD8, size 8
	char const *sound_throw_1p;                                 // 0x0FE0, size 8
	char const *sound_throw_3p;                                 // 0x0FE8, size 8
	char const *sound_deploy_1p;                                // 0x0FF0, size 8
	char const *sound_deploy_3p;                                // 0x0FF8, size 8
	char const *sound_grenade_projectile;                       // 0x1000, size 8
	char const *active_optic_appearance;                        // 0x1008, size 8
	bool melee_respect_next_attack_time;                        // 0x1010, size 1
	bool can_attack_when_dead;                                  // 0x1011, size 1
	bool show_pre_modded_tracer;                                // 0x1012, size 1
	char unk_62[1];                                             // 0x1013
	float threat_scope_fadedist_start;                          // 0x1014, size 4
	float threat_scope_fadedist_end;                            // 0x1018, size 4
	bool threat_scope_enabled;                                  // 0x101C, size 1
	char unk_63[3];                                             // 0x101D
	float threat_scope_zoomfrac_start;                          // 0x1020, size 4
	float threat_scope_zoomfrac_end;                            // 0x1024, size 4
	char const *threat_scope_bounds_tagname1;                   // 0x1028, size 8
	char const *threat_scope_bounds_tagname2;                   // 0x1030, size 8
	float threat_scope_bounds_width;                            // 0x1038, size 4
	float threat_scope_bounds_height;                           // 0x103C, size 4
	bool threat_scope_fadeWithDistance;                         // 0x1040, size 1
	char unk_64[3];                                             // 0x1041
	float ignition_distance;                                    // 0x1044, size 4
	float pre_ignition_speed;                                   // 0x1048, size 4
	int pre_ignition_damage;                                    // 0x104C, size 4
	int pre_ignition_damage_titanarmor;                         // 0x1050, size 4
	int pre_ignition_npc_damage;                                // 0x1054, size 4
	int pre_ignition_npc_damage_titanarmor;                     // 0x1058, size 4
	char unk_65[4];                                             // 0x105C
	char const *pre_ignition_flight_sound;                      // 0x1060, size 8
	char const *pre_ignition_trail_effect;                      // 0x1068, size 8
	char const *ignition_sound;                                 // 0x1070, size 8
	char const *ignition_effect;                                // 0x1078, size 8
	bool grapple_weapon;                                        // 0x1080, size 1
	char unk_66[3];                                             // 0x1081
	float grapple_power_required;                               // 0x1084, size 4
	float grapple_power_use_rate;                               // 0x1088, size 4
	float grapple_maxLength;                                    // 0x108C, size 4
	float grapple_maxLengthVert;                                // 0x1090, size 4
	vec3_t chroma_color;                                   // 0x1094, size 12
	eWeaponFireMode fire_mode;                                  // 0x10A0, size 4
	eActiveInventorySlot offhand_active_slot;                   // 0x10A4, size 4
	eWeaponCooldownType cooldown_type;                          // 0x10A8, size 4
	eWeaponHolsterType holster_type;                            // 0x10AC, size 4
	eWeaponDamageFalloffType damage_falloff_type;               // 0x10B0, size 4
	eWeaponBallisticType ballistic_type;                        // 0x10B4, size 4
	std::uint16_t viewmodel;                                    // 0x10B8, size 2
	std::uint16_t playermodel;                                  // 0x10BA, size 2
	std::uint16_t holstermodel;                                 // 0x10BC, size 2
	char unk_67[2];                                             // 0x10BE
	std::uint64_t impact_effect_table;                          // 0x10C0, size 8
	std::uint64_t bounce_effect_table;                          // 0x10C8, size 8
	std::uint64_t sustained_laser_impact_effect_table;          // 0x10D0, size 8
	std::uint64_t pre_ignition_impact_effect_table;             // 0x10D8, size 8
	std::uint64_t hud_icon;                                     // 0x10E0, size 8
	std::uint64_t tracer_effect;                                // 0x10E8, size 8
	std::uint64_t tracer_effect_first_person;                   // 0x10F0, size 8
	std::uint64_t projectile_trail_effect_0_1p;                 // 0x10F8, size 8
	std::uint64_t projectile_trail_effect_0_3p;                 // 0x1100, size 8
	std::uint64_t projectile_trail_effect_1_1p;                 // 0x1108, size 8
	std::uint64_t projectile_trail_effect_1_3p;                 // 0x1110, size 8
	std::uint64_t projectile_trail_effect_2_1p;                 // 0x1118, size 8
	std::uint64_t projectile_trail_effect_2_3p;                 // 0x1120, size 8
	std::uint64_t projectile_trail_effect_3_1p;                 // 0x1128, size 8
	std::uint64_t projectile_trail_effect_3_3p;                 // 0x1130, size 8
	std::uint64_t projectile_trail_effect_4_1p;                 // 0x1138, size 8
	std::uint64_t projectile_trail_effect_4_3p;                 // 0x1140, size 8
	std::uint64_t projectilemodel;                              // 0x1148, size 8
	std::uint64_t fx_muzzle_flash_view;                         // 0x1150, size 8
	std::uint64_t fx_muzzle_flash_world;                        // 0x1158, size 8
	char const *fx_muzzle_flash_attach;                         // 0x1160, size 8
	char const *fx_muzzle_flash_attach_scoped;                  // 0x1168, size 8
	std::uint64_t fx_muzzle_flash2_view;                        // 0x1170, size 8
	std::uint64_t fx_muzzle_flash2_world;                       // 0x1178, size 8
	char const *fx_muzzle_flash2_attach;                        // 0x1180, size 8
	char const *fx_muzzle_flash2_attach_scoped;                 // 0x1188, size 8
	std::uint64_t fx_shell_eject_view;                          // 0x1190, size 8
	std::uint64_t fx_shell_eject_world;                         // 0x1198, size 8
	char const *fx_shell_eject_attach;                          // 0x11A0, size 8
	char const *fx_shell_eject_attach_scoped;                   // 0x11A8, size 8
	std::uint64_t fx_shell_eject2_view;                         // 0x11B0, size 8
	std::uint64_t fx_shell_eject2_world;                        // 0x11B8, size 8
	char const *fx_shell_eject2_attach;                         // 0x11C0, size 8
	char const *fx_shell_eject2_attach_scoped;                  // 0x11C8, size 8
	std::uint64_t grenade_arc_indicator_effect;                 // 0x11D0, size 8
	std::uint64_t grenade_arc_indicator_effect_first;           // 0x11D8, size 8
	std::uint64_t grenade_arc_impact_indicator_effect;          // 0x11E0, size 8
	std::uint64_t zipline_indicator_arc_blocked_effect;         // 0x11E8, size 8
	std::uint64_t zipline_indicator_line_effect;                // 0x11F0, size 8
	std::uint64_t zipline_indicator_impact_ground_effect;       // 0x11F8, size 8
	std::uint64_t zipline_indicator_impact_wall_effect;         // 0x1200, size 8
	std::uint64_t zipline_indicator_impact_blocked_effect;      // 0x1208, size 8
	std::uint64_t sustained_laser_effect_1p;                    // 0x1210, size 8
	std::uint64_t sustained_laser_effect_3p;                    // 0x1218, size 8
	std::uint64_t sustained_laser_impact_effect;                // 0x1220, size 8
	std::uint64_t sustained_laser_damage_effect;                // 0x1228, size 8
	std::uint64_t charge_effect_1p;                             // 0x1230, size 8
	std::uint64_t charge_effect_3p;                             // 0x1238, size 8
	std::uint64_t charge_effect_burn_mod_1p;                    // 0x1240, size 8
	std::uint64_t charge_effect_burn_mod_3p;                    // 0x1248, size 8
	std::uint64_t charge_effect2_1p;                            // 0x1250, size 8
	std::uint64_t charge_effect2_3p;                            // 0x1258, size 8
	std::uint64_t smart_ammo_lock_effect_1p;                    // 0x1260, size 8
	std::uint64_t smart_ammo_lock_effect_3p;                    // 0x1268, size 8
	std::uint64_t smart_ammo_lock_effect2_1p;                   // 0x1270, size 8
	std::uint64_t smart_ammo_lock_effect2_3p;                   // 0x1278, size 8
	std::uint64_t vortex_absorb_effect;                         // 0x1280, size 8
	std::uint64_t vortex_absorb_effect_third_person;            // 0x1288, size 8
	std::uint64_t vortex_impact_effect;                         // 0x1290, size 8
	std::uint64_t targeting_laser_effect_1p;                    // 0x1298, size 8
	std::uint64_t targeting_laser_effect_3p;                    // 0x12A0, size 8
};
