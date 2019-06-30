#ifndef PUGGO_ENTITY_HPP
#define PUGGO_ENTITY_HPP

#include <iostream>
#include <limits>

using namespace std;

namespace puggo {
	struct EntityID {
		unsigned int index;
		unsigned int generation;

		EntityID() noexcept;
		EntityID(const unsigned int& index, const unsigned int& generation);
	};

	struct ComponentFlags {
		unsigned int collisionBox : 1;
		unsigned int collisionCapsule : 1;
		unsigned int collisionSphere : 1;
		unsigned int mesh : 1;
		unsigned int physics : 1;
		unsigned int shader : 1;
		unsigned int move : 1;
		unsigned int transform : 1;

		ComponentFlags() noexcept;
	};
	
	struct Entity {
		EntityID id;
		ComponentFlags flags;

		Entity(const EntityID& id = EntityID(), const ComponentFlags& flags = ComponentFlags());
		Entity(const Entity& entity);
		Entity(Entity&& entity) noexcept;

		Entity& operator=(const Entity& entity);
		Entity& operator=(Entity&& entity) noexcept;
	};

	ostream& operator<<(ostream& out, const Entity& entity) noexcept;
}

#endif // !PUGGO_ENTITY_HPP
