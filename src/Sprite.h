#ifndef Rotten_Sprite_h
#define Rotten_Sprite_h

#include <Resource.h>
#include <SceneGraph/TranslationTransformation.h>
#include <SceneGraph/Drawable.h>
#include <Shaders/Shaders.h>

#include "Rotten.h"

namespace Rotten {

class Sprite: public Object2D, public SceneGraph::Drawable2D {
    public:
        explicit Sprite(Object2D* parent, SceneGraph::DrawableGroup2D* drawables = nullptr);

        explicit Sprite(const Vector2i& size, const ResourceKey& texture, Object2D* parent, SceneGraph::DrawableGroup2D* drawables = nullptr);

        void reset(const Vector2i& size, const ResourceKey& texture);

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
