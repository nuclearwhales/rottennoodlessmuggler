#include "GameScreen.h"

#include <Color.h>
#include <DefaultFramebuffer.h>
#include <Renderer.h>

#include "Application.h"
#include "ColoringCamera.h"
#include "Dumpster.h"
#include "Sprite.h"
#include "Button.h"
#include "MutableTextSprite.h"
#include "Bag.h"
#include "BagScreen.h"

namespace Rotten {

GameScreen::GameScreen() {
    Renderer::setClearColor(Color3(0.66f));

    /* Add dumpster */
    dumpster = new Dumpster(&scene, &drawables);

    /* Add some stuff to it */
    dumpster->next();
    dumpster->next();
    dumpster->next();

    /* Add bag */
    (bag = new Bag(&scene, &drawables))
        ->translate(Vector2i::yAxis(-43));

    player = new Player(bag, dumpster, &scene, &drawables);

    /* Configure state transitions of StateMachine handling input from player */
    handler.addTransitions({
        {PositionState::Center, PositionInput::LeftKey, PositionState::Left},
        {PositionState::Center, PositionInput::RightKey, PositionState::Right},
        {PositionState::Left, PositionInput::RightKey, PositionState::Center},
        {PositionState::Right, PositionInput::LeftKey, PositionState::Center},
    });

    /* Connect to player */
    Interconnect::connect(handler, &MovementHandler::entered<PositionState::Left>, *player, &Player::goLeft);
    Interconnect::connect(handler, &MovementHandler::entered<PositionState::Right>, *player, &Player::goRight);
    Interconnect::connect(handler, &MovementHandler::exited<PositionState::Left>, *player, &Player::goRight);
    Interconnect::connect(handler, &MovementHandler::exited<PositionState::Right>, *player, &Player::goLeft);
    Interconnect::connect(handler, &MovementHandler::entered<PositionState::Center>, *player, &Player::moveUp);
    Interconnect::connect(handler, &MovementHandler::exited<PositionState::Center>, *player, &Player::moveDown);

    /* Configure camera */
    camera = new ColoringCamera(&scene);

    /* UI */
    (new MutableTextSprite(10, Text::Alignment::TopLeft, &scene, &drawables))
        ->setText("0:38")
        .translate({-78, 70});
    (new MutableTextSprite(10, Text::Alignment::TopRight, &scene, &drawables))
        ->setText("$150")
        .translate({78, 70});
    (new Button(Button::Style::ActionA, "Done", &scene, &drawables))
        ->translate({40, -66});
}

void GameScreen::focusEvent() {
    setPropagatedEvents(PropagatedEvent::Draw|PropagatedEvent::Input);
}

void GameScreen::blurEvent() {
    setPropagatedEvents({});
}

void GameScreen::viewportEvent(const Vector2i& size) {
    camera->setViewport(size);
}

void GameScreen::drawEvent() {
    camera->draw(drawables);
}

void GameScreen::keyPressEvent(KeyEvent& event) {
    switch(event.key()){
        case KeyEvent::Key::Left:
            handler.step(PositionInput::LeftKey);
            redraw();
            break;
        case KeyEvent::Key::Right:
            handler.step(PositionInput::RightKey);
            redraw();
            break;
        case KeyEvent::Key::Up:
            player->grab();
            redraw();
            break;
        case KeyEvent::Key::Down:
            player->save();
            redraw();
            break;
        case KeyEvent::Key::A:
            static_cast<BagScreen&>(application<Application>()->bagScreen()).viewBag(bag);
            break;
        default: return;
    }

    event.setAccepted();
}

}
