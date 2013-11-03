#include "SplashScreen.h"

#include <Color.h>
#include <DefaultFramebuffer.h>
#include <Renderer.h>

#include "ColoringCamera.h"
#include "TextSprite.h"

namespace Rotten {

SplashScreen::SplashScreen() {
    /* Configure camera */
    cameraObject = new Object2D(&scene);
    camera = new ColoringCamera(*cameraObject);
    camera->setProjection({160.0f, 144.0f})
        .setViewport(defaultFramebuffer.viewport().size());

    new TextSprite("Press START", &scene, &drawables);
}

void SplashScreen::focusEvent() {
    setPropagatedEvents(PropagatedEvent::Draw|PropagatedEvent::Input);
}

void SplashScreen::blurEvent() {
    setPropagatedEvents({});
}

void SplashScreen::viewportEvent(const Vector2i& size) {
    camera->setViewport(size);
}

void SplashScreen::drawEvent() {
    camera->draw(drawables);
}

void SplashScreen::keyPressEvent(KeyEvent& event) {
    if(event.key() == KeyEvent::Key::Enter) {
        application()->focusScreen(*application()->backScreen());
        event.setAccepted();
    }
}

}
