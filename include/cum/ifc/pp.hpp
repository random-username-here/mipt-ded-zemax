#ifndef I_PP_IFC
#define I_PP_IFC

#include "cum/plugin.hpp"
#include "hui/geomprim.hpp"
#include "dr4/window.hpp"

namespace hui {

/**
 * @brief Plugin which provides tools for screenshotter.
 */
class PPToolPlugin: public cum::Plugin {

public:

    // TODO
	virtual hui::GeomPrim* CreateGeomPrim(size_t geomPrimType, dr4::Window* dr4Window) = 0;
	inline virtual ~PPToolPlugin() {};

};

}; // namespace hui

#endif
