#ifndef _TRANSFORM_COMPONENT_hpp
#define _TRANSFORM_COMPONENT_hpp

#include <map>
#include "es/component.hpp"
#include "graphics/transform.hpp"

class TransformComponent : public Component
{
private:
    graphics::Transform* _transform;

	std::string _id;
public:
    static const long MASK = 0x00000000000000000000000000000001;

    /// default const
    TransformComponent(std::string component_id = "");

    //return the mask for this component
    long mask();

	/// Gets the transform.
	/// @return	null if it fails, else the transform.
	graphics::Transform* getTransform();

	/*
	 * Convience wrappers for internal transform
	 */
	inline TransformComponent* translate(float x, float y, float z) { _transform->translate(x, y, z); return this; }
    inline TransformComponent* rotate(float x_rot, float y_rot, float z_rot) { _transform->rotate(x_rot, y_rot, z_rot); return this; }
    inline TransformComponent* scale(float scale_x, float scale_y, float scale_z) { _transform->scale(scale_x, scale_y, scale_z); return this; }
    inline TransformComponent* uniform_scale(float scale) { _transform->uniform_scale(scale); return this; }
	inline glm::mat4 getMatrix() { return _transform->getMatrix(); }
};
#endif  // _TRANSFORM_COMPONENT_hpp