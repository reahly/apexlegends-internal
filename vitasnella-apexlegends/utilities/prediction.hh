#pragma once
#include "vec3.hh"

namespace prediction {
	struct prediction_ctx {
		float pitch, yaw, time;
	};

	inline vec3_t get_projectile_fire_setup( const vec3_t& origin, const vec3_t& target ) {
		return target - origin;
	}

	inline vec3_t predict_position( vec3_t origin, const vec3_t velocity, const float time ) {
		return origin + velocity * time;
	}

	inline bool optimal( const float x, const float y, const float v0, const float g, float& pitch ) {
		const auto root = v0 * v0 * v0 * v0 - g * ( g * x * x + 2.0f * y * v0 * v0 );
		if ( root < 0.0f ) 
			return false;

		pitch = atan( ( v0 * v0 - sqrt( root ) ) / ( g * x ) );
		return true;
	}

	inline bool solve2d( const vec3_t& origin, const float bullet_speed, const float bullet_gravity, const vec3_t& target, prediction_ctx& sol ) {
		const auto v = get_projectile_fire_setup( origin, target );
		const auto dx = sqrt( v.x * v.x + v.y * v.y );
		const auto dy = v.z;
		const auto v0 = bullet_speed;
		const auto g = bullet_gravity;
		if ( !optimal( dx, dy, v0, g, sol.pitch ) ) 
			return false;

		sol.time = dx / ( cos( sol.pitch ) * v0 );
		sol.yaw = atan2( v.y, v.x );
		return true;
	}

	inline bool solve( entity_t* entity, weapon_t* weapon, prediction_ctx& sol ) {
		static const auto MAX_TIME = 1.0f;
		static const float TIME_STEP = 1.0 / 256.0f;
		for ( auto target_time = 0.0f; target_time <= MAX_TIME; target_time += TIME_STEP ) {
			const auto target_pos = predict_position( entity->get_bone_position( 12 ), entity->velocity( ), target_time );
			if ( !solve2d( entity_t::camera_position( ), weapon->bullet_speed( ), 375.f * weapon->bullet_gravity( ), target_pos, sol ) ) {
				return false;
			}

			if ( sol.time < target_time ) {
				return true;
			}
		}

		return false;
	}
}