#ifndef Rotten_MutableTextSprite_h
#define Rotten_MutableTextSprite_h

#include <memory>
#include <Color.h>
#include <Resource.h>
#include <SceneGraph/TranslationTransformation.h>
#include <SceneGraph/Drawable.h>
#include <Shaders/Shaders.h>
#include <Text/Alignment.h>

#include "Rotten.h"

namespace Rotten {

class MutableTextSprite: public Object2D, SceneGraph::Drawable2D {
    public:
        explicit MutableTextSprite(UnsignedInt capacity, Text::Alignment alignment, Object2D* parent, SceneGraph::DrawableGroup2D* drawables = nullptr);

        ~MutableTextSprite();

        MutableTextSprite& setBackgroundColor(const Color3& color) {
            _backgroundColor = color;
            return *this;
        }

        MutableTextSprite& setColor(const Color3& color) {
            _color = color;
            return *this;
        }

        MutableTextSprite& setText(const std::string& text);

    private:
        void draw(const Matrix3& transformationMatrix, SceneGraph::AbstractCamera2D& camera) override;

        Resource<Text::AbstractFont> _font;
        Resource<Text::GlyphCache> _glyphCache;
        std::unique_ptr<Text::Renderer2D> _renderer;
        Resource<AbstractShaderProgram, Shaders::Vector2D> _shader;

        Color3 _backgroundColor,
            _color;
};

}

#endif
