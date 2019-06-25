#ifndef PUGGO_LOCAL_TRANSFORM_COMPONENT_HPP
#define PUGGO_LOCAL_TRANSFORM_COMPONENT_HPP
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/dual_quaternion.hpp>

using namespace glm;

namespace puggo {
	// Transforms are applied for S (scale), R (Rotation), P(position)
	// P * R * S
	struct TransformComponent {
		fdualquat positionAndOrientation = fdualquat(fquat(1.f, 0.f, 0.f, 0.f), vec3());
		vec3 scale = vec3(1.f, 1.f, 1.f);
	};

	// Applies a translation to the transform component
	void translate(TransformComponent& comp, const vec3& translation) noexcept;

	// Applies a rotation to the transform component.
	// Axis is expected to be a normalized vector
	void rotate(TransformComponent& comp, const float& degrees, const vec3& axis) noexcept;

	// Applies a rotation to the transform component.
	void rotate(TransformComponent& comp, const float& degreesX, const float& degreesY, const float& degreesZ) noexcept;

	// Applies a rotation to the transform component.
	void rotate(TransformComponent& comp, const fquat& rot) noexcept;

	// Applies an orbit to the transform component.
	// Axis is expected to be a normalized vector
	void orbit(TransformComponent& comp, const float& degrees, const vec3& axis) noexcept;

	// Applies an orbit to the transform component.
	void orbit(TransformComponent& comp, const float& degreesX, const float& degreesY, const float& degreesZ) noexcept;

	// Applies an orbit to the transform component.
	void orbit(TransformComponent& comp, const fquat& rot) noexcept;

	// Applies translation then rotation
	// Axis is expected to be a normalized vector
	void translateAndRotate(TransformComponent& comp, const vec3& translation, const float& degrees, const vec3& axis) noexcept;

	// Applies translation then rotation
	void translateAndRotate(TransformComponent& comp, const vec3& translation, const float& degreesX, const float& degreesY, const float& degreesZ) noexcept;

	// Applies translation then rotation
	void translateAndRotate(TransformComponent& comp, const vec3& translation, const fquat& rot) noexcept;

	// Applies rotation then translation
	// Axis is expected to be a normalized vector
	void rotateAndTranslate(TransformComponent& comp, const vec3& translation, const float& degrees, const vec3& axis) noexcept;

	// Applies rotation then translation
	void rotateAndTranslate(TransformComponent& comp, const vec3& translation, const float& degreesX, const float& degreesY, const float& degreesZ) noexcept;

	// Applies rotation then translation
	void rotateAndTranslate(TransformComponent& comp, const vec3& translation, const fquat& rot) noexcept;

	// Applies scale
	void scale(TransformComponent& comp, const vec3& s) noexcept;

	// Applies transform component
	void transform(TransformComponent& comp, const TransformComponent& transformComp) noexcept;
}

#endif // !PUGGO_LOCAL_TRANSFORM_COMPONENT_HPP
