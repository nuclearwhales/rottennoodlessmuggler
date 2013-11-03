#ifndef Rotten_Application_h
#define Rotten_Application_h

#include <PluginManager/Manager.h>
#include <Platform/Sdl2Application.h>
#include <Platform/ScreenedApplication.h>
#include <ResourceManager.h>

#include "Rotten.h"

namespace Rotten {

class GameScreen;
class SplashScreen;

class Application: public Platform::ScreenedApplication {
    public:
        explicit Application(const Arguments& arguments);

        ~Application();

        Platform::Screen& gameScreen();
        Platform::Screen& splashScreen();

    private:
        void globalViewportEvent(const Vector2i& size) override;
        void globalDrawEvent() override;

        PluginManager::Manager<Trade::AbstractImporter> importerManager;
        PluginManager::Manager<Text::AbstractFont> fontManager;
        Manager resourceManager;
        std::unique_ptr<GameScreen> _gameScreen;
        std::unique_ptr<SplashScreen> _splashScreen;
        std::unique_ptr<BagScreen> _bagScreen;
};

}

#endif
