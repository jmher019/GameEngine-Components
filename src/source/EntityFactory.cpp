#include <EntityFactory.hpp>

using namespace puggo;

unsigned int EntityFactory::numEntities = MINIMUM_ENTITIES;
HeapRingBuffer<unsigned int> EntityFactory::freedIndices;
unsigned int EntityFactory::lastIndex = 0;
unsigned int* EntityFactory::generations = nullptr;
CollisionBoxComponent* EntityFactory::collisionBoxComponents = nullptr;
CollisionCapsuleComponent* EntityFactory::collisionCapsuleComponents = nullptr;
CollisionSphereComponent* EntityFactory::collisionSphereComponents = nullptr;
MeshComponent* EntityFactory::meshComponents = nullptr;
MoveComponent* EntityFactory::moveComponents = nullptr;
PhysicsComponent* EntityFactory::physicsComponents = nullptr;
ShaderComponent* EntityFactory::shaderComponents = nullptr;
TransformComponent* EntityFactory::transformComponents = nullptr;

void EntityFactory::initialize(const unsigned int entityCapacity) {
	assert(EntityFactory::numEntities >= MINIMUM_ENTITIES);
	assert(EntityFactory::generations == nullptr);
	
	numEntities = entityCapacity;

	generations = static_cast<unsigned int*>(AllocationSystem::requestMemoryFromSystem(sizeof(unsigned int) * entityCapacity));
	memset(generations, 0, sizeof(unsigned int) * entityCapacity);

	freedIndices = move(HeapRingBuffer<unsigned int>(entityCapacity, static_cast<unsigned int*>(AllocationSystem::requestMemoryFromSystem(sizeof(unsigned int) * entityCapacity))));

	// Initialize components here
	collisionBoxComponents = static_cast<CollisionBoxComponent*>(AllocationSystem::requestMemoryFromSystem(sizeof(CollisionBoxComponent) * entityCapacity));
	collisionCapsuleComponents = static_cast<CollisionCapsuleComponent*>(AllocationSystem::requestMemoryFromSystem(sizeof(CollisionCapsuleComponent) * entityCapacity));
	collisionSphereComponents = static_cast<CollisionSphereComponent*>(AllocationSystem::requestMemoryFromSystem(sizeof(CollisionSphereComponent) * entityCapacity));
	meshComponents = static_cast<MeshComponent*>(AllocationSystem::requestMemoryFromSystem(sizeof(MeshComponent) * entityCapacity));
	moveComponents = static_cast<MoveComponent*>(AllocationSystem::requestMemoryFromSystem(sizeof(MoveComponent) * entityCapacity));
	physicsComponents = static_cast<PhysicsComponent*>(AllocationSystem::requestMemoryFromSystem(sizeof(PhysicsComponent) * entityCapacity));
	shaderComponents = static_cast<ShaderComponent*>(AllocationSystem::requestMemoryFromSystem(sizeof(ShaderComponent) * entityCapacity));
	transformComponents = static_cast<TransformComponent*>(AllocationSystem::requestMemoryFromSystem(sizeof(TransformComponent) * entityCapacity));
}

void EntityFactory::cleanUp() {
	assert(generations != nullptr);
	numEntities = 0;
	lastIndex = 0;
}

Entity EntityFactory::createBasicEntity() {
	assert(generations != nullptr);

	unsigned int index = lastIndex;
	if (
		index == numEntities ||
		freedIndices.getLength() > 0
	) {
		index = *freedIndices.extractNext();
	}
	else {
		assert(lastIndex < numEntities);

		++lastIndex;
		generations[index] = 0;
	}


	Entity entity = {
		EntityID(index, generations[index])
	};
	addComponent(entity, Components::TRANSFORM);
	return entity;
}

bool EntityFactory::doesEntityExist(const Entity& entity) {
	assert(generations != nullptr);

	return generations[entity.id.index] == entity.id.generation;
}

bool EntityFactory::deleteEntity(const Entity& entity) {
	assert(generations != nullptr);

	if (doesEntityExist(entity) && freedIndices.getLength() != freedIndices.getCapacity()) {
		++generations[entity.id.index];
		freedIndices.add(entity.id.index);
		return true;
	}

	return false;
}

bool EntityFactory::addComponent(Entity& entity, const Components& component) {
	assert(generations != nullptr);
	
	if (!doesEntityExist(entity)) {
		return false;
	}

	switch (component) {
		case Components::COLLISION_BOX: {
			if (entity.flags.collisionBox) {
				return false;
			}

			removeComponent(entity, Components::COLLISION_CAPSULE);
			removeComponent(entity, Components::COLLISION_SPHERE);

			entity.flags.collisionBox = 1;
			collisionBoxComponents[entity.id.index] = CollisionBoxComponent();
			return true;
		}
		case Components::COLLISION_CAPSULE: {
			if (entity.flags.collisionCapsule) {
				return false;
			}

			removeComponent(entity, Components::COLLISION_BOX);
			removeComponent(entity, Components::COLLISION_SPHERE);

			entity.flags.collisionCapsule = 1;
			collisionCapsuleComponents[entity.id.index] = CollisionCapsuleComponent();
			return true;
		}
		case Components::COLLISION_SPHERE: {
			if (entity.flags.collisionSphere) {
				return false;
			}

			removeComponent(entity, Components::COLLISION_BOX);
			removeComponent(entity, Components::COLLISION_CAPSULE);

			entity.flags.collisionSphere = 1;
			collisionSphereComponents[entity.id.index] = CollisionSphereComponent();
			return true;
		}
		case Components::MESH: {
			if (entity.flags.mesh) {
				return false;
			}

			entity.flags.mesh = 1;
			meshComponents[entity.id.index] = MeshComponent();
			return true;
		}
		case Components::MOVE: {
			if (entity.flags.move) {
				return false;
			}

			entity.flags.move = 1;
			moveComponents[entity.id.index] = MoveComponent();
			return true;
		}
		case Components::PHYSICS: {
			if (entity.flags.physics) {
				return false;
			}

			entity.flags.physics = 1;
			physicsComponents[entity.id.index] = PhysicsComponent();
			return true;
		}
		case Components::SHADER: {
			if (entity.flags.shader) {
				return false;
			}

			entity.flags.shader = 1;
			shaderComponents[entity.id.index] = ShaderComponent();
			return true;
		}
		case Components::TRANSFORM: {
			if (entity.flags.transform) {
				return false;
			}

			entity.flags.transform = 1;
			transformComponents[entity.id.index] = TransformComponent();
			return true;
		}
	}

	return false;
}

bool EntityFactory::removeComponent(Entity& entity, const Components& component) {
	assert(generations != nullptr);

	if (!doesEntityExist(entity)) {
		return false;
	}

	switch (component) {
		case Components::COLLISION_BOX: {
			if (!entity.flags.collisionBox) {
				return false;
			}

			entity.flags.collisionBox = 0;
			return true;
		}
		case Components::COLLISION_CAPSULE: {
			if (!entity.flags.collisionCapsule) {
				return false;
			}

			entity.flags.collisionCapsule = 0;
			return true;
		}
		case Components::COLLISION_SPHERE: {
			if (!entity.flags.collisionSphere) {
				return false;
			}

			entity.flags.collisionSphere = 0;
			return true;
		}
		case Components::MESH: {
			if (!entity.flags.mesh) {
				return false;
			}

			entity.flags.mesh = 0;
			return true;
		}
		case Components::MOVE: {
			if (!entity.flags.move) {
				return false;
			}

			entity.flags.move = 0;
			return true;
		}
		case Components::PHYSICS: {
			if (!entity.flags.physics) {
				return false;
			}

			entity.flags.physics = 0;
			return true;
		}
		case Components::SHADER: {
			if (!entity.flags.shader) {
				return false;
			}

			entity.flags.shader = 0;
			return true;
		}
		case Components::TRANSFORM: {
			if (!entity.flags.transform) {
				return false;
			}

			entity.flags.transform = 0;
			return true;
		}
	}

	return false;
}