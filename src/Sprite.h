#ifndef Rotten_Sprite_h
#define Rotten_Sprite_h

#include <Resource.h>
#include <SceneGraph/TranslationTransformation.h>
#include <SceneGraph/Drawable.h>
#include <Shaders/Shaders.h>

#include "Rotten.h"

namespace Rotten {

class Sprite: public Object2D, SceneGraph::Drawable2D {
    public:
        explicit Sprite(const Vector2i& size, const ResourceKey& texture, Object2D* parent, SceneGraph::DrawableGroup2D* drawables = nullptr);

        ~Sprite();

    private:
        void draw(const Matrix3& transformationMatrix, SceneGraph::AbstractCamera2D& camera) override;

        Vector2i _size;
        Resource<Mesh> _mesh;
        Resource<Texture2D> _texture;
        Resource<AbstractShaderProgram, Shaders::Flat2D> _shader;
};

}

#endif
