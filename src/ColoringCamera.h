#ifndef Rotten_ColoringCamera_h
#define Rotten_ColoringCamera_h

#include <Resource.h>
#include <SceneGraph/Camera2D.h>
#include <SceneGraph/Object.h>
#include <SceneGraph/TranslationTransformation.h>

#include "Rotten.h"

namespace Rotten {

class ColoringCamera: public Object2D, public SceneGraph::Camera2D {
    public:
        static void setup();

        ColoringCamera(Object2D* parent);

        ~ColoringCamera();

        void draw(SceneGraph::DrawableGroup2D& group);

    private:
        class ColoringShader;

        Resource<Framebuffer> _framebuffer;
        Resource<Texture2D> _lookupTexture, _texture;
        Resource<Mesh> _mesh;
        Resource<AbstractShaderProgram, ColoringShader> _shader;
};

}

#endif
