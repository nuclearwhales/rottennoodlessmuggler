#include "GameScreen.h"

#include <Color.h>
#include <DefaultFramebuffer.h>
#include <Renderer.h>

#include "ColoringCamera.h"
#include "Sprite.h"
#include "TextSprite.h"

namespace Rotten {

GameScreen::GameScreen() {
    Renderer::setClearColor(Color3(0.66f));

    /* Configure camera */
    cameraObject = new Object2D(&scene);
    camera = new ColoringCamera(*cameraObject);
    camera->setProjection({160.0f, 144.0f})
        .setViewport(defaultFramebuffer.viewport().size());

    /* Add some stuff */
    (new Sprite(Vector2i(20), "box", &scene, &drawables))->translate({-40, -10});
    (new Sprite(Vector2i(20), "mess", &scene, &drawables))->translate({0, 30});
    (new Sprite(Vector2i(20), "strongbox", &scene, &drawables))->translate({40, -10});
    (new TextSprite("hellou peeple", &scene, &drawables))->translate({0, -40});
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
