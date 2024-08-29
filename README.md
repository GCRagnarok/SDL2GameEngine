# SDL2GameEngine

## Overview
2D game engine utilising an entity component system. Built with C++ and SDL2.

## Prerequisites
- CMake 3.10 or higher
- A C++17 compatible compiler
- `vcpkg` for managing dependencies

## Installing CMake

### Windows
1. Download the CMake installer from the [CMake website](https://cmake.org/download/).
2. Run the installer and follow the instructions.

### macOS
1. Download the CMake installer from the [CMake website](https://cmake.org/download/).
2. Open the downloaded `.dmg` file and drag the CMake application to your Applications folder.
3. Open a terminal and run the following command to add CMake to your PATH:
```
sudo "/Applications/CMake.app/Contents/bin/cmake-gui" --install
```
### Linux
1. Install CMake using your package manager. For example, on Ubuntu:
```
sudo apt-get update
```
```
sudo apt-get install -y cmake
```
## Setting Up the Project

### Step 1: Clone the Repository

Using your preferred shell or command-line interface (CLI) (e.g., Git Bash, PowerShell, etc.):

Clone the project repository:
```
git clone https://github.com/GCRagnarok/SDL2GameEngine.git
```
```
cd SDL2GameEngine
```
### Step 2: Install `vcpkg`

Clone the `vcpkg` repository and bootstrap it:

#### On Unix-like systems (Linux, macOS, Git Bash on Windows):
```
git clone https://github.com/microsoft/vcpkg.git
```
```
cd vcpkg
```
```
./bootstrap-vcpkg.sh
```    
#### On Windows Command Prompt or PowerShell:
```
git clone https://github.com/microsoft/vcpkg.git
```
```
cd vcpkg
```
```
.\bootstrap-vcpkg.bat
```
### Step 3: Install Dependencies

Use `vcpkg` to install SDL2 and its extensions. `vcpkg` will download and manage these files for you:
```
./vcpkg install sdl2 sdl2-ttf sdl2-mixer sdl2-image
```
### Step 4: Integrate `vcpkg` with CMake

Integrate `vcpkg` with your project:
```
./vcpkg integrate install
```
### Step 5: Configure the Project with CMake

Navigate back to the project root directory and configure the project using CMake:
```
cd ..
```
```
cmake -B build -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
```
### Step 6: Build the Project

Build the project using CMake:
```
cmake --build build
```
## Running the Project

After building the project, you can open the solution file in Visual Studio:
1. Navigate to the SDL2 Game Engine directory and copy the 'assets' folder to the build directory.
2. While in the build directoy, open the `SDL2GameEngine.sln` file in Visual Studio.
3. Set the startup project to `SDL2GameEngine` if it is not already set.
4. Build the solution by selecting `Build > Build Solution` from the menu or pressing `Ctrl+Shift+B`.
5. Run the project by selecting `Debug > Start Debugging` or pressing `F5`.

## Note

The CMake build process has only been tested on Windows using Git Bash.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [SDL2](https://www.libsdl.org/)
- [vcpkg](https://github.com/microsoft/vcpkg)
### Example Game Assets
- [Tileset & sprites](https://biggermanjd.itch.io/platformer-tileset-pixelart-grasslands)
- [Font](https://www.dafont.com/little-malio-8-bit.font)
- [Coin Sound](https://freesound.org/people/AceOfSpadesProduc100/sounds/341695/)
- [Background Music](https://freesound.org/people/Mrthenoronha/sounds/476545/)
