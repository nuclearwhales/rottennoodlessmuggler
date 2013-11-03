#ifndef Rotten_TradeScreen_h
#define Rotten_TradeScreen_h

#include <Platform/Screen.h>
#include <Platform/Sdl2Application.h>
#include <SceneGraph/Scene.h>
#include <SceneGraph/TranslationTransformation.h>
#include <SceneGraph/Camera2D.h>
#include <SceneGraph/Drawable.h>

#include "Rotten.h"

namespace Rotten {

class Bag;
class ColoringCamera;
class MutableTextSprite;

class BagScreen: public Platform::Screen {
    public:
        explicit BagScreen();

    private:
        void focusEvent() override;
        void blurEvent() override;
        void viewportEvent(const Vector2i& size) override;
        void drawEvent() override;
        void keyPressEvent(KeyEvent& event) override;

        void displayItem(Int id);

        Scene2D scene;
        ColoringCamera* camera;
        SceneGraph::DrawableGroup2D drawables;

        Bag* _bag;
        MutableTextSprite *_itemCount, *_currentContents;
        Int _current;
};

}

#endif
