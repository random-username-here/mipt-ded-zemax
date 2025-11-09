#ifndef I_CUM_PLUGIN
#define I_CUM_PLUGIN

#include <string>
#include <vector>
#include <memory>

#include "cum/version.hpp"

namespace cum {

class Plugin {
public:
    virtual ~Plugin() = default;
    
    virtual const std::string &GetName() const = 0;
    virtual const std::string &GetDescription() const = 0;
    virtual const PluginVersion &GetVersion() const = 0;

    virtual std::vector<std::string> GetDependencies() const = 0;
    virtual bool IsCompatibleWith(const Plugin& other) const = 0;
    
    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;
};

using PluginPtr = std::unique_ptr<Plugin>;

} // namespace cum

#endif