#ifndef NOESIS_FONT_LOADER_H
#define NOESIS_FONT_LOADER_H

#include "config_noesis.h"

#include <NsCore/Ptr.h>
#include <NsGui/CachedFontProvider.h>
#include <NsGui/Stream.h>
#include <NsGui/Uri.h>

/**
 * Forward declarations for interrogate.
 */
namespace Noesis {
template <class T> class Ptr;
class Stream;
struct Uri;
} // namespace Noesis

class NoesisFontLoader : public Noesis::CachedFontProvider {
public:
  NoesisFontLoader() = default;

private:
  void ScanFolder(const Noesis::Uri &folder) override;
  Noesis::Ptr<Noesis::Stream> OpenFont(const Noesis::Uri &folder,
                                       const char *filename) const override;
};

#endif // NOESIS_FONT_LOADER_H
