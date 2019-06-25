#ifndef PUGGO_COLLISION_BOX_COMPONENT_HPP
#define PUGGO_COLLISION_BOX_COMPONENT_HPP

#include <glm/glm.hpp>

using namespace glm;

namespace puggo {
	struct CollisionBoxComponent {
		vec3 halfExtents = vec3();
	};
}

#endif // !PUGGO_COLLISION_BOX_COMPONENT_HPP
