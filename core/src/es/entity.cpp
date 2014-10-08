#include "es/entity.hpp"

#include "es/entity_manager.hpp"

Entity::Entity()
{
}

template<typename Type> Type* Entity::GetAs() {
	return EntityManager::GetComponent<Type>(this);
}