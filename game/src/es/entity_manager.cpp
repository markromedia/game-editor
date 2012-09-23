#include "entity_manager.hpp"

#include "entity.hpp"

EntityManager* EntityManager::instance = NULL;

void EntityManager::_checkCreateInstance() 
{
	if (EntityManager::instance == NULL)
		EntityManager::instance = new EntityManager();			
}

EntityManager::EntityManager() {
}

template<typename T>
T* EntityManager::GetComponent( Entity *e )
{
	_checkCreateInstance();
	return (T*)e->Components[T::familyId];
}

template<typename T> 
void EntityManager::GetEntities(std::vector<Entity*> &result) 
{
	_checkCreateInstance();
	auto iterPair = EntityManager::instance->ComponentStore.equal_range(T::familyId);
	for(auto iter = iterPair.first; iter != iterPair.second; ++iter) {
		result.push_back(iter->second);
	}
}

template<typename T> 
void EntityManager::AddComponent(Entity *e, T* comp) 
{
	_checkCreateInstance();
	EntityManager::instance->ComponentStore.insert(std::pair<FamilyId, Entity*>(T::familyId, e));
	e->Components.insert(std::pair<FamilyId, Component*>(T::familyId, comp));
}

