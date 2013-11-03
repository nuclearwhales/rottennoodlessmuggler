#include "Sprite.h"

#include <Mesh.h>
#include <Texture.h>
#include <SceneGraph/Camera2D.h>
#include <Shaders/Flat.h>

namespace Rotten {

Sprite::Sprite(Object2D* parent, SceneGraph::DrawableGroup2D* drawables): Object2D(parent), Drawable(*this, drawables) {
    _mesh = Manager::instance().get<Mesh>("square");
    _shader = Manager::instance().get<AbstractShaderProgram, Shaders::Flat2D>("flat-textured");
}

Sprite::Sprite(const Vector2i& size, const ResourceKey& texture, Object2D* parent, SceneGraph::DrawableGroup2D* drawables): Sprite(parent, drawables) {
    reset(size, texture);
}

void Sprite::reset(const Vector2i& size, const ResourceKey& texture) {
    _size = size/2; /* Square texture is 2x2, thus halving the size */
    _texture = Manager::instance().get<Texture2D>(texture);
}

Sprite::~Sprite() = default;

void Sprite::draw(const Matrix3& transformationMatrix, SceneGraph::AbstractCamera2D& camera) {
    if(!_texture) return;

    _shader->setTransformationProjectionMatrix(camera.projectionMatrix()*transformationMatrix*Matrix3::scaling(Vector2(_size)))
        .use();
    _texture->bind(Shaders::Flat2D::TextureLayer);
    _mesh->draw();
}

}
