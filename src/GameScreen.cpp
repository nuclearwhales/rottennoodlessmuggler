#include "GameScreen.h"

#include <Color.h>
#include <DefaultFramebuffer.h>
#include <Renderer.h>

#include "ColoringCamera.h"

namespace Rotten {

GameScreen::GameScreen() {
    Renderer::setClearColor(Color3(0.66f));

    /* Configure camera */
    cameraObject = new Object2D(&scene);
    camera = new ColoringCamera(*cameraObject);
    camera->setProjection({160.0f, 144.0f})
        .setViewport(defaultFramebuffer.viewport().size());
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
