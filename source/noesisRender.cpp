#include "noesisRender.h"

#include "displayRegionDrawCallbackData.h"

#include <NsGui/IRenderer.h>

NoesisRender::NoesisRender(Noesis::IView *view) { _view = view; }

void NoesisRender::do_callback(CallbackData *data) {
  DisplayRegionDrawCallbackData *cbdata = (DisplayRegionDrawCallbackData *)data;
  if (cbdata == nullptr || cbdata->get_scene_setup() == nullptr) {
    return;
  }

  GraphicsStateGuardian *gsg =
      cbdata->get_scene_setup()->get_display_region()->get_window()->get_gsg();

  // Applies last changes happened in view.
  _view->GetRenderer()->UpdateRenderTree();
  // Generates offscreen textures.
  _view->GetRenderer()->RenderOffscreen();

  // TODO: Do we need this.
  // We need to reset graphics state here.
  gsg->clear_state_and_transform();

  // Render on-screen!
  _view->GetRenderer()->Render();

  cbdata->upcall();
}
