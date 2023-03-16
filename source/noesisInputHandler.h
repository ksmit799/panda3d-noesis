#ifndef NOESIS_INPUT_HANDLER_H
#define NOESIS_INPUT_HANDLER_H

#include "config_noesis.h"
#include "dataNode.h"
#include "dataNodeTransmit.h"

#include <NsGui/IView.h>

/**
 * Forward declarations for interrogate.
 */
namespace Noesis {
struct IView;
}

class EXPCL_NOESIS NoesisInputHandler : public DataNode {
PUBLISHED:
  NoesisInputHandler(const std::string &name = std::string());
  virtual ~NoesisInputHandler();

public:
  virtual void do_transmit_data(DataGraphTraverser *trav,
                                const DataNodeTransmit &input,
                                DataNodeTransmit &output);

  void process(Noesis::IView *view, int xoffs, int yoffs);

private:
  typedef pmap<int32_t, bool> ButtonActivityMap;

  // Mouse input.
  int _pixel_xy_input;
  LVecBase2 _mouse_xy;
  bool _mouse_xy_changed;
  float _mouse_last_x;
  float _mouse_last_y;
  ButtonActivityMap _mouse_buttons;

  // Keyboard input.
  int _button_events_input;

public:
  static TypeHandle get_class_type() { return _type_handle; }

  static void init_type() {
    DataNode::init_type();
    register_type(_type_handle, "NoesisInputHandler",
                  DataNode::get_class_type());
  }

  virtual TypeHandle get_type() const { return get_class_type(); }

  virtual TypeHandle force_init_type() {
    init_type();
    return get_class_type();
  }

private:
  static TypeHandle _type_handle;
};

#endif // NOESIS_INPUT_HANDLER_H
