#include "MutableTextSprite.h"

#include <SceneGraph/AbstractCamera.h>
#include <Shaders/Vector.h>
#include <Text/AbstractFont.h>
#include <Text/TextRenderer.h>
#include <Text/GlyphCache.h>

namespace Rotten {

MutableTextSprite::MutableTextSprite(const UnsignedInt capacity, Object2D* parent, SceneGraph::DrawableGroup2D* drawables): Object2D(parent), SceneGraph::Drawable2D(*this, drawables), _backgroundColor(Color3(0.6f)), _color(Color3(0.0f)) {
    _font = Manager::instance().get<Text::AbstractFont>("font");
    _glyphCache = Manager::instance().get<Text::GlyphCache>("glyph-cache");
    _shader = Manager::instance().get<AbstractShaderProgram, Shaders::Vector2D>("text");

    _renderer.reset(new Text::TextRenderer2D(*_font, *_glyphCache, 6.0f));
    _renderer->reserve(capacity, Buffer::Usage::StaticDraw, Buffer::Usage::StaticDraw);
}

MutableTextSprite::~MutableTextSprite() = default;

Rectanglei MutableTextSprite::rectangle() { return Rectanglei(_renderer->rectangle()); }

MutableTextSprite& MutableTextSprite::setText(const std::string& text) {
    _renderer->render(text);
    return *this;
}

void MutableTextSprite::draw(const Matrix3& transformationMatrix, SceneGraph::AbstractCamera2D& camera) {
    _shader->setBackgroundColor(_backgroundColor)
        .setColor(_color)
        .setTransformationProjectionMatrix(camera.projectionMatrix()*transformationMatrix)
        .use();
    _glyphCache->texture().bind(Shaders::Vector2D::VectorTextureLayer);
    _renderer->mesh().draw();
}

}
