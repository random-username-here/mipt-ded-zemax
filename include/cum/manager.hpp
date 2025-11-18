#ifndef I_CUM_MANAGER
#define I_CUM_MANAGER

#include <memory>
#include <stdexcept>
#include <string_view>
#include <vector>
#include <dlfcn.h>

#include "cum/plugin.hpp"

namespace cum {

#define CREATE_PLUGIN_FUNC_NAME CreatePlugin

static inline const std::string CreatePluginFuncNameStr = "CreatePlugin";

extern "C" cum::Plugin* CREATE_PLUGIN_FUNC_NAME();

/**
 * A manager is a class which loads plugins, owns them, and provides
 * them for other plugins to find their dependencies.
 *
 * Due to this being the thing loading plugins, its implementation
 * is not in a plugin.
 */
class Manager {

private:

    std::vector<std::unique_ptr<Plugin>> plugins_;

public:
 
    Plugin *LoadFromFile(const std::string_view path) {
        auto* lib = dlopen(path.data(), RTLD_LAZY);
        if (!lib) {
            throw std::runtime_error("Can't open lib '" + std::string(path) + "'");
        }
        auto* func = reinterpret_cast<cum::Plugin*(*)()>(dlsym(lib, CreatePluginFuncNameStr.c_str()));
        if (!func) {
            throw std::runtime_error("Can't load sym '" + CreatePluginFuncNameStr + "' in lib '" + std::string(path) + "'");
        }
        plugins_.push_back(std::unique_ptr<Plugin>(func()));
        return plugins_.back().get();
    }

    Plugin *GetById(std::string_view id) const {
        for (const auto& plugin : plugins_) {
            if (plugin->GetIdentifier() == id) {
                return plugin.get();
            }
        }
        return nullptr;
    }

    template<typename Interface>
    Interface *GetAnyOfType() const {
        for (auto& plugin : plugins_) {
            Interface *impl = dynamic_cast<Interface*>(plugin.get());
            if (impl) return impl;
        }
        return NULL;
    }

    template<typename Interface>
    std::vector<Interface*> GetAllOfType() const {
        std::vector<Interface*> res = {};
        for (auto& plugin : plugins_) {
            Interface *impl = dynamic_cast<Interface*>(plugin.get());
            if (impl) res.push_back(impl);
        }
        return res;
    }

    const std::vector<std::unique_ptr<Plugin>>& GetAll() const {
        return plugins_;
    }
};

};

#endif
