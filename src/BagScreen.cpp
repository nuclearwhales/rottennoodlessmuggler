#include "BagScreen.h"

#include <Math/Geometry/Rectangle.h>

#include "Application.h"
#include "Bag.h"
#include "ColoringCamera.h"
#include "Dumpster.h"
#include "Item.h"
#include "MutableTextSprite.h"
#include "TextSprite.h"
#include "Button.h"

namespace Rotten {

BagScreen::BagScreen(): _current(-1) {
    /* Configure camera */
    camera = new ColoringCamera(&scene);

    (_itemCount = new MutableTextSprite(64, Text::Alignment::TopLeft, &scene, &drawables))
        ->translate({-78, 70});
    (_currentContents = new MutableTextSprite(64, Text::Alignment::MiddleCenterIntegral, &scene, &drawables))
        ->translate(Vector2i::yAxis(-30));

    (new Button(Button::Style::ActionB, "Thrash", &scene, &drawables))
        ->translate({-40, -66});
    (new Button(Button::Style::ActionA, "Trade", &scene, &drawables))
        ->translate({40, -66});
}

void BagScreen::viewBag(Bag* bag) {
    application()->focusScreen(*this);

    /* Empty the bag */
    _items = std::move(bag->items());
    for(auto i: _items) i->setParent(&scene);

    /* Display items */
    _itemCount->setText("Bag:" + std::to_string(_items.size()) + " items");
    displayNextItem();
}

void BagScreen::focusEvent() {
    setPropagatedEvents(PropagatedEvent::Draw|PropagatedEvent::Input);
}

void BagScreen::blurEvent() {
    setPropagatedEvents({});
}

void BagScreen::viewportEvent(const Vector2i& size) {
    camera->setViewport(size);
}

void BagScreen::drawEvent() {
    camera->draw(drawables);
}

void BagScreen::keyPressEvent(KeyEvent& event) {
    if(event.key() == KeyEvent::Key::Left)
        displayPreviousItem();
    else if(event.key() == KeyEvent::Key::Right)
        displayNextItem();
    else if(event.key() == KeyEvent::Key::B)
        thrash();
    else return;

    event.setAccepted();
    redraw();
}

void BagScreen::displayNextItem() {
    if(!_items.empty()) displayItem((_current + 1) % _items.size());
    else _currentContents->setText("");
}

void BagScreen::displayPreviousItem() {
    if(!_items.empty()) displayItem((_current - 1) % _items.size());
    else _currentContents->setText("");
}

void BagScreen::displayItem(Int id) {
    CORRADE_INTERNAL_ASSERT(id >= 0 && std::size_t(id) < _items.size());

    /* Gosh this is fugly. */
    if(_current != -1 && _items[_current]->drawables())
        _items[_current]->drawables()->remove(*_items[_current]);

    drawables.add(*_items[id]);
    _currentContents->setText(_items[id]->contents());

    _current = id;
}

void BagScreen::thrash() {
    if(_current == -1) return;

    delete _items[_current];
    _items.erase(_items.begin() + _current);
    --_current;
    _itemCount->setText("Bag:" + std::to_string(_items.size()) + " items");
    displayNextItem();
}

}
