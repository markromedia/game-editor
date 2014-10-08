#ifndef _ENTITY_SYSTEM_hpp
#define _ENTITY_SYSTEM_hpp

#include <map>
#include <vector>

//forward declarations
class Entity;
class Component;

typedef int FamilyId;

class EntityManager {

private:
	/// @summary	The instance.
	static EntityManager* instance;

	/// Checks to see if instance is not created. creates it then
	static void _checkCreateInstance();
protected:
	std::multimap<FamilyId, Entity*> ComponentStore;
public:
	/// Default constructor.
	EntityManager();

	/// Returns the component of provided type which is attached to the entity
	/// @param [in,out]	e	If non-null, the Entity * to process.
	/// @return	null if it fails, else the component.
	template<typename T> 
	static T* GetComponent(Entity *e);

	/// Gets all entities which have a specific component attached to them
	/// @param [out]	result	if non-null, the result.
	template<typename T> 
	static void GetEntities(std::vector<Entity*> &result);

	/// Adds a component to the entity
	/// @param [in,out]	e   	If non-null, the Entity * to process.
	/// @param [in,out]	comp	If non-null, the component.
	template<typename T> 
	static void AddComponent(Entity *e, T* comp);
};

#endif  // _ENTITY_SYSTEM_hpp