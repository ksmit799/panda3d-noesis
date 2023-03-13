#include "noesisRender.h"

#include <NsGui/IRenderer.h>

TypeHandle NoesisRender::_type_handle;

NoesisRender::NoesisRender(Noesis::IView *view) {
  noesis_cat.debug() << "Draw\n";
  _view = view;
}

void NoesisRender::do_callback(CallbackData *data) {
  _view->GetRenderer()->Render();
}
