#ifndef I_CUM_PLUGIN
#define I_CUM_PLUGIN

#include <string>
#include <vector>

#include "version.hpp"

namespace cum {

class Plugin {

public:

    virtual const std::string &GetName() const = 0;
    virtual const std::string &GetDescription() const = 0;
    virtual const PluginVersion &GetVersion() const = 0;

    // TODO: finish plugins interdependency
    virtual bool CheckCompatibles(const std::vector<Plugin*>) const = 0;
    

};

};

#endif
