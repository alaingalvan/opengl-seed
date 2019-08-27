# ⚪ OpenGL Seed

[![CMake][cmake-img]][cmake-url]
[![License][license-img]][license-url]

A starter repo that you could use to build an OpenGL application on top of.

## Setup

First install:

- [Git](https://git-scm.com/)

- [CMake](https://cmake.org)

- An IDE such as [Visual Studio](https://visualstudio.microsoft.com/downloads/), [XCode](https://developer.apple.com/xcode/), or a compiler such as [GCC](https://gcc.gnu.org/).

Then type the following in your [terminal](https://hyper.is/).

```bash
# 🐑 Clone the repo
git clone https://github.com/alaingalvan/opengl-seed --recurse-submodules

# 💿 go inside the folder
cd opengl-seed

# 👯 If you forget to `recurse-submodules` you can always run:
git submodule update --init

# 👷 Make a build folder
mkdir build
cd build

# 🖼️ To build your Visual Studio solution on Windows x64
cmake .. -A x64

# 🍎 To build your XCode project on Mac OS
cmake .. -G Xcode

# 🐧 To build your .make file on Linux
cmake ..

# 🔨 Build on any platform:
cmake --build .
```

### File Structure

```bash
├─ external/              # Dependencies
│  ├─ crosswindow/
│  ├─ crosswindow-graphics/
│  ├─ glad/
│  └─ glm/
├─ src/                   # Source Files
│  └─ Main.cpp
├─ .gitignore
├─ CMakeLists.txt         # Build Script
├─ license.md
└─ readme.md
```

[cmake-img]: https://img.shields.io/badge/cmake-3.10-1f9948.svg?style=flat-square
[cmake-url]: https://cmake.org/
[license-img]: http://img.shields.io/:license-unlicense-blue.svg?style=flat-square
[license-url]: http://unlicense.org/
[windows-img]: http://img.shields.io/:supports-win-03b3fe.svg?style=flat-square
[mac-img]: http://img.shields.io/:download-mac-1ed1fa.svg?style=flat-square
[android-img]: http://img.shields.io/:supports-android-a4ca39.svg?style=flat-square
[linux-img]: http://img.shields.io/:supports-linux-df491e.svg?style=flat-square
[ios-img]: http://img.shields.io/:supports-ios-006ded.svg?style=flat-square