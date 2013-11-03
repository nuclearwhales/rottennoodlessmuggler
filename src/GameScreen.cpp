#include "GameScreen.h"

#include <Color.h>
#include <DefaultFramebuffer.h>
#include <Renderer.h>

#include "ColoringCamera.h"
#include "Sprite.h"

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

    /* Configure camera */
    cameraObject = new Object2D(&scene);
    camera = new ColoringCamera(*cameraObject);
    camera->setProjection({160.0f, 144.0f})
        .setViewport(defaultFramebuffer.viewport().size());

    /* Add some stuff */
    (new Sprite(Vector2i(20), "box", &scene, &drawables))->translate({-40, -10});
    (new Sprite(Vector2i(20), "mess", &scene, &drawables))->translate({0, 30});
    (new Sprite(Vector2i(20), "strongbox", &scene, &drawables))->translate({40, -10});
}

void GameScreen::focusEvent() {
    setPropagatedEvents(PropagatedEvent::Draw|PropagatedEvent::Input);
}

void GameScreen::blurEvent() {
    setPropagatedEvents(PropagatedEvent::Draw);
}

void GameScreen::viewportEvent(const Vector2i& size) {
    camera->setViewport(size);
}

void GameScreen::drawEvent() {
    camera->draw(drawables);
}

}
