#include "es/system/entity_system.hpp"
#include "logger.hpp"

EntitySystem* EntitySystem::_instance = NULL;

void Init() {
    if (!_instance) {
        _instance = new EntitySystem();
    }
}

Entity* EntitySystem::CreateEntity(std::string uuid) {
    if (uuid == "") {
        uuid = generateId();
    }
    Entity* entity = new Entity(uuid);
    _instance->_entities[uuid] = entity;
    return entity;
}

Entity* EntitySystem::Find(std::string id) {
    Entity* entity = _instance->_entities[id];
    if (!entity) {
        LOG_ERROR("failed to find entity with id: " + id);
    }
    return entity;
}