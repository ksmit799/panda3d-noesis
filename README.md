# Panda3D Noesis

> Noesis GUI support for Panda3D

[Noesis GUI](https://www.noesisengine.com/) is a resolution-independent, vector-based rendering engine that is built to
take advantage of modern graphics
hardware. Based on XAML, a powerful UI declarative markup language compatible with Microsoft Expression Blend and WPF.

Panda3D Noesis adds native Noesis GUI support to the [Panda3D](https://www.panda3d.org/) game engine.

*Latest supported Noesis GUI version: **3.1.7***

## Features

- Supports the Panda3D Virtual File System. We recommend placing XAML files on your model path.
- Supports the Panda3D Input System (including re-bindings.)
- Python bindings for UI callbacks/events.

## Requirements

### Panda3D

You will need to run your Panda3D application with the OpenGL 3.2 Core render pipeline:

```
loadPrcFileData("", "load-display pandagl")
loadPrcFileData("", "gl-version 3 2")
```

### Noesis GUI

You must obtain a [copy of Noesis GUI](https://www.noesisengine.com/licensing.php) and place it into the `libs/` folder.
Make sure to rename the root Noesis folder
to `NoesisGUI`

Currently, the NoesisApp dependency will also need to be compiled. You can do so by navigating
to `libs/NoesisGUI/Src/NoesisApp/Projects/<your platform>` and compiling.

You will also need to set the `NS_LICENSE_NAME` and `NS_LICENSE_KEY` CMake variables before compling for Panda3D (with
your license
name and key).

## Building

*Panda3D Noesis has been built and tested on Windows 10/11 64-bit with Visual Studio 2022*

- The Panda3D SDK (get it <a href="http://www.panda3d.org/download.php?sdk">here</a>)
- CMake 2.6 or higher (get it <a href="https://cmake.org/download/">here</a>)
- windows only: The thirdparty folder installed in the Panda3D sdk folder (
  See <a href="https://www.panda3d.org/forums/viewtopic.php?f=9&t=18775">here</a>)

**For compiling on Windows 32 bit:**

- Visual Studio 2010/2015/2022

**For compiling on Windows 64 bit:**

- Visual Studio 2010/2015/2022
- Windows SDK 10 (be sure to tick the VC++ 64 bit compilers option)

Once these requirements have been satisfied, simply run `ppython build.py` in the root directory.

## Examples

You can see implementation examples in the `examples/` folder.
