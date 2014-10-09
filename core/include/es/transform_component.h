#ifndef _TRANSFORM_COMPONENT_hpp
#define _TRANSFORM_COMPONENT_hpp

#include <map>
#include "component.hpp"
#include "graphics/transform.hpp"

class TransformComponent : public Component
{
private:
    Graphics::Transform* _transform;
public:
    static const long MASK = 0x00000000000000000000000000000001;

    /// default const
    TransformComponent();

    //return the mask for this component
    long mask();
};
#endif  // _TRANSFORM_COMPONENT_hpp