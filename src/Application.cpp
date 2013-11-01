#include <Platform/Sdl2Application.h>
#include <Platform/ScreenedApplication.h>
#include <DefaultFramebuffer.h>

#include "GameScreen.h"

namespace Rotten {

class Application: public Platform::ScreenedApplication {
    public:
        explicit Application(const Arguments& arguments);

    protected:
        void globalViewportEvent(const Vector2i& size) override;
        void globalDrawEvent() override;

        GameScreen gameScreen;
};

Application::Application(const Arguments& arguments): Platform::ScreenedApplication(arguments,
    Configuration().setSize(Vector2i(160, 144)*4).setTitle("ROTTEN NOODLES SMUGGLER"))
{
    addScreen(gameScreen);
}

void Application::globalViewportEvent(const Vector2i& size) {
    defaultFramebuffer.setViewport({{}, size});
}

void Application::globalDrawEvent() {
    swapBuffers();
}

}

MAGNUM_APPLICATION_MAIN(Rotten::Application)
