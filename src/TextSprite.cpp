#include "TextSprite.h"

#include <SceneGraph/AbstractCamera.h>
#include <Shaders/Vector.h>
#include <Text/AbstractFont.h>
#include <Text/TextRenderer.h>
#include <Text/GlyphCache.h>

namespace Rotten {

TextSprite::TextSprite(const std::string& text, Object2D* parent, SceneGraph::DrawableGroup2D* drawables): Object2D(parent), SceneGraph::Drawable2D(*this, drawables), _indexBuffer(Buffer::Target::ElementArray), _vertexBuffer(Buffer::Target::Array) {
    auto font = Manager::instance().get<Text::AbstractFont>("font");
    _glyphCache = Manager::instance().get<Text::GlyphCache>("glyph-cache");
    _shader = Manager::instance().get<AbstractShaderProgram, Shaders::Vector2D>("text");

    Rectangle rect;
    std::tie(_mesh, rect) = Text::TextRenderer2D::render(*font, *_glyphCache, 8.0f, text, _vertexBuffer, _indexBuffer, Buffer::Usage::StaticDraw);
    translate(Vector2i(rect.size())/-2);
}

TextSprite::~TextSprite() = default;

void TextSprite::draw(const Matrix3& transformationMatrix, SceneGraph::AbstractCamera2D& camera) {
    _shader->setBackgroundColor(Color3(0.6f))
        .setColor(Color3(0.0f))
        .setTransformationProjectionMatrix(camera.projectionMatrix()*transformationMatrix)
        .use();
    _glyphCache->texture().bind(Shaders::Vector2D::VectorTextureLayer);
    _mesh.draw();
}

}
