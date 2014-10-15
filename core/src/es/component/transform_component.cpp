#include "es/component/transform_component.h"

TransformComponent::TransformComponent() :
        _transform(new Graphics::Transform())
{
}

long TransformComponent::mask() {
    return TransformComponent::MASK;
}
