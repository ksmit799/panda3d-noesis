#include "config_noesis.h"

#include <NsGui/FontProperties.h>
#include <NsGui/IntegrationAPI.h>

#include "dconfig.h"
#include "noesisFontLoader.h"
#include "noesisInputHandler.h"
#include "noesisRegion.h"
#include "noesisTextureLoader.h"
#include "noesisXamlLoader.h"
#include "pandaSystem.h"

Configure(config_noesis);
NotifyCategoryDef(noesis, "");

ConfigureFn(config_noesis) { init_libnoesis(); }

/**
 * Initializes the library.  This must be called at least once before any of
 * the functions or classes in this library can be used.  Normally it will be
 * called by the static initializers and need not be called explicitly, but
 * special cases exist.
 */
void init_libnoesis() {
  static bool initialized = false;
  if (initialized) {
    return;
  }
  initialized = true;

  if (noesis_cat->is_debug()) {
    noesis_cat->debug() << "Initializing libNoesis library.\n";
  }

  // Setup logging.
  // Noesis logging maps directly to the noesis-notify-level prc variable.
  Noesis::SetLogHandler([](const char *, uint32_t, uint32_t level, const char *,
                           const char *msg) {
    switch (level) {
    case 0:
      noesis_cat->spam() << msg << "\n";
      break;
    case 1:
      noesis_cat->debug() << msg << "\n";
      break;
    case 2:
      noesis_cat->info() << msg << "\n";
      break;
    case 3:
      noesis_cat->warning() << msg << "\n";
      break;
    case 4:
      noesis_cat->error() << msg << "\n";
      break;
    }
  });

  // Configure licensing info for Noesis.
  // This is set at compile time.
  Noesis::GUI::SetLicense(NS_LICENSE_NAME, NS_LICENSE_KEY);

  // See: https://www.noesisengine.com/docs/Gui.Core.InspectorTutorial.html
  // TODO: Make this a config variable.
  // NB: This should always be disabled in shipping builds.
  Noesis::GUI::DisableInspector();

  // Noesis initialization. This must be the first step before using any
  // NoesisGUI functionality
  Noesis::GUI::Init();

  // Setup resource providers.
  // (Hooks into the VFS).
  Noesis::GUI::SetXamlProvider(Noesis::MakePtr<NoesisXamlLoader>());
  Noesis::GUI::SetTextureProvider(Noesis::MakePtr<NoesisTextureLoader>());
  Noesis::GUI::SetFontProvider(Noesis::MakePtr<NoesisFontLoader>());

  const char *fonts[] = {"Arial", "Segoe UI Emoji"};
  Noesis::GUI::SetFontFallbacks(fonts, 2);
  Noesis::GUI::SetFontDefaultProperties(15.0f, Noesis::FontWeight_Normal,
                                        Noesis::FontStretch_Normal,
                                        Noesis::FontStyle_Normal);

  // Init your dynamic types here:
  NoesisRegion::init_type();
  NoesisInputHandler::init_type();

  // Register that we have the libNoesis system.
  PandaSystem *ps = PandaSystem::get_global_ptr();
  ps->add_system("libNoesis");

  return;
}
