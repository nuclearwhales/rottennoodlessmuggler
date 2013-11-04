#include "TextSprite.h"

#include <SceneGraph/AbstractCamera.h>
#include <Shaders/Vector.h>
#include <Text/AbstractFont.h>
#include <Text/Renderer.h>
#include <Text/GlyphCache.h>

namespace Rotten {

TextSprite::TextSprite(const std::string& text, Text::Alignment alignment, Object2D* parent, SceneGraph::DrawableGroup2D* drawables): Object2D(parent), SceneGraph::Drawable2D(*this, drawables), _indexBuffer(Buffer::Target::ElementArray), _vertexBuffer(Buffer::Target::Array), _backgroundColor(0.6f), _color(0.0f) {
    auto font = Manager::instance().get<Text::AbstractFont>("font");
    _glyphCache = Manager::instance().get<Text::GlyphCache>("glyph-cache");
    _shader = Manager::instance().get<AbstractShaderProgram, Shaders::Vector2D>("text");

    std::tie(_mesh, std::ignore) = Text::Renderer2D::render(*font, *_glyphCache, 6.0f, text, _vertexBuffer, _indexBuffer, Buffer::Usage::StaticDraw, alignment);
}

TextSprite::~TextSprite() = default;

void TextSprite::draw(const Matrix3& transformationMatrix, SceneGraph::AbstractCamera2D& camera) {
    _shader->setBackgroundColor(_backgroundColor)
        .setColor(_color)
        .setTransformationProjectionMatrix(camera.projectionMatrix()*transformationMatrix)
        .use();
    _glyphCache->texture().bind(Shaders::Vector2D::VectorTextureLayer);
    _mesh.draw();
}

}
