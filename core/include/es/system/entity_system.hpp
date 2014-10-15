#ifndef _ENTITY_SYSTEM_hpp
#define _ENTITY_SYSTEM_hpp

#include <map>
#include "es/system.hpp"
#include "es/entity.hpp"

class EntitySystem : public System
{
private:
    map<std::string, Entity*> _entities;
    static EntitySystem* _instance;
public:
    ///init this system
    static void Init();

    ///Creates an entity. If uuid is empty, will
    ///assign a new uuid
    static Entity* CreateEntity(std::string uuid = "");

    ///finds an entity by id or returns null
    static Entity* Find(std::string id);
};
#endif  // _ENTITY_SYSTEM_hpp