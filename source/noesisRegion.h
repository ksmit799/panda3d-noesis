#ifndef NOESIS_REGION_H
#define NOESIS_REGION_H

#include "config_noesis.h"
#include "displayRegion.h"
#include "graphicsOutput.h"
#include "noesisInputHandler.h"

#include <NsGui/IView.h>

/**
 * Forward declarations for interrogate.
 */
namespace Noesis {
struct IView;
}

class OrthographicLens;
class NoesisRender;

/**
 * Represents a region in a window or buffer where the libNoesis UI will be
 * rendered to.
 */
class EXPCL_NOESIS NoesisRegion : public DisplayRegion {
protected:
  NoesisRegion(GraphicsOutput *window, const LVecBase4 &dimensions,
               const std::string &context_name, const std::string &theme_name,
               const std::string &root_panel);

  virtual void do_cull(CullHandler *cull_handler, SceneSetup *scene_setup,
                       GraphicsStateGuardian *gsg, Thread *current_thread);

PUBLISHED:
  virtual ~NoesisRegion();

  INLINE static NoesisRegion *make(const std::string &context_name,
                                   GraphicsOutput *window,
                                   const std::string &theme_name,
                                   const std::string &root_panel);
  INLINE static NoesisRegion *make(const std::string &context_name,
                                   GraphicsOutput *window,
                                   const std::string &theme_name,
                                   const std::string &root_panel,
                                   const LVecBase4 &dimensions);

  INLINE void set_input_handler(NoesisInputHandler *handler);
  INLINE NoesisInputHandler *get_input_handler() const;

private:
  int _width, _height;
  PT(OrthographicLens) _lens;
  PT(NoesisRender) _render_callback;
  PT(NoesisInputHandler) _input_handler;
  Noesis::IView *_view;

public:
  static TypeHandle get_class_type() { return _type_handle; }

  static void init_type() {
    DisplayRegion::init_type();
    register_type(_type_handle, "NoesisRegion",
                  DisplayRegion::get_class_type());
  }

  virtual TypeHandle get_type() const { return get_class_type(); }

  virtual TypeHandle force_init_type() {
    init_type();
    return get_class_type();
  }

private:
  static TypeHandle _type_handle;
};

#include "noesisRegion.I"

#endif // NOESIS_REGION_H
