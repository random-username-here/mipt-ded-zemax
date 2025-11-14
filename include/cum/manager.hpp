#ifndef I_CUM_MANAGER
#define I_CUM_MANAGER

#include "cum/plugin.hpp"
#include <string_view>
#include <vector>

namespace cum {

/**
 * A manager is a class which loads plugins, owns them, and provides
 * them for other plugins to find their dependencies.
 *
 * Due to this being the thing loading plugins, its implementation
 * is not in a plugin.
 */
class Manager {
    std::vector<Plugin*> plugins;
public:
    Manager();
    ~Manager();

    /**
     * @brief Load a plugin from file. 
     * If plugin failed to load, will return NULL.
     * TODO: report an error? Like "file does not exist".
     */
    Plugin *LoadFromFile(const std::string_view path);

    /** 
     * @brief Find plugin by its identifier.
     * Will return NULL if such plugin was not found.
     */
    Plugin *GetById(std::string_view id) const;

    /**
     * @brief Get plugin which implements given interface.
     */
    template<typename Interface>
    Interface *GetAnyOfType() const {
        for (auto plugin : plugins) {
            Interface *impl = dynamic_cast<Interface>(plugin);
            if (impl) return impl;
        }
        return NULL;
    }

    /**
     * @brief Get all plugins implementing given interface.
     * Creates a vector of plugins, so do not call this in a loop. 
     */
    template<typename Interface>
    std::vector<Interface*> GetAllOfType() const {
        std::vector<Interface*> res;
        for (auto plugin : plugins) {
            Interface *impl = dynamic_cast<Interface>(plugin);
            if (impl) res.push_back(impl);
        }
        return res;
    }

    /**
     * Get all the plugins
     */
    const std::vector<Plugin*> GetAll() const;
};

};

#endif
