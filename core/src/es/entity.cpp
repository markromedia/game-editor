#include "es/entity.hpp"

Entity::Entity(std::string id) : _id(id),  _enabled_components(0)
{
}

bool Entity::has_components(const long component_mask) {
    return !((_enabled_components & component_mask) ^ component_mask); //mask enabled. if mask == component mask(XOR), then enabled
}

void Entity::add_component(Component *component) {
    if (!has_components(component->mask()))
    {
        _components[component->mask()] = component;
        _enabled_components |= component->mask();
    }
}

Component* Entity::get_component(const long mask) {
    if (has_components(mask))
    {
        return _components[mask];
    }
    else
    {
        return NULL;
    }
}
