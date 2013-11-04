#include "SplashScreen.h"

#include <Color.h>
#include <DefaultFramebuffer.h>
#include <Renderer.h>

#include "Application.h"
#include "ColoringCamera.h"
#include "TextSprite.h"

namespace Rotten {

SplashScreen::SplashScreen() {
    /* Configure camera */
    camera = new ColoringCamera(&scene);

    new TextSprite("Press START", Text::Alignment::MiddleCenterIntegral, &scene, &drawables);
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
    if(event.key() == KeyEvent::Key::Enter)
        application()->focusScreen(application<Application>()->gameScreen());
    else return;

    event.setAccepted();
}

}
