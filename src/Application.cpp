#include <Platform/Sdl2Application.h>
#include <DefaultFramebuffer.h>
#include <SceneGraph/Scene.h>
#include <SceneGraph/TranslationTransformation.h>
#include <SceneGraph/Camera2D.h>
#include <SceneGraph/Drawable.h>

using namespace Magnum;

typedef SceneGraph::Object<SceneGraph::TranslationTransformation2D> Object2D;
typedef SceneGraph::Scene<SceneGraph::TranslationTransformation2D> Scene2D;

class Application: public Platform::Application {
    public:
        explicit Application(const Arguments& arguments);

    protected:
        void viewportEvent(const Vector2i& size) override;
        void drawEvent() override;

    private:
        Scene2D scene;
        Object2D* cameraObject;
        SceneGraph::Camera2D* camera;
        SceneGraph::DrawableGroup2D drawables;
};

Application::Application(const Arguments& arguments): Platform::Application(arguments,
    Configuration().setSize(Vector2i(160, 144)*4).setTitle("ROTTEN NOODLES SMUGGLER"))
{
    /* Configure camera */
    cameraObject = new Object2D(&scene);
    camera = new SceneGraph::Camera2D(*cameraObject);
    camera->setProjection({160.0f, 144.0f})
        .setViewport(defaultFramebuffer.viewport().size());
}

void Application::viewportEvent(const Vector2i& size) {
    defaultFramebuffer.setViewport({{}, size});
    camera->setViewport(size);
}

void Application::drawEvent() {
    defaultFramebuffer.clear(FramebufferClear::Color);

    camera->draw(drawables);

    swapBuffers();
}

MAGNUM_APPLICATION_MAIN(Application)
