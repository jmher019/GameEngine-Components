#include <Entity.hpp>

using namespace puggo;

EntityID::EntityID() noexcept: index(numeric_limits<unsigned int>::max()), generation(numeric_limits<unsigned int>::max()) {}

EntityID::EntityID(const unsigned int& index, const unsigned int& generation) :
	index(index),
	generation(generation) {

}

ComponentFlags::ComponentFlags() noexcept:
	collisionBox(0),
	collisionCapsule(0),
	collisionSphere(0),
	mesh(0),
	physics(0),
	shader(0),
	move(0),
	transform(0) {
}

Entity::Entity(const EntityID& id, const ComponentFlags& flags): id(id), flags(flags) {}
Entity::Entity(const Entity& entity): id(entity.id), flags(entity.flags) {}
Entity::Entity(Entity&& entity) noexcept: id(move(entity.id)), flags(move(entity.flags)) {}

Entity& Entity::operator=(const Entity& entity) {
	id = entity.id;
	flags = entity.flags;
	return *this;
}

Entity& Entity::operator=(Entity&& entity) noexcept {
	id = move(entity.id);
	flags = move(entity.flags);
	return *this;
}

ostream& puggo::operator<<(ostream& out, const Entity& entity) noexcept {
	out << "/********************* Entity[id=" << entity.id.index << ", generation=" << entity.id.generation << "] *******************/" << endl;
	out << "/********************* Attached components *******************/" << endl;
	out << "collisionBox: " << static_cast<unsigned int>(entity.flags.collisionBox) << endl;
	out << "collisionCapsule: " << static_cast<unsigned int>(entity.flags.collisionCapsule) << endl;
	out << "collisionSphere: " << static_cast<unsigned int>(entity.flags.collisionSphere) << endl;
	out << "mesh: " << static_cast<unsigned int>(entity.flags.mesh) << endl;
	out << "physics: " << static_cast<unsigned int>(entity.flags.physics) << endl;
	out << "shader: " << static_cast<unsigned int>(entity.flags.shader) << endl;
	out << "move: " << static_cast<unsigned int>(entity.flags.move) << endl;
	out << "transform: " << static_cast<unsigned int>(entity.flags.transform) << endl;
	return out;
}