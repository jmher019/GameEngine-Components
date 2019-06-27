#include <TransformComponent.hpp>

void puggo::translate(TransformComponent& comp, const vec3& translation) noexcept {
	comp.positionAndOrientation = fdualquat(fquat(1.f, 0.f, 0.f, 0.f), translation) * comp.positionAndOrientation;
}

void puggo::rotate(TransformComponent& comp, const float& degrees, const vec3& axis) noexcept {
	rotate(comp, glm::rotate(fquat(1.f, 0.f, 0.f, 0.f), glm::radians(degrees), axis));
}

void puggo::rotate(TransformComponent& comp, const float& degreesX, const float& degreesY, const float& degreesZ) noexcept {
	const vec3 degreesVec = vec3(degreesX, degreesY, degreesZ);
	const float degrees = glm::length(vec3(degreesX, degreesY, degreesZ));
	rotate(comp, degrees, degreesVec / degrees);
}

void puggo::rotate(TransformComponent& comp, const fquat& rot) noexcept {
	comp.positionAndOrientation = dualquat(rot * comp.positionAndOrientation.real, comp.positionAndOrientation.dual);
}

void puggo::orbit(TransformComponent& comp, const float& degrees, const vec3& axis) noexcept {
	orbit(comp, glm::rotate(fquat(1.f, 0.f, 0.f, 0.f), glm::radians(degrees), axis));
}

void puggo::orbit(TransformComponent& comp, const float& degreesX, const float& degreesY, const float& degreesZ) noexcept {
	const vec3 degreesVec = vec3(degreesX, degreesY, degreesZ);
	const float degrees = glm::length(vec3(degreesX, degreesY, degreesZ));
	orbit(comp, degrees, degreesVec / degrees);
}

void puggo::orbit(TransformComponent& comp, const fquat& rot) noexcept {
	comp.positionAndOrientation = fdualquat(rot, vec3()) * comp.positionAndOrientation;
}

void puggo::translateAndRotate(TransformComponent& comp, const vec3& translation, const float& degrees, const vec3& axis) noexcept {
	translateAndRotate(comp, translation, glm::rotate(fquat(1.f, 0.f, 0.f, 0.f), glm::radians(degrees), axis));
}

void puggo::translateAndRotate(TransformComponent& comp, const vec3& translation, const float& degreesX, const float& degreesY, const float& degreesZ) noexcept {
	const vec3 degreesVec = vec3(degreesX, degreesY, degreesZ);
	const float degrees = glm::length(vec3(degreesX, degreesY, degreesZ));
	translateAndRotate(comp, translation, degrees, degreesVec / degrees);
}

void puggo::translateAndRotate(TransformComponent& comp, const vec3& translation, const fquat& rot) noexcept {
	comp.positionAndOrientation = fdualquat(rot, vec3()) * fdualquat(fquat(1.f, 0.f, 0.f, 0.f), translation) * comp.positionAndOrientation;
}

void puggo::rotateAndTranslate(TransformComponent& comp, const vec3& translation, const float& degrees, const vec3& axis) noexcept {
	rotateAndTranslate(comp, translation, glm::rotate(fquat(1.f, 0.f, 0.f, 0.f), glm::radians(degrees), axis));
}

void puggo::rotateAndTranslate(TransformComponent& comp, const vec3& translation, const float& degreesX, const float& degreesY, const float& degreesZ) noexcept {
	const vec3 degreesVec = vec3(degreesX, degreesY, degreesZ);
	const float degrees = glm::length(vec3(degreesX, degreesY, degreesZ));
	rotateAndTranslate(comp, translation, degrees, degreesVec / degrees);
}

void puggo::rotateAndTranslate(TransformComponent& comp, const vec3& translation, const fquat& rot) noexcept {
	comp.positionAndOrientation = fdualquat(rot, translation) * comp.positionAndOrientation;
}

void puggo::scale(TransformComponent& comp, const vec3& s) noexcept {
	comp.scale *= s;
}

void puggo::transform(TransformComponent& comp, const TransformComponent& transfromComp) noexcept {
	scale(comp, transfromComp.scale);
	comp.positionAndOrientation = transfromComp.positionAndOrientation * comp.positionAndOrientation;
}