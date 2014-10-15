#ifndef _ENTITY_hpp
#define _ENTITY_hpp

#include <map>
#include "es/component.hpp"

typedef int FamilyId;

class Entity
{
private:
    long _enabled_components;
    std::map<const long,Component*> _components;
public:
	/// Default constructor.
	Entity(std::string id = "");

    ///the id of this entity
    std::string _id;

	/// Gets as the provided component
	/// @return	null if it fails, else as.
    Component* get_component(const long mask);

	/// @summary	The components attached to this entity
	std::map<FamilyId, Component*> Components;

    /// and's the component mask and the internal "available" mask
    bool has_components(const long component_mask);

    /// add's a particular componet to this list of components
    void add_component(Component* component);
};
#endif  // _ENTITY_hpp