#include "GameScreen.h"

#include <DefaultFramebuffer.h>

namespace Rotten {

GameScreen::GameScreen() {
    /* Configure camera */
    cameraObject = new Object2D(&scene);
    camera = new SceneGraph::Camera2D(*cameraObject);
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
    defaultFramebuffer.clear(FramebufferClear::Color);

    camera->draw(drawables);
}

}
