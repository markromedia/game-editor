#include "entity.hpp"

#include "entity_manager.hpp"

Entity::Entity()
{
}

template<typename Type> Type* Entity::GetAs() {
	return EntityManager::GetComponent<Type>(this);
}