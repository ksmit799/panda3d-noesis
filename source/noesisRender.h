#ifndef NOESIS_RENDER_H
#define NOESIS_RENDER_H

#include "config_noesis.h"
#include "callbackObject.h"
#include "displayRegionDrawCallbackData.h"
#include "typedReferenceCount.h"

#include <NsGui/IView.h>

/**
 * Forward declarations for interrogate.
 */
namespace Noesis {
struct IView;
}

class NoesisRender : public CallbackObject {
public:
  ALLOC_DELETED_CHAIN(NoesisRender);
  NoesisRender(Noesis::IView *view);

  virtual void do_callback(CallbackData *data);

private:
  Noesis::IView *_view;

public:
  static TypeHandle get_class_type() { return _type_handle; }

  static void init_type() {
    CallbackObject::init_type();
    register_type(_type_handle, "NoesisRender",
                  CallbackObject::get_class_type());
  }

  virtual TypeHandle get_type() const { return get_class_type(); }

  virtual TypeHandle force_init_type() {
    init_type();
    return get_class_type();
  }

private:
  static TypeHandle _type_handle;
};

#endif // NOESIS_RENDER_H
