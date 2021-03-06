#ifndef Rotten_GameScreen_h
#define Rotten_GameScreen_h

#include <Interconnect/StateMachine.h>
#include <Platform/Screen.h>
#include <Platform/Sdl2Application.h>
#include <SceneGraph/Scene.h>
#include <SceneGraph/TranslationTransformation.h>
#include <SceneGraph/Drawable.h>

#include "Player.h"
#include "Rotten.h"

namespace Rotten {

enum class PositionState: UnsignedByte {
    Center,
    Left,
    Right
};

enum class PositionInput: UnsignedByte {
    LeftKey,
    RightKey
};

typedef Interconnect::StateMachine<3, 2, PositionState, PositionInput> MovementHandler;

class Bag;
class ColoringCamera;
class Dumpster;

class GameScreen: public Platform::Screen {
    public:
        explicit GameScreen();

    private:
        void focusEvent() override;
        void blurEvent() override;
        void viewportEvent(const Vector2i& size) override;
        void drawEvent() override;
        void keyPressEvent(KeyEvent& event);

        Scene2D scene;
        ColoringCamera* camera;
        SceneGraph::DrawableGroup2D drawables;
        MovementHandler handler;

        Dumpster* dumpster;
        Bag* bag;
        Player* player;
};

}

#endif
