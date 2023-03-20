#include "noesisRender.h"

#include "graphicsOutput.h"
#include "graphicsStateGuardian.h"

#include <NsGui/IRenderer.h>

NoesisRender::NoesisRender(Noesis::IView *view) { _view = view; }

void NoesisRender::do_callback(DisplayRegionDrawCallbackData *data) {
  // Get a handle to the GraphicsStateGuardian.
  GraphicsStateGuardian *gsg =
      data->get_scene_setup()->get_display_region()->get_window()->get_gsg();

  // TODO: Calling this in a draw callback crashes panda. Figure out why.
//  // Applies last changes happened in view.
//  _view->GetRenderer()->UpdateRenderTree();
//  // Generates offscreen textures.
//  _view->GetRenderer()->RenderOffscreen();
//
//  gsg->clear_state_and_transform();
//
//  _view->GetRenderer()->Render();
}
