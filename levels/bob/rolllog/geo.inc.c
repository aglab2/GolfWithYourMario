#include "src/game/envfx_snow.h"

const GeoLayout rolllog_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, rolllog_golfer_wood_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rolllog_golfer_wood_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
