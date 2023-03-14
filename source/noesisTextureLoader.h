#ifndef NOESIS_TEXTURE_LOADER_H
#define NOESIS_TEXTURE_LOADER_H

#include "config_noesis.h"

#include <NsApp/FileTextureProvider.h>
#include <NsCore/Ptr.h>
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

// TODO: Remove the dependency on NsApp entirely.
class NoesisTextureLoader : public NoesisApp::FileTextureProvider {
public:
  NoesisTextureLoader() = default;

private:
  Noesis::Ptr<Noesis::Stream> OpenStream(const Noesis::Uri &uri) const override;
};

#endif // NOESIS_TEXTURE_LOADER_H
