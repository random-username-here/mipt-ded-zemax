#ifndef I_CUM_PLUGIN
#define I_CUM_PLUGIN

#include <string_view>
#include <vector>
#include <memory>

namespace cum {

/**
 * @brief A plugin, loaded by Manager.
 *
 * All plugins which do something meaningfull should implement
 * interfaces, inherited from this. For example:
 *
 * @usage @code
 *      // in interface definition file
 *      class ColorSchemePlugin : public Plugin {
 *          virtual Color GetColor(std::string_view name) = 0;
 *      };
 *
 *      // in plugin
 *      class MyColorScheme : public ColorSchemePlugin {
 *          ...
 *      };
 *      Plugin *CreatePlugin() { return new MyColorScheme; } 
 *
 *      // in app
 *      int main() {
 *          ...
 *          auto *scheme = manager.GetAnyOfType<ColorSchemePlugin>();
 *          scheme.GetColor("red");
 *      }
 * @endcode
 */
class Plugin {
public:
    virtual ~Plugin() = default;

    /** Identifier used for naming plugin in dependencies */
    virtual std::string_view GetIdentifier() const = 0;

    /** User-readable name, to be shown in UI */
    virtual std::string_view GetName() const = 0;

    /** User-readable info about what this thing does */
    virtual std::string_view GetDescription() const = 0;

    /** Vector of plugin identifiers this plugin depends on */
    virtual std::vector<std::string_view> GetDependencies() const = 0;
    
    /**
     * Vector of plugins this conflicts with.
     * (so they both cannot be enabled at same time). Note what things
     * like themes do not conflict - they are both enabled, but values
     * of only one of them are used.
     * For most plugins this will be empty.
     */
    virtual std::vector<std::string_view> GetConflicts() const = 0;

    /**
     * Do some things after plugins were loaded.
     * For example, find other plugins in the list.
     */
    virtual void AfterLoad() = 0;
};

using PluginPtr = std::unique_ptr<Plugin>;

} // namespace cum

#endif
