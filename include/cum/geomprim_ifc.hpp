#ifndef I_GEOMPRIM_IFC
#define I_GEOMPRIM_IFC

#include "cum/plugin.hpp"

#include "hui/geomprim.hpp"

#include "dr4/window.hpp"

namespace hui {

class GeomPrimBackend: public cum::Plugin {

public:

	virtual hui::GeomPrim* CreateGeomPrim(size_t geomPrimType, dr4::Window* dr4Window) = 0;
	inline virtual ~GeomPrimBackend() {};

};


inline const char *GeomPrimBackendFunctionName = "CreateGeomPrimBackend";

#define GEOM_PRIM_BACKEND_FUNCTION CreateGeomPrimBackend

}; // namespace hui

#endif
