#ifndef Rotten_GameScreen_h
#define Rotten_GameScreen_h

#include <Interconnect/StateMachine.h>
#include <Platform/Screen.h>
#include <Platform/Sdl2Application.h>
#include <SceneGraph/Scene.h>
#include <SceneGraph/TranslationTransformation.h>
#include <SceneGraph/Drawable.h>

#include "Rotten.h"

namespace Rotten {

enum class State: UnsignedByte {
    Center,
    Left,
    Right,
    CenterWithItem,
    LeftWithItem,
    RightWithItem
};

enum class Input: UnsignedByte {
    LeftKey,
    RightKey,
    ActionKey
};

typedef Interconnect::StateMachine<6, 3, State, Input> ActionHandler;

class ColoringCamera;

class GameScreen: public Platform::Screen {
    public:
        explicit GameScreen();

    private:
        void focusEvent() override;
        void blurEvent() override;
        void viewportEvent(const Vector2i& size) override;
        void drawEvent() override;

        Scene2D scene;
        ColoringCamera* camera;
        SceneGraph::DrawableGroup2D drawables;
        ActionHandler handler;
};

}

#endif
