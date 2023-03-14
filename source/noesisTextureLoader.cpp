#include "noesisTextureLoader.h"

#include <NsGui/MemoryStream.h>

#include "config_putil.h"
#include "virtualFileSystem.h"

Noesis::Ptr<Noesis::Stream>
NoesisTextureLoader::OpenStream(const Noesis::Uri &uri) const {
  VirtualFileSystem *vfs = VirtualFileSystem::get_global_ptr();

  // Resolve the filename on the model path.
  Filename filename(uri.Str());
  PT(VirtualFile) vf = vfs->find_file(filename, get_model_path());
  if (vf == nullptr) {
    // The filename doesn't exist.
    noesis_cat.warning() << "Could not find Texture file: " << filename << "\n";
    return nullptr;
  }

  std::istream *source = vf->open_read_file(true);
  if (source == nullptr) {
    noesis_cat.warning() << "Could not open Texture file: " << filename << "\n";
    return nullptr;
  }

  // Read the file into memory.
  size_t size = vf->get_file_size(source);
  char *buffer = (char *)malloc(size);
  source->read(buffer, size);

  vfs->close_read_file(source);

  // Memory steam will automatically delete the malloced buffer.
  return *new Noesis::MemoryStream(buffer, size);
}
