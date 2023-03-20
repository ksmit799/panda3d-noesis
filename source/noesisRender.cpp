#include "noesisRender.h"

#include <NsGui/IRenderer.h>

NoesisRender::NoesisRender(Noesis::IView *view) { _view = view; }

void NoesisRender::do_callback(CallbackData *data) {
  // Applies last changes happened in view.
  _view->GetRenderer()->UpdateRenderTree();
  // Generates offscreen textures.
  _view->GetRenderer()->RenderOffscreen();

  // Render on-screen!
  _view->GetRenderer()->Render();
}
