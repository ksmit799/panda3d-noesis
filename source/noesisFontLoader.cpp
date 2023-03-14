#include "noesisFontLoader.h"

#include <NsGui/MemoryStream.h>

#include "config_putil.h"
#include "virtualFileSystem.h"

void NoesisFontLoader::ScanFolder(const Noesis::Uri &folder) {
  VirtualFileSystem *vfs = VirtualFileSystem::get_global_ptr();

  // Make sure the folder is a directory.
  Filename folderPath(folder.Str());
  PT(VirtualFile) vf = vfs->find_file(folderPath, get_model_path());
  if (!vf->is_directory()) {
    return;
  }

  // Scan the directory for files.
  PT(VirtualFileList) contents = vf->scan_directory();
  if (contents == nullptr) {
    return;
  }

  // We have at least one file in the directory.
  int num_files = contents->get_num_files();
  for (int i = 0; i < num_files; ++i) {
    VirtualFile *file = contents->get_file(i);
    Filename filename = file->get_filename();

    // Register as a font if the file has a valid extension.
    if (filename.get_extension() == "ttf" ||
        filename.get_extension() == "otf" ||
        filename.get_extension() == "ttc") {
      RegisterFont(folder, filename.get_basename().c_str());
    }
  }
}

Noesis::Ptr<Noesis::Stream>
NoesisFontLoader::OpenFont(const Noesis::Uri &folder,
                           const char *filename) const {
  VirtualFileSystem *vfs = VirtualFileSystem::get_global_ptr();

  // Resolve the filename on the model path.
  Filename filepath(Filename(folder.Str()), Filename(filename));
  PT(VirtualFile) vf = vfs->find_file(filepath, get_model_path());
  if (vf == nullptr) {
    // The filename doesn't exist.
    noesis_cat.warning() << "Could not find Font file: " << filepath << "\n";
    return nullptr;
  }

  std::istream *source = vf->open_read_file(true);
  if (source == nullptr) {
    noesis_cat.warning() << "Could not open Font file: " << filepath << "\n";
    return nullptr;
  }

  // Read the font into memory.
  size_t size = vf->get_file_size(source);
  char *buffer = (char *)malloc(size);
  source->read(buffer, size);

  vfs->close_read_file(source);

  // Memory steam will automatically delete the malloced buffer.
  return *new Noesis::MemoryStream(buffer, size);
}
