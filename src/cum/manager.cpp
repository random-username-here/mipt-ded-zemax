#include "cum/manager.hpp"
#include "cum/plugin.hpp"
#include <sstream>
#include <string_view>
#include <dlfcn.h>
#include <unordered_map>

namespace cum {

Plugin *Manager::LoadFromFile(const std::string_view path) {
    void *so = dlopen(path.data(), RTLD_LAZY);
    if (so == nullptr)
        throw LoadError(dlerror());

    CreatePluginFn createPlugin = (CreatePluginFn) dlsym(so, "CreatePlugin");
    if (createPlugin == nullptr) {
        dlclose(so);
        throw LoadError("CreatePlugin() function missing in the plugin");
    }
    
    Plugin *plugin = createPlugin();
    plugin->soHandle = std::unique_ptr<void, void(*)(void*)>(so, [](void* so) {
        dlclose(so);
    });
    plugin->manager = this;
    plugins.push_back(std::unique_ptr<Plugin>(plugin));
    return plugin;
}

Plugin *Manager::GetById(std::string_view id) const {
    for (auto &plugin : plugins)
        if (plugin->GetIdentifier() == id)
            return plugin.get();
    return nullptr;
}
    
const std::vector<std::unique_ptr<Plugin>> &Manager::GetAll() const {
    return plugins;
}

void Manager::TriggerAfterLoad() {
    std::unordered_map<std::string_view, Plugin*> names;

    for (auto &plugin : plugins)
        names[plugin->GetIdentifier()] = plugin.get();

    for (auto &plugin : plugins) {
        for (auto &dep : plugin->GetDependencies()) {
            if (!names.count(dep)) {
                std::ostringstream err;
                err << "Plugin " << plugin->GetIdentifier() << " (`" << plugin->GetName() << "`) "
                    << "is missing a dependency " << dep;
                throw DependencyError(err.str());
            }
        }
        for (auto &conf : plugin->GetConflicts()) {
            if (names.count(conf)) {
                std::ostringstream err;
                err << "Plugin " << plugin->GetIdentifier() << " (`" << plugin->GetName() << "`) "
                    << "is conflicting with " << conf << " (`" << names[conf]->GetName() << "`)";
                throw DependencyError(err.str());
            }
        }
    }

    for (auto &plugin : plugins)
        plugin->AfterLoad();
}

};

