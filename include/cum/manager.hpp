#ifndef I_CUM_MANAGER
#define I_CUM_MANAGER

#include <memory>
#include <stdexcept>
#include <string_view>
#include <vector>
#include <dlfcn.h>
#include "cum/plugin.hpp"
namespace cum {

/**
 * A manager is a class which loads plugins, owns them, and provides
 * them for other plugins to find their dependencies.
 *
 * Due to this being the thing loading plugins, its implementation
 * is not in a plugin.
 */
class Manager {

    // DO NOT REORDER!
    // Otherwise .so handles will be destroyed before plugins,
    // and nonexistent destructors will be called.
    std::vector<std::unique_ptr<void, int (*)(void*)>> soHandles;
    std::vector<std::unique_ptr<Plugin>> plugins;

    typedef Plugin *(*CreatePluginFn)();

public:

    /** Exception thrown when `LoadFromFile()` fails. */
    class LoadError : public std::runtime_error {
        using std::runtime_error::runtime_error; // same constructor
    };

    /** Exception thrown when there is unmet dependency. */
    class DependencyError : public std::runtime_error {
        using std::runtime_error::runtime_error; // same constructor
    };

    /**
     * @brief Load a plugin from file. 
     * If file loading fails, will throw `LoadError`.
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
        for (auto &plugin : plugins) {
            Interface *impl = dynamic_cast<Interface*>(plugin.get());
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
        for (auto &plugin : plugins) {
            Interface *impl = dynamic_cast<Interface*>(plugin.get());
            if (impl) res.push_back(impl);
        }
        return res;
    }

    /**
     * Get all the plugins
     */
    const std::vector<std::unique_ptr<Plugin>> &GetAll() const;

    /**
     * All plugins which we want are now loaded.
     * Check dependencies, runs `AfterLoad()`.
     * If a dependency is missing, will throw `DependencyError`.
     */
    void TriggerAfterLoad();
};

};

#endif
