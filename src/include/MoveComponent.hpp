#ifndef PUGGO_MOVE_COMPONENT_HPP
#define PUGGO_MOVE_COMPONENT_HPP

#include <glm/glm.hpp>

using namespace glm;

namespace puggo {
	struct MoveComponent {
		vec3 velocity = vec3(0.f, 0.f, 0.f);
		vec3 acceleration = vec3(0.f, 0.f, 0.f);
		vec3 angularVelocity = vec3();
		vec3 angularAcceleration = vec3();
	};
}

#endif // !PUGGO_MOVE_COMPONENT_HPP
