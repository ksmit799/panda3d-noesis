#ifndef NOESIS_XAML_LOADER_H
#define NOESIS_XAML_LOADER_H

#include "config_noesis.h"

#include <NsCore/Ptr.h>
#include <NsGui/Stream.h>
#include <NsGui/Uri.h>
#include <NsGui/XamlProvider.h>

/**
 * Forward declarations for interrogate.
 */
namespace Noesis {
template <class T> class Ptr;
class Stream;
struct Uri;
} // namespace Noesis

class NoesisXamlLoader : public Noesis::XamlProvider {
public:
  NoesisXamlLoader() = default;

private:
  Noesis::Ptr<Noesis::Stream> LoadXaml(const Noesis::Uri &uri) override;
};

#endif // NOESIS_XAML_LOADER_H
