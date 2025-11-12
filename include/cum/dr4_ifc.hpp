#ifndef I_DR4_IFC
#define I_DR4_IFC

#include "dr4/window.hpp"
#include "plugin.hpp"

namespace dr4 {

/**
 * @brief DR4 backend interface
 *
 * To be rewritten later to use approporiate plugin system.
 */
class DR4Backend: public cum::Plugin {

public:
    virtual dr4::Window *CreateWindow() = 0;
    inline virtual ~DR4Backend() {};

};


/**
 * @brief Name of a function all DR4 backend plugins must export
 *
 * It's signature is:
 *
 *      extern "C" DR4Backend* DR4_BACKEND_FUNCTION(void);
 *
 * Created object must be free'd with `delete` when it is not
 * needed anymore.
 *
 */
inline const char *DR4BackendFunctionName = "CreateDR4Backend";

#define DR4_BACKEND_FUNCTION CreateDR4Backend

};

#endif
