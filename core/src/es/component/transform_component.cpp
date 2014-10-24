#include "es/component/transform_component.h"

TransformComponent::TransformComponent(std::string uuid) : 
		_id(uuid),
        _transform(new graphics::Transform())
{
}

long TransformComponent::mask() {
    return TransformComponent::MASK;
}

graphics::Transform* TransformComponent::getTransform()
{
	return _transform;
}
