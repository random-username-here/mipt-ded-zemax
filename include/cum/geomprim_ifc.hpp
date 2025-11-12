#ifndef I_GEOMPRIM_IFC
#define I_GEOMPRIM_IFC

#include "plugin.hpp"

namespace dr4 {

/**
 * @brief DR4 backend interface
 *
 * To be rewritten later to use approporiate plugin system.
 */
class GeomPrimBackend: public cum::Plugin {
	virtual GeomPrim* CreateGeomPrim(size_t geomPrimType) = 0;
	inline virtual ~GeomPrimBackend() {};
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
inline const char *GeomPrimBackendFunctionName = "CreateGeomPrimBackend";

#define GEOM_PRIM_BACKEND_FUNCTION CreateGeomPrimBackend

}; // namespace dr4

#endif
