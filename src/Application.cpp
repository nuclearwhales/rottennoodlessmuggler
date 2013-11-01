#include <Platform/Sdl2Application.h>
#include <Platform/ScreenedApplication.h>
#include <DefaultFramebuffer.h>
#include <Framebuffer.h>
#include <Mesh.h>
#include <ResourceManager.h>
#include <Texture.h>
#include <MeshTools/Interleave.h>
#include <Primitives/Square.h>
#include <Shaders/Flat.h>
#include <Trade/MeshData2D.h>
#include <PluginManager/Manager.h>

#include "GameScreen.h"
#include "TextureLoader.h"
#include "ColoringCamera.h"

#include "configure.h"

#ifdef MAGNUM_BUILD_STATIC
/* Import shader resources in static build */
#include <Shaders/magnumShadersResourceImport.hpp>

/* Import plugins in static build */
static int importStaticPlugins() {
    CORRADE_PLUGIN_IMPORT(TgaImporter)
    return 0;
} CORRADE_AUTOMATIC_INITIALIZER(importStaticPlugins)
#endif

namespace Rotten {

class Application: public Platform::ScreenedApplication {
    public:
        explicit Application(const Arguments& arguments);

    protected:
        void globalViewportEvent(const Vector2i& size) override;
        void globalDrawEvent() override;

        PluginManager::Manager<Trade::AbstractImporter> importerManager;
        Manager resourceManager;
        std::unique_ptr<GameScreen> gameScreen;
};

Application::Application(const Arguments& arguments): Platform::ScreenedApplication(arguments,
    Configuration().setSize(Vector2i(160, 144)*4).setTitle("ROTTEN NOODLES SMUGGLER")), importerManager(ROTTEN_PLUGINS_IMPORTER_DIR)
{
    /* Load TGA importer */
    if(!(importerManager.load("TgaImporter") & PluginManager::LoadState::Loaded)) {
        Error() << "Cannot load TgaImporter plugin";
        std::exit(1);
    }
    auto tgaImporter = importerManager.instance("TgaImporter");
    if(!tgaImporter) {
        Error() << "Cannot instantiate TgaImporter plugin";
        std::exit(1);
    }

    /* Prepare the rectangle mesh */
    Trade::MeshData2D squareData = Primitives::Square::solid(Primitives::Square::TextureCoords::Generate);
    auto squareBuffer = new Buffer;
    auto squareMesh = new Mesh;
    MeshTools::interleave(*squareMesh, *squareBuffer, Buffer::Usage::StaticDraw, squareData.positions(0), squareData.textureCoords2D(0));
    squareMesh->setPrimitive(squareData.primitive())
        .addVertexBuffer(*squareBuffer, 0, Shaders::Flat2D::Position(), Shaders::Flat2D::TextureCoordinates());

    /* Fill the manager with data */
    resourceManager.setLoader(new TextureLoader)
        .set("tga-importer", tgaImporter.release())
        .set<AbstractShaderProgram>("flat-textured", new Shaders::Flat2D(Shaders::Flat2D::Flag::Textured))
        .set("square-buffer", squareBuffer)
        .set("square", squareMesh);

    /* Prepare coloring camera */
    ColoringCamera::setup();

    /* Screens */
    gameScreen.reset(new GameScreen);
    addScreen(*gameScreen);
}

void Application::globalViewportEvent(const Vector2i& size) {
    defaultFramebuffer.setViewport({{}, size});
}

void Application::globalDrawEvent() {
    swapBuffers();
}

}

MAGNUM_APPLICATION_MAIN(Rotten::Application)
