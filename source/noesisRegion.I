/**
 * Creates a libNoesis context with the given name (must be unique) for the
 * given window.  Returns a new DisplayRegion where the libNoesis context will
 * render to.  This variant of make() creates a region that fills the entire
 * window.
 */
INLINE NoesisRegion *NoesisRegion::make(const std::string &context_name,
                                        GraphicsOutput *window,
                                        const std::string &theme_name,
                                        const std::string &root_panel) {
  return make(context_name, window, theme_name, root_panel,
              LVecBase4(0.0f, 1.0f, 0.0f, 1.0f));
}

/**
 * Creates a libNoesis context with the given name (must be unique) for the
 * given window.  Returns a new DisplayRegion where the libNoesis context will
 * render to.
 */
INLINE NoesisRegion *NoesisRegion::make(const std::string &context_name,
                                        GraphicsOutput *window,
                                        const std::string &theme_name,
                                        const std::string &root_panel,
                                        const LVecBase4 &dimensions) {
  return new NoesisRegion(window, dimensions, context_name, theme_name,
                          root_panel);
}

INLINE void NoesisRegion::set_input_handler(NoesisInputHandler *handler) {
  _input_handler = handler;
}

INLINE NoesisInputHandler *NoesisRegion::get_input_handler() const {
  return _input_handler;
}
