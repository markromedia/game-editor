#include "es/system/transform_system.hpp"
#include "logger.hpp"

TransformSystem * TransformSystem::_instance = NULL;

void TransformSystem::Init()
{
	if (!_instance)
	{
		_instance = new TransformSystem();
	}
}

TransformComponent* TransformSystem::CreateComponent(std::string uuid)
{
	if (uuid == "") {
        uuid = generateId();
    }
    TransformComponent* entity = new TransformComponent(uuid);
    _instance->_components[uuid] = entity;
    return entity;
}

TransformComponent* TransformSystem::Find(std::string id)
{
	return _instance->_components.begin()->second;
//	TransformComponent* component = _instance->_components[id];
//    if (!component) {
//        LOG_ERROR("failed to find component with id: " + id);
//    }
//    return component;
}