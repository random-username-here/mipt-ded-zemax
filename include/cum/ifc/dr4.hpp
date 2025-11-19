#ifndef I_DR4_IFC
#define I_DR4_IFC

#include "dr4/window.hpp"
#include "cum/plugin.hpp"

namespace dr4 {

/**
 * @brief DR4 backend interface
 * Can create windows and draw on them.
 */
class DR4BackendPlugin: public cum::Plugin {

public:
    virtual dr4::Window *CreateWindow() = 0;
    virtual ~DR4BackendPlugin() = default;
};

};

#endif
