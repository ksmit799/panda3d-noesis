#ifndef NOESIS_RENDER_H
#define NOESIS_RENDER_H

#include "config_noesis.h"
#include "callbackObject.h"
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
};

#endif // NOESIS_RENDER_H
