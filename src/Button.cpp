#include "Button.h"
#include "Sprite.h"
#include "TextSprite.h"

namespace Rotten {

Button::Button(const Style style, const std::string& text, Object2D* parent, SceneGraph::DrawableGroup2D* drawables): Object2D(parent) {
    _image = new Sprite(this, drawables);

    Vector2i translation;
    Text::Alignment alignment;
    if(style == Style::Plain || style == Style::Selected)
        alignment = Text::Alignment::MiddleCenter;
    else {
        alignment = Text::Alignment::MiddleLeft;
        translation = Vector2i::xAxis(-22);
    }

    (_text = new TextSprite(text, alignment, this, drawables))
        ->setColor(Color3(0.6f))
        .translate(translation);

    setStyle(style);
}

void Button::setStyle(const Style style) {
    ResourceKey key;

    switch(style) {
        case Style::Plain: key = "button"; break;
        case Style::Selected: key = "selected"; break;
        case Style::ActionA: key = "button-a"; break;
        case Style::ActionB: key = "button-b"; break;
        default: CORRADE_ASSERT_UNREACHABLE();
    }

    _image->reset({80, 12}, key);
    _text->setBackgroundColor(style == Style::ActionB || style == Style::Plain ?
        Color3(1.0f) : Color3(0.3f));
}

}
