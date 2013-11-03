#include "GameScreen.h"

#include <Color.h>
#include <DefaultFramebuffer.h>
#include <Renderer.h>

#include "Application.h"
#include "ColoringCamera.h"
#include "Sprite.h"
#include "TextSprite.h"

namespace Rotten {

GameScreen::GameScreen() {
    Renderer::setClearColor(Color3(0.66f));

    /* Configure state transitions of StateMachine handling input from player */
    handler.addTransitions({
        {State::Center, Input::LeftKey, State::Left},
        {State::Center, Input::RightKey, State::Right},
        {State::Center, Input::ActionKey, State::CenterWithItem},
        {State::CenterWithItem, Input::LeftKey, State::LeftWithItem},
        {State::CenterWithItem, Input::RightKey, State::RightWithItem},
        /*there is no action in center with item carried*/
        {State::Left, Input::RightKey, State::Center},
        {State::Left, Input::ActionKey, State::LeftWithItem},
        {State::LeftWithItem, Input::RightKey, State::CenterWithItem},
        {State::LeftWithItem, Input::ActionKey, State::Left}, //drop
        {State::Right, Input::LeftKey, State::Center},
        {State::Right, Input::ActionKey, State::RightWithItem},
        {State::RightWithItem, Input::LeftKey, State::CenterWithItem},
        {State::RightWithItem, Input::ActionKey, State::Right} //save item
    });

    Interconnect::connect(handler, &ActionHandler::stepped<State::Center, State::Left>, player, player.goLeft());
    Interconnect::connect(handler, &ActionHandler::stepped<State::Center, State::Right>, player, player.goRight());
    Interconnect::connect(handler, &ActionHandler::stepped<State::Center, State::CenterWithItem>, player, player.takeItem());
    Interconnect::connect(handler, &ActionHandler::stepped<State::CenterWithItem, State::LeftWithItem>, player, player.goLeft());
    Interconnect::connect(handler, &ActionHandler::stepped<State::CenterWithItem, State::RightWithItem>, player, player.goRight());
    Interconnect::connect(handler, &ActionHandler::stepped<State::Left, State::Center>, player, player.goRight());
    Interconnect::connect(handler, &ActionHandler::stepped<State::Left, State::LeftWithItem>, player, player.takeItem());
    Interconnect::connect(handler, &ActionHandler::stepped<State::LeftWithItem, State::CenterWithItem>, player, player.goRight());
    Interconnect::connect(handler, &ActionHandler::stepped<State::LeftWithItem, State::Left>, player, player.dropItem());
    Interconnect::connect(handler, &ActionHandler::stepped<State::Right, State::Center>, player, player.goLeft());
    Interconnect::connect(handler, &ActionHandler::stepped<State::Right, State::RightWithItem>, player, player.takeItem());
    Interconnect::connect(handler, &ActionHandler::stepped<State::RightWithItem, State::CenterWithItem>, player, player.goLeft());
    Interconnect::connect(handler, &ActionHandler::stepped<State::RightWithItem, State::Right>, player, player.saveItem());

    /* Configure camera */
    camera = new ColoringCamera(&scene);

    /* Add some stuff */
    (new Sprite(Vector2i(20), "box", &scene, &drawables))->translate({-40, -10});
    (new Sprite(Vector2i(20), "mess", &scene, &drawables))->translate({0, 30});
    (new Sprite(Vector2i(20), "strongbox", &scene, &drawables))->translate({40, -10});

    (new TextSprite("St: SHOW BAG", &scene, &drawables))
        ->setColor(Color3(0.3f))
        .translate({30, -67});
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
    if(event.key() == KeyEvent::Key::Enter)
        application()->focusScreen(application<Application>()->bagScreen());
    //else return;

    switch(event.key()){
        case KeyEvent::Key::Left:
            handler.step(Input::LeftKey);
            break;
        case KeyEvent::Key::Right:
            handler.step(Input::RightKey);
            break;
        case KeyEvent::Key::A:
            handler.step(Input::ActionKey);
            break;
        default:
            //do nothing
    }

    event.setAccepted();
}

}
