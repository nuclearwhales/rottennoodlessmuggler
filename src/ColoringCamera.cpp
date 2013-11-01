#include "ColoringCamera.h"

#include <Utility/Resource.h>
#include <AbstractShaderProgram.h>
#include <DefaultFramebuffer.h>
#include <Framebuffer.h>
#include <Texture.h>
#include <TextureFormat.h>
#include <Mesh.h>
#include <Shader.h>
#include <ImageReference.h>
#include <ColorFormat.h>
#include <SceneGraph/Object.h>
#include <SceneGraph/TranslationTransformation.h>

namespace Rotten {

class ColoringCamera::ColoringShader: public AbstractShaderProgram {
    public:
        /* Same as Shaders::Flat2D */
        typedef Attribute<0, Vector2> Position;
        typedef Attribute<1, Vector2> TextureCoordinates;

        enum: Int {
            LookupTextureLayer = 15,
            TextureLayer = 16
        };

        explicit ColoringShader();
};

void ColoringCamera::setup() {
    /* Palette */
    static BasicColor3<UnsignedByte> palette[] = {
        { 36,  35,  34}, /* Almost black */
        {137,  30,   7}, /* Dusty red */
        {163, 162, 161}, /* Light gray */
        {239, 239, 239} /* Almost white */
    };

    /* Lookup texture */
    auto lookupTexture = new Texture2D;
    lookupTexture->setMinificationFilter(Sampler::Filter::Nearest)
        .setMagnificationFilter(Sampler::Filter::Nearest)
        .setWrapping(Sampler::Wrapping::ClampToEdge)
        .setImage(0, TextureFormat::RGB, ImageReference2D(ColorFormat::RGB, ColorType::UnsignedByte, {4, 1}, palette));

    /* Framebuffer texture */
    auto texture = new Texture2D;
    texture->setMinificationFilter(Sampler::Filter::Nearest)
        .setMagnificationFilter(Sampler::Filter::Nearest)
        .setWrapping(Sampler::Wrapping::ClampToEdge);

    #ifndef MAGNUM_TARGET_GLES
    texture->setStorage(1, TextureFormat::RGB8, {160, 144});
    #else
    texture->setStorage(1, TextureFormat::RGB, {160, 144});
    #endif

    /* Framebuffer */
    auto framebuffer = new Framebuffer({{}, {160, 144}});
    framebuffer->attachTexture2D(Framebuffer::ColorAttachment(0), *texture, 0);
    if(framebuffer->checkStatus(FramebufferTarget::ReadDraw) != Framebuffer::Status::Complete) {
        Error() << "ColoringCamera framebuffer setup failure:" << framebuffer->checkStatus(FramebufferTarget::ReadDraw);
        std::exit(1);
    }

    /* Add the stuff to resource manager */
    Manager::instance().set("coloring-lookup-texture", lookupTexture)
        .set("coloring-texture", texture)
        .set("coloring-framebuffer", framebuffer)
        .set<AbstractShaderProgram>("coloring-shader", new ColoringShader);
}

ColoringCamera::ColoringCamera(Object2D& object): SceneGraph::Camera2D(object) {
    _lookupTexture = Manager::instance().get<Texture2D>("coloring-lookup-texture");
    _texture = Manager::instance().get<Texture2D>("coloring-texture");
    _framebuffer = Manager::instance().get<Framebuffer>("coloring-framebuffer");
    _shader = Manager::instance().get<AbstractShaderProgram, ColoringShader>("coloring-shader");
    _mesh = Manager::instance().get<Mesh>("square");

    setProjection({160.0f, 144.0f});
    setViewport(_framebuffer->viewport().size());
}

ColoringCamera::~ColoringCamera() = default;

void ColoringCamera::draw(SceneGraph::DrawableGroup2D& group) {
    _framebuffer->clear(FramebufferClear::Color);

    /* Draw everything to our framebuffer */
    _framebuffer->bind(FramebufferTarget::ReadDraw);
    SceneGraph::Camera2D::draw(group);

    /* Colorize everything */
    defaultFramebuffer.bind(FramebufferTarget::ReadDraw);
    _shader->use();
    _texture->bind(ColoringShader::TextureLayer);
    _lookupTexture->bind(ColoringShader::LookupTextureLayer);
    _mesh->draw();
}

ColoringCamera::ColoringShader::ColoringShader() {
    CORRADE_INTERNAL_ASSERT(Shader::maxCombinedTextureImageUnits() > TextureLayer);

    Utility::Resource rs("shaders");
    #ifndef MAGNUM_TARGET_GLES
    constexpr Version v = Version::GL210;
    #else
    constexpr Version v = Version::GLES200;
    #endif

    Shader vert(v, Shader::Type::Vertex);
    vert.addSource(rs.get("ColoringShader.vert"));
    CORRADE_INTERNAL_ASSERT_OUTPUT(vert.compile());
    attachShader(vert);

    Shader frag(v, Shader::Type::Fragment);
    frag.addSource(rs.get("ColoringShader.frag"));
    CORRADE_INTERNAL_ASSERT_OUTPUT(frag.compile());
    attachShader(frag);

    bindAttributeLocation(Position::Location, "position");
    bindAttributeLocation(TextureCoordinates::Location, "textureCoordinates");

    CORRADE_INTERNAL_ASSERT_OUTPUT(link());

    setUniform(uniformLocation("lookupTexture"), LookupTextureLayer);
    setUniform(uniformLocation("inputTexture"), TextureLayer);
}

}
