#include "BagScreen.h"

#include <Math/Geometry/Rectangle.h>

#include "Application.h"
#include "Bag.h"
#include "ColoringCamera.h"
#include "Dumpster.h"
#include "Item.h"
#include "MutableTextSprite.h"
#include "TextSprite.h"

namespace Rotten {

BagScreen::BagScreen(): _current(-1) {
    /* Configure camera */
    camera = new ColoringCamera(&scene);

    /* TODO: debug code, please put dumpster diving in game screen */
    _bag = new Bag(&scene, &drawables);

    (_itemCount = new MutableTextSprite(64, Text::Alignment::TopLeft, &scene, &drawables))
        ->setText("Bag:" + std::to_string(_bag->items().size()) + " items")
        .translate({-78, 70});
    (_currentContents = new MutableTextSprite(64, Text::Alignment::MiddleCenterIntegral, &scene, &drawables))
        ->translate(Vector2i::yAxis(-30));

    (new TextSprite("Se: BACK", Text::Alignment::LineLeft, &scene, &drawables))
        ->setColor(Color3(1.0f))
        .translate({-78, -70});

    (new TextSprite("St: TRADE", Text::Alignment::LineRight, &scene, &drawables))
        ->setColor(Color3(0.3f))
        .translate({78, -70});

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
    else if(event.key() == KeyEvent::Key::Space)
        application()->focusScreen(application<Application>()->gameScreen());
    else return;

    event.setAccepted();
    redraw();
}

void BagScreen::displayNextItem() {
    if(!_bag->items().empty()) displayItem((_current + 1) % _bag->items().size());
}

void BagScreen::displayPreviousItem() {
    if(!_bag->items().empty()) displayItem((_current - 1) % _bag->items().size());
}

void BagScreen::displayItem(Int id) {
    CORRADE_INTERNAL_ASSERT(id >= 0 && std::size_t(id) < _bag->items().size());

    /* Gosh this is fugly. */

    if(_current != -1)
        _bag->items()[_current]->drawables()->remove(*_bag->items()[_current]);

    drawables.add(*_bag->items()[id]);
    _bag->items()[id]->setTransformation({});
    _currentContents->setText(_bag->items()[id]->contents());

    _current = id;
}

}
