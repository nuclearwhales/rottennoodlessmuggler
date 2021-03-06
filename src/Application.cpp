#include "Application.h"

#include <ColorFormat.h>
#include <DefaultFramebuffer.h>
#include <Framebuffer.h>
#include <ImageReference.h>
#include <Mesh.h>
#include <Texture.h>
#include <TextureFormat.h>
#include <MeshTools/Interleave.h>
#include <Primitives/Square.h>
#include <Shaders/Flat.h>
#include <Shaders/Vector.h>
#include <Text/AbstractFont.h>
#include <Text/GlyphCache.h>
#include <Trade/MeshData2D.h>

#include "BagScreen.h"
#include "ColoringCamera.h"
#include "GameScreen.h"
#include "SplashScreen.h"
#include "TextureLoader.h"

#include "configure.h"

#ifdef MAGNUM_BUILD_STATIC
/* Import shader resources in static build */
#include <Shaders/magnumShadersResourceImport.hpp>

/* Import plugins in static build */
static int importStaticPlugins() {
    CORRADE_PLUGIN_IMPORT(MagnumFont)
    CORRADE_PLUGIN_IMPORT(TgaImporter)
    return 0;
} CORRADE_AUTOMATIC_INITIALIZER(importStaticPlugins)
#endif

namespace Rotten {

Application::Application(const Arguments& arguments): Platform::ScreenedApplication(arguments,
    Configuration().setSize(Vector2i(160, 144)*4).setTitle("ROTTEN NOODLES SMUGGLER")), importerManager(ROTTEN_PLUGINS_IMPORTER_DIR), fontManager(ROTTEN_PLUGINS_FONT_DIR)
{
    /* Load TGA importer plugin */
    std::unique_ptr<Trade::AbstractImporter> tgaImporter;
    if(!(importerManager.load("TgaImporter") & PluginManager::LoadState::Loaded) ||
       !(tgaImporter = importerManager.instance("TgaImporter"))) {
        Error() << "Cannot load TgaImporter plugin";
        std::exit(1);
    }

    /* Fallback texture */
    UnsignedByte black = 0;
    auto texture = new Texture2D;
    texture->setMinificationFilter(Sampler::Filter::Nearest)
        .setMagnificationFilter(Sampler::Filter::Nearest)
        .setWrapping(Sampler::Wrapping::ClampToEdge);

    #ifndef MAGNUM_TARGET_GLES
    texture->setImage(0, TextureFormat::Red, ImageReference2D(ColorFormat::Red, ColorType::UnsignedByte, Vector2i(1), &black));
    #else
    texture->setImage(0, TextureFormat::Luminance, ImageReference2D(ColorFormat::Luminance, ColorType::UnsignedByte, Vector2i(1), &black));
    #endif

    /* Prepare the rectangle mesh */
    Trade::MeshData2D squareData = Primitives::Square::solid(Primitives::Square::TextureCoords::Generate);
    auto squareBuffer = new Buffer;
    auto squareMesh = new Mesh;
    MeshTools::interleave(*squareMesh, *squareBuffer, Buffer::Usage::StaticDraw, squareData.positions(0), squareData.textureCoords2D(0));
    squareMesh->setPrimitive(squareData.primitive())
        .addVertexBuffer(*squareBuffer, 0, Shaders::Flat2D::Position(), Shaders::Flat2D::TextureCoordinates());

    /* Load font plugin */
    std::unique_ptr<Text::AbstractFont> font;
    if(!(fontManager.load("MagnumFont") & PluginManager::LoadState::Loaded) ||
       !(font = fontManager.instance("MagnumFont"))) {
        Error() << "Cannot load MagnumFont plugin";
        std::exit(1);
    }

    /* Open font, fill glyph cache */
    Utility::Resource rs("fonts");
    if(!font->openData({{"font.conf", rs.getRaw("font.conf")}, {"font.tga", rs.getRaw("font.tga")}}, 0.0f)) {
        Error() << "Cannot open font";
        std::exit(1);
    }
    auto glyphCache = font->createGlyphCache();
    glyphCache->texture().setMinificationFilter(Sampler::Filter::Nearest)
        .setMagnificationFilter(Sampler::Filter::Nearest);

    /* Fill the manager with data */
    resourceManager.setLoader(new TextureLoader)
        .set("tga-importer", tgaImporter.release())
        .set("font", font.release())
        .set("glyph-cache", glyphCache.release())
        .set<AbstractShaderProgram>("flat-textured", new Shaders::Flat2D(Shaders::Flat2D::Flag::Textured))
        .set<AbstractShaderProgram>("text", new Shaders::Vector2D)
        .set("square-buffer", squareBuffer)
        .set("square", squareMesh)
        .setFallback(texture);

    /* Prepare coloring camera */
    ColoringCamera::setup();

    /* Screens */
    _splashScreen.reset(new SplashScreen);
    addScreen(*_splashScreen);
    _gameScreen.reset(new GameScreen);
    addScreen(*_gameScreen);
    _bagScreen.reset(new BagScreen);
    addScreen(*_bagScreen);
}

Application::~Application() = default;

Platform::Screen& Application::bagScreen() { return *_bagScreen; }

Platform::Screen& Application::gameScreen() { return *_gameScreen; }

Platform::Screen& Application::splashScreen() { return *_splashScreen; }

void Application::globalViewportEvent(const Vector2i& size) {
    defaultFramebuffer.setViewport({{}, size});
}

void Application::globalDrawEvent() {
    swapBuffers();
}

}

MAGNUM_APPLICATION_MAIN(Rotten::Application)
