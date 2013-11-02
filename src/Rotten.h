#ifndef Rotten_Rotten_h
#define Rotten_Rotten_h

#include "Magnum.h"
#include "SceneGraph/SceneGraph.h"
#include "Text/Text.h"
#include "Trade/Trade.h"

namespace Rotten {

using namespace Magnum;

typedef SceneGraph::Object<SceneGraph::BasicTranslationTransformation2D<Float, Int>> Object2D;
typedef SceneGraph::Scene<SceneGraph::BasicTranslationTransformation2D<Float, Int>> Scene2D;

typedef ResourceManager<Buffer, Framebuffer, Mesh, Texture2D, AbstractShaderProgram, Trade::AbstractImporter, Text::AbstractFont, Text::GlyphCache> Manager;

}

#endif
