#include "noesisRender.h"

#include <NsGui/IRenderer.h>

NoesisRender::NoesisRender(Noesis::IView *view) {
  _view = view;
}

void NoesisRender::do_callback(CallbackData *data) {
  _view->GetRenderer()->Render();
}
