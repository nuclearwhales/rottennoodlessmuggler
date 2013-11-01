#ifndef Rotten_GameScreen_h
#define Rotten_GameScreen_h

#include <Platform/Screen.h>
#include <Platform/Sdl2Application.h>
#include <SceneGraph/Scene.h>
#include <SceneGraph/TranslationTransformation.h>
#include <SceneGraph/Camera2D.h>
#include <SceneGraph/Drawable.h>

#include "Rotten.h"

namespace Rotten {

class GameScreen: public Platform::Screen {
    public:
        explicit GameScreen();

    private:
        void focusEvent() override;
        void blurEvent() override;
        void viewportEvent(const Vector2i& size) override;
        void drawEvent() override;

        Scene2D scene;
        Object2D* cameraObject;
        SceneGraph::Camera2D* camera;
        SceneGraph::DrawableGroup2D drawables;
};

}

#endif
