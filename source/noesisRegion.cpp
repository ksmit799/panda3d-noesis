#include "noesisRegion.h"

#include "camera.h"
#include "clockObject.h"
#include "orthographicLens.h"
#include "pStatTimer.h"
#include "noesisRender.h"

#include <NsApp/ThemeProviders.h>
#include <NsGui/FontProperties.h>
#include <NsGui/Grid.h>
#include <NsGui/IRenderer.h>
#include <NsGui/IView.h>
#include <NsGui/IntegrationAPI.h>
#include <NsRender/GLFactory.h>

TypeHandle NoesisRegion::_type_handle;

NoesisRegion::NoesisRegion(GraphicsOutput *window,
                           const LVecBase4 &dr_dimensions,
                           const std::string &context_name)
    : DisplayRegion(window, dr_dimensions) {
  int pl, pr, pb, pt;
  get_pixels(pl, pr, pb, pt);

  _width = pr - pl;
  _height = pt - pb;

  noesis_cat.debug() << "Setting initial context dimensions to (" << _width
                     << ", " << _height << ")\n";

  // Setup theme
  NoesisApp::SetThemeProviders();
  Noesis::GUI::LoadApplicationResources("Theme/NoesisTheme.DarkBlue.xaml");

  // For simplicity purposes we are not using resource providers in this sample.
  // ParseXaml() is enough if there is no extra XAML dependencies
  Noesis::Ptr<Noesis::Grid> xaml(Noesis::GUI::ParseXaml<Noesis::Grid>(R"(
        <Grid xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation">
            <Grid.Background>
                <LinearGradientBrush StartPoint="0,0" EndPoint="0,1">
                    <GradientStop Offset="0" Color="#FF123F61"/>
                    <GradientStop Offset="0.6" Color="#FF0E4B79"/>
                    <GradientStop Offset="0.7" Color="#FF106097"/>
                </LinearGradientBrush>
            </Grid.Background>
            <Viewbox>
                <StackPanel Margin="50">
                    <Button Content="Hello World!" Margin="0,30,0,0"/>
                    <Rectangle Height="5" Margin="-10,20,-10,0">
                        <Rectangle.Fill>
                            <RadialGradientBrush>
                                <GradientStop Offset="0" Color="#40000000"/>
                                <GradientStop Offset="1" Color="#00000000"/>
                            </RadialGradientBrush>
                        </Rectangle.Fill>
                    </Rectangle>
                </StackPanel>
            </Viewbox>
        </Grid>
    )"));

  // View creation to render and interact with the user interface
  // We transfer the ownership to a global pointer instead of a Ptr<> because
  // there is no way in GLUT to do shutdown and we don't want the Ptr<> to be
  // released at global time
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

  _renderCallback = new NoesisRender(_view);
  set_draw_callback(_renderCallback);
}

NoesisRegion::~NoesisRegion() {}

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

    noesis_cat.debug() << "Setting  context dimensions to (" << _width
                       << ", " << _height << ")\n";

    _lens->set_film_size(_width, -_height);
    _lens->set_film_offset(_width * 0.5, _height * 0.5);

    _view->SetSize(_width, _height);
  }

  // Updates view (real time, not dt).
  _view->Update(ClockObject::get_global_clock()->get_real_time());

  // Applies last changes happened in view.
  _view->GetRenderer()->UpdateRenderTree();
  // Generates offscreen textures.
  _view->GetRenderer()->RenderOffscreen();
}
