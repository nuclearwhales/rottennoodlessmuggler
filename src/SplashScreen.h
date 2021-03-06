#ifndef Rotten_SplashScreen_h
#define Rotten_SplashScreen_h

#include <Platform/Screen.h>
#include <Platform/Sdl2Application.h>
#include <SceneGraph/Scene.h>
#include <SceneGraph/TranslationTransformation.h>
#include <SceneGraph/Drawable.h>

#include "Rotten.h"

namespace Rotten {

class ColoringCamera;

class SplashScreen: public Platform::Screen {
    public:
        explicit SplashScreen();

    private:
        void focusEvent() override;
        void blurEvent() override;
        void viewportEvent(const Vector2i& size) override;
        void drawEvent() override;
        void keyPressEvent(KeyEvent& event);

        Scene2D scene;
        ColoringCamera* camera;
        SceneGraph::DrawableGroup2D drawables;
};

}

#endif
