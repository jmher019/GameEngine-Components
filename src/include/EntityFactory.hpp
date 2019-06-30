#ifndef PUGGO_ENTITY_FACTORY_HPP
#define PUGGO_ENTITY_FACTORY_HPP

#include <assert.h> 
#include <algorithm>

#include <CollisionBoxComponent.hpp>
#include <CollisionCapsuleComponent.hpp>
#include <CollisionSphereComponent.hpp>
#include <Entity.hpp>
#include <MeshComponent.hpp>
#include <MoveComponent.hpp>
#include <PhysicsComponent.hpp>
#include <HeapRingBuffer.hpp>
#include <ShaderComponent.hpp>
#include <TransformComponent.hpp>

#include <AllocationSystem.hpp>

namespace puggo {
	enum class Components {
		COLLISION_BOX,
		COLLISION_CAPSULE,
		COLLISION_SPHERE,
		MESH,
		MOVE,
		PHYSICS,
		SHADER,
		TRANSFORM
	};

	class EntityFactory {
	public:
		// Call this function to initialize the memory in the factory
		static void initialize(const unsigned int entityCapacity = 1024);

		// Call this function to cleanup the memory in the factory
		static void cleanUp();

		// Creates an entity with just a transform component
		static Result<Entity, string> createBasicEntity();

		// Utility check function to verify if an entity exists
		static bool doesEntityExist(const Entity& entity);

		// Deletes an entity (Caller is responsible for disposing reference to entity)
		// Will fail if the entity has already been deleted
		static bool deleteEntity(const Entity& entity);

		// Adds a component
		// Returns false if the component is already added or if the entity has been freed
		static bool addComponent(Entity& entity, const Components& component);

		// Removes a component
		// Returns false if the component is already removed or if the entity has been freed
		static bool removeComponent(Entity& entity, const Components& component);

	private:
		static unsigned int numEntities;
		static HeapRingBuffer<unsigned int> freedIndices;
		static unsigned int lastIndex;
		static unsigned int* generations;
		static CollisionBoxComponent* collisionBoxComponents;
		static CollisionCapsuleComponent* collisionCapsuleComponents;
		static CollisionSphereComponent* collisionSphereComponents;
		static MeshComponent* meshComponents;
		static MoveComponent* moveComponents;
		static PhysicsComponent* physicsComponents;
		static ShaderComponent* shaderComponents;
		static TransformComponent* transformComponents;
	};
}

#endif // !PUGGO_ENTITY_FACTORY_HPP
