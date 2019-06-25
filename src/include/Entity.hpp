#ifndef PUGGO_ENTITY_HPP
#define PUGGO_ENTITY_HPP

#include <iostream>

using namespace std;

namespace puggo {
	struct EntityID {
		unsigned int index;
		unsigned int generation;

		EntityID(const unsigned int& index, const unsigned int& generation);
	};

	struct ComponentFlags {
		unsigned char collisionBox : 1;
		unsigned char collisionCapsule : 1;
		unsigned char collisionSphere : 1;
		unsigned char mesh : 1;
		unsigned char physics : 1;
		unsigned char shader : 1;
		unsigned char move : 1;
		unsigned char transform : 1;

		ComponentFlags();
	};
	
	struct Entity {
		EntityID id;
		ComponentFlags flags = ComponentFlags();
	};

	ostream& operator<<(ostream& out, const Entity& entity) noexcept;
}

#endif // !PUGGO_ENTITY_HPP
