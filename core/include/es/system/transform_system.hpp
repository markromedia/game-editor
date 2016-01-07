#ifndef _TRANSFORM_SYSTEM_hpp
#define _TRANSFORM_SYSTEM_hpp

#include <map>
#include "es/system.hpp"
#include "es/component/transform_component.h"

class TransformSystem : public System
{
private:
    std::map<std::string, TransformComponent*> _components;
    static TransformSystem* _instance;
public:
    ///init this system
    static void Init();

    ///Creates a component. If uuid is empty, will
    ///assign a new uuid
    static TransformComponent* CreateComponent(std::string uuid = "");

    ///finds an entity by id or returns null
    static TransformComponent* Find(std::string id);
};
#endif  // _TRANSFORM_SYSTEM_hpp