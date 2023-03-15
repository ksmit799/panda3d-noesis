/**
 * Creates a libNoesis context with the given name (must be unique) for the
 * given window.  Returns a new DisplayRegion where the libNoesis context will
 * render to.  This variant of make() creates a region that fills the entire
 * window.
 */
INLINE NoesisRegion *NoesisRegion::make(const std::string &context_name,
                                        GraphicsOutput *window) {
  return make(context_name, window, LVecBase4(0.0f, 1.0f, 0.0f, 1.0f));
}

/**
 * Creates a libNoesis context with the given name (must be unique) for the
 * given window.  Returns a new DisplayRegion where the libNoesis context will
 * render to.
 */
INLINE NoesisRegion *NoesisRegion::make(const std::string &context_name,
                                        GraphicsOutput *window,
                                        const LVecBase4 &dimensions) {
  return new NoesisRegion(window, dimensions, context_name);
}

INLINE void NoesisRegion::set_input_handler(NoesisInputHandler *handler) {
  _input_handler = handler;
}

INLINE NoesisInputHandler *NoesisRegion::get_input_handler() const {
  return _input_handler;
}
