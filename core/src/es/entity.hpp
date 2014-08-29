#ifndef _ENTITY_hpp
#define _ENTITY_hpp

#include <map>

typedef int FamilyId;

//forward declarations
class EntityManager;
class Component;

class Entity
{
public:

	/// Default constructor.
	Entity();

	/// Gets as the provided component
	/// @return	null if it fails, else as.
	template<typename Type> Type *GetAs();

	/// @summary	The components attached to this entity
	std::map<FamilyId, Component*> Components;
};
#endif  // _ENTITY_hpp