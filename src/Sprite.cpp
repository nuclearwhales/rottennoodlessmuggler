#include "Sprite.h"

#include <Mesh.h>
#include <Texture.h>
#include <SceneGraph/Camera2D.h>
#include <Shaders/Flat.h>

namespace Rotten {

/* Square texture is 2x2, thus halving the size */
Sprite::Sprite(const Vector2i& size, const ResourceKey& texture, Object2D* parent, SceneGraph::DrawableGroup2D* drawables): Object2D(parent), Drawable(*this, drawables), _size(size/2) {
    _mesh = Manager::instance().get<Mesh>("square");
    _texture = Manager::instance().get<Texture2D>(texture);
    _shader = Manager::instance().get<AbstractShaderProgram, Shaders::Flat2D>("flat-textured");
}

Sprite::~Sprite() = default;

void Sprite::draw(const Matrix3& transformationMatrix, SceneGraph::AbstractCamera2D& camera) {
    _shader->setTransformationProjectionMatrix(camera.projectionMatrix()*transformationMatrix*Matrix3::scaling(Vector2(_size)))
        .use();
    _texture->bind(Shaders::Flat2D::TextureLayer);
    _mesh->draw();
}

}
