#include "noesisRegion.h"

#include "camera.h"
#include "clockObject.h"
#include "noesisRender.h"
#include "orthographicLens.h"
#include "pStatTimer.h"

#include <NsGui/FontProperties.h>
#include <NsGui/FrameworkElement.h>
#include <NsGui/IRenderer.h>
#include <NsGui/IView.h>
#include <NsGui/IntegrationAPI.h>
#include <NsRender/GLFactory.h>

TypeHandle NoesisRegion::_type_handle;

NoesisRegion::NoesisRegion(GraphicsOutput *window,
                           const LVecBase4 &dr_dimensions,
                           const std::string &context_name,
                           const std::string &theme_name,
                           const std::string &root_panel)
    : DisplayRegion(window, dr_dimensions) {
  int pl, pr, pb, pt;
  get_pixels(pl, pr, pb, pt);

  _width = pr - pl;
  _height = pt - pb;

  noesis_cat.debug() << "Setting initial context dimensions to (" << _width
                     << ", " << _height << ")\n";

  // Setup theme.
  Noesis::GUI::LoadApplicationResources(theme_name.c_str());

  // Load the root panel.
  Noesis::Ptr<Noesis::FrameworkElement> xaml =
      Noesis::GUI::LoadXaml<Noesis::FrameworkElement>(root_panel.c_str());

  // View creation to render and interact with the user interface.
  _view = Noesis::GUI::CreateView(xaml).GiveOwnership();
  _view->SetFlags(Noesis::RenderFlags_PPAA | Noesis::RenderFlags_LCD);
  _view->SetSize(_width, _height);

  // Renderer initialization with an OpenGL device
  std::string pipeName = window->get_pipe()->get_interface_name();
  if (pipeName == "OpenGL") {
    _view->GetRenderer()->Init(NoesisApp::GLFactory::CreateDevice(false));
    noesis_cat.debug() << "Render device set to OpenGL\n";
  } else {
    noesis_cat.fatal() << "No compatible render device for pipe: " << pipeName
                       << "\n";
  }

  _lens = new OrthographicLens();
  _lens->set_film_size(_width, -_height);
  _lens->set_film_offset(_width * 0.5, _height * 0.5);
  _lens->set_near_far(-1, 1);

  PT(Camera) cam = new Camera(context_name, _lens);
  set_camera(NodePath(cam));

  _render_callback = new NoesisRender(_view);
  set_draw_callback(_render_callback);
}

NoesisRegion::~NoesisRegion() {
  // Shutdown the renderer.
  _view->GetRenderer()->Shutdown();
}

void NoesisRegion::do_cull(CullHandler *cull_handler, SceneSetup *scene_setup,
                           GraphicsStateGuardian *gsg, Thread *current_thread) {
  // Register this cull with PStats.
  PStatTimer timer(get_cull_region_pcollector(), current_thread);

  // Re-calculate the viewport width/height.
  int pl, pr, pb, pt;
  get_pixels(pl, pr, pb, pt);

  int width = pr - pl;
  int height = pt - pb;

  if (width != _width || height != _height) {
    // Our viewport has changed, update our camera lens.
    _width = width;
    _height = height;

    noesis_cat.debug() << "Setting  context dimensions to (" << _width << ", "
                       << _height << ")\n";

    _lens->set_film_size(_width, -_height);
    _lens->set_film_offset(_width * 0.5, _height * 0.5);

    _view->SetSize(_width, _height);
  }

  // Input handling.
  if (_input_handler != nullptr) {
    _input_handler->process(_view, pl, pb);
  }

  // Updates view (real time, not dt).
  _view->Update(ClockObject::get_global_clock()->get_real_time());

  // Applies last changes happened in view.
  _view->GetRenderer()->UpdateRenderTree();
  // Generates offscreen textures.
  _view->GetRenderer()->RenderOffscreen();
}
