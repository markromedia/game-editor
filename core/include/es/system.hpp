#ifndef _SYSTEM_hpp
#define _SYSTEM_hpp

#include <map>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

class System
{
private:
public:
    static inline std::string generateId() {
        boost::uuids::uuid id = boost::uuids::random_generator()();
        return boost::lexical_cast<std::string>(id);
    }
};
#endif  // _SYSTEM_hpp