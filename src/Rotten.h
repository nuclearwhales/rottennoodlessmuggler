#ifndef Rotten_Rotten_h
#define Rotten_Rotten_h

#include "Magnum.h"
#include "SceneGraph/SceneGraph.h"
#include "Trade/Trade.h"

namespace Rotten {

using namespace Magnum;

typedef SceneGraph::Object<SceneGraph::TranslationTransformation2D> Object2D;
typedef SceneGraph::Scene<SceneGraph::TranslationTransformation2D> Scene2D;

typedef ResourceManager<Buffer, Mesh, Texture2D, AbstractShaderProgram, Trade::AbstractImporter> Manager;

}

#endif
