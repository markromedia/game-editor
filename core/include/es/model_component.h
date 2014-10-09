#ifndef _MODEL_COMPONENT_hpp
#define _MODEL_COMPONENT_hpp

#include <map>
#include "component.hpp"
#include "graphics/vertex_buffer.hpp"

class ModelComponent : public Component
{
private:
    Graphics::VertexBuffer* model_data;
public:
    static const long MASK = 0x00000000000000000000000000000010;

    /// default const
    ModelComponent();

    //return the mask for this component
    long mask();
};
#endif  // _MODEL_COMPONENT_hpp