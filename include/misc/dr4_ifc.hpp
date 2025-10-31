#ifndef I_DR4_IFC
#define I_DR4_IFC

#include "dr4/texture.hpp"
#include "dr4/window.hpp"

namespace dr4 {

/**
 * @brief DR4 backend interface
 *
 * To be rewritten later to use approporiate plugin system.
 */
class DR4Backend {

    virtual const std::string &Name() const = 0;
    virtual dr4::Texture *CreateTexture() = 0;
    virtual dr4::Window *CreateWindow() = 0;

};

/**
 * @brief Name of a function all DR4 backend plugins must export
 * 
 * It's signature is:
 *      
 *      extern "C" DR4Backend* CreateDR4Backend(void);
 *
 * Created object must be free'd with `delete` when it is not
 * needed anymore.
 *
 */
static const char *DR4BackendFunctionName = "CreateDR4Backend";

};

#endif
