#include "es/component/transform_component.h"

TransformComponent::TransformComponent(std::string uuid) : 
		_id(uuid),
        _transform(new Graphics::Transform())
{
}

long TransformComponent::mask() {
    return TransformComponent::MASK;
}

Graphics::Transform* TransformComponent::getTransform()
{
	return _transform;
}
