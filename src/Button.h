#ifndef Rotten_Button_h
#define Rotten_Button_h

#include <SceneGraph/Object.h>
#include <SceneGraph/TranslationTransformation.h>

#include "Rotten.h"

namespace Rotten {

class Sprite;
class TextSprite;

class Button: public Object2D {
    public:
        enum class Style: UnsignedByte {
            Plain,
            Selected,
            ActionA,
            ActionB
        };

        explicit Button(Style style, const std::string& text, Object2D* parent, SceneGraph::DrawableGroup2D* drawables = nullptr);

        void setStyle(Style style);

    private:
        Sprite* _image;
        TextSprite* _text;
};

}

#endif
