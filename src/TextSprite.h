#ifndef Rotten_TextSprite_h
#define Rotten_TextSprite_h

#include <Buffer.h>
#include <Color.h>
#include <Mesh.h>
#include <Resource.h>
#include <SceneGraph/TranslationTransformation.h>
#include <SceneGraph/Drawable.h>
#include <Shaders/Shaders.h>
#include <Text/Text.h>
#include <Text/Alignment.h>

#include "Rotten.h"

namespace Rotten {

class TextSprite: public Object2D, SceneGraph::Drawable2D {
    public:
        explicit TextSprite(const std::string& text, Text::Alignment alignment, Object2D* parent, SceneGraph::DrawableGroup2D* drawables = nullptr);

        ~TextSprite();

        TextSprite& setBackgroundColor(const Color3& color) {
            _backgroundColor = color;
            return *this;
        }

        TextSprite& setColor(const Color3& color) {
            _color = color;
            return *this;
        }

    private:
        void draw(const Matrix3& transformationMatrix, SceneGraph::AbstractCamera2D& camera) override;

        Resource<Text::GlyphCache> _glyphCache;
        Buffer _indexBuffer, _vertexBuffer;
        Mesh _mesh;
        Resource<AbstractShaderProgram, Shaders::Vector2D> _shader;

        Color3 _backgroundColor,
            _color;
};

}

#endif
