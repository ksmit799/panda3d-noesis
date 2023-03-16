#include "noesisInputHandler.h"

#include <NsGui/InputEnums.h>

#include "buttonEventList.h"
#include "keyboardButton.h"
#include "linmath_events.h"
#include "mouseButton.h"

TypeHandle NoesisInputHandler::_type_handle;

NoesisInputHandler::NoesisInputHandler(const std::string &name)
    : DataNode(name), _mouse_xy(-1), _mouse_xy_changed(false), _mouse_last_x(0),
      _mouse_last_y(0) {
  _pixel_xy_input = define_input("pixel_xy", EventStoreVec2::get_class_type());
  _button_events_input =
      define_input("button_events", ButtonEventList::get_class_type());
}

NoesisInputHandler::~NoesisInputHandler() {}

void NoesisInputHandler::do_transmit_data(DataGraphTraverser *trav,
                                          const DataNodeTransmit &input,
                                          DataNodeTransmit &output) {
  // Handle mouse input.
  if (input.has_data(_pixel_xy_input)) {
    // The mouse is within the window. Get the current mouse position.
    const EventStoreVec2 *pixel_xy;
    DCAST_INTO_V(pixel_xy, input.get_data(_pixel_xy_input).get_ptr());
    LVecBase2 p = pixel_xy->get_value();

    // Determine if mouse moved from last position
    if (p != _mouse_xy) {
      _mouse_xy_changed = true;
      _mouse_xy = p;
    }
  }

  ButtonEventList new_button_events;

  // Look for new button events.
  if (input.has_data(_button_events_input)) {
    const ButtonEventList *this_button_events;
    DCAST_INTO_V(this_button_events,
                 input.get_data(_button_events_input).get_ptr());

    // Map button keys to Noesis keys.
    int num_events = this_button_events->get_num_events();
    for (int i = 0; i < num_events; i++) {
      const ButtonEvent &be = this_button_events->get_event(i);

      switch (be._type) {
      // A button has been pressed.
      case ButtonEvent::T_down:
        if (be._button == MouseButton::one()) {
          _mouse_buttons[Noesis::MouseButton_Left] = true;
        } else if (be._button == MouseButton::two()) {
          _mouse_buttons[Noesis::MouseButton_Middle] = true;
        } else if (be._button == MouseButton::three()) {
          _mouse_buttons[Noesis::MouseButton_Right] = true;
        } else if (be._button == MouseButton::four()) {
          _mouse_buttons[Noesis::MouseButton_XButton1] = true;
        } else if (be._button == MouseButton::five()) {
          _mouse_buttons[Noesis::MouseButton_XButton2] = true;
        }
        break;

      case ButtonEvent::T_repeat:
        break;

      // A button has been lifted.
      case ButtonEvent::T_up:
        if (be._button == MouseButton::one()) {
          _mouse_buttons[Noesis::MouseButton_Left] = false;
        } else if (be._button == MouseButton::two()) {
          _mouse_buttons[Noesis::MouseButton_Middle] = false;
        } else if (be._button == MouseButton::three()) {
          _mouse_buttons[Noesis::MouseButton_Right] = false;
        } else if (be._button == MouseButton::four()) {
          _mouse_buttons[Noesis::MouseButton_XButton1] = false;
        } else if (be._button == MouseButton::five()) {
          _mouse_buttons[Noesis::MouseButton_XButton2] = false;
        }
        break;

      case ButtonEvent::T_keystroke:
        break;

      // Default cases (unhandled)
      case ButtonEvent::T_resume_down:
      case ButtonEvent::T_move:
      case ButtonEvent::T_candidate:
      case ButtonEvent::T_raw_down:
      case ButtonEvent::T_raw_up:
        break;
      }
    }
  }
}

void NoesisInputHandler::process(Noesis::IView *view, int xoffs, int yoffs) {
  // Handle mouse movement.
  if (_mouse_xy_changed) {
    _mouse_xy_changed = false;

    _mouse_last_x = _mouse_xy.get_x() - xoffs;
    _mouse_last_y = _mouse_xy.get_y() - yoffs;

    view->MouseMove(_mouse_last_x, _mouse_last_y);
  }

  // Handle mouse key-presses.
  if (_mouse_buttons.size() > 0) {
    ButtonActivityMap::const_iterator it;
    for (it = _mouse_buttons.begin(); it != _mouse_buttons.end(); ++it) {
      if (it->second) {
        view->MouseButtonDown(_mouse_last_x, _mouse_last_y,
                              (Noesis::MouseButton)it->first);
      } else {
        view->MouseButtonUp(_mouse_last_x, _mouse_last_y,
                            (Noesis::MouseButton)it->first);
      }
    }

    _mouse_buttons.clear();
  }
}
