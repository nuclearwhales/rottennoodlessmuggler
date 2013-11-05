#include "GameScreen.h"

#include <Color.h>
#include <DefaultFramebuffer.h>
#include <Renderer.h>

#include "Application.h"
#include "ColoringCamera.h"
#include "Dumpster.h"
#include "Sprite.h"
#include "Button.h"

namespace Rotten {

GameScreen::GameScreen() {
    Renderer::setClearColor(Color3(0.66f));

    /* Add dumpster */
    dumpster = new Dumpster(&scene, &drawables);

    /* Add some stuff to it */
    dumpster->next();
    dumpster->next();

    player = new Player(dumpster,&scene, &drawables);

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



    (new Button(Button::Style::ActionB, "Done", &scene, &drawables))
        ->translate({-40, -66});

    (new Button(Button::Style::ActionA, "Take", &scene, &drawables))
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
        case KeyEvent::Key::A:
            player->takeAction();
            redraw();
            break;
        case KeyEvent::Key::B:
            application()->focusScreen(application<Application>()->bagScreen());
            break;
        default: return;
    }

    event.setAccepted();
}

}
