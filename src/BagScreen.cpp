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
    Dumpster d(&scene, &drawables);
    _bag = new Bag(&scene, &drawables);
    while(auto i = d.next()) _bag->put(i);

    (_itemCount = new MutableTextSprite(64, &scene, &drawables))
        ->setText("Bag:" + std::to_string(_bag->items().size()) + " items")
        .translate({-78, 62});
    _currentContents = new MutableTextSprite(64, &scene, &drawables);

    (new TextSprite("Se: BACK", &scene, &drawables))
        ->setColor(Color3(1.0f))
        .translate({-47, -67});

    (new TextSprite("St: TRADE", &scene, &drawables))
        ->setColor(Color3(0.3f))
        .translate({42, -67});

    displayItem(0);
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
        displayItem((_current-1) % _bag->items().size());
    else if(event.key() == KeyEvent::Key::Right)
        displayItem((_current+1) % _bag->items().size());
    else if(event.key() == KeyEvent::Key::Space)
        application()->focusScreen(application<Application>()->gameScreen());
    else return;

    event.setAccepted();
    redraw();
}

void BagScreen::displayItem(Int id) {
    /* Gosh this is fugly. */

    if(_current != -1)
        _bag->items()[_current]->drawables()->remove(*_bag->items()[_current]);

    drawables.add(*_bag->items()[id]);
    _bag->items()[id]->setTransformation({});
    _currentContents->setText(_bag->items()[id]->contents());
    _currentContents->setTransformation({-_currentContents->rectangle().size().x()/2, -30});

    _current = id;
}

}