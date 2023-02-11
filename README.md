# TF2 Internal Hack

## Notes

### Project

This project is built using CXX23, which allows for the use of the latest libraries. The standard for building the project is CMake version 3.9. To add an extra layer of security, the project uses Themida to virtualize the code, making it more difficult to reverse. If you choose to remove Themida, make sure to also remove all references to it in the `CMakeLists` file.

### VCPKG Information

For the project to compile, you must have the VCPKG folder in your root directory. You can change this location in the `CMakeLists` file, but it is discouraged.

### Required Libraries

* [DirectX 9 SDK](https://www.microsoft.com/en-in/download/confirmation.aspx?id=6812)
  > Note: Non-fatal errors can be ignored, but make sure that the `DXSDK_DIR` is in your system variables. If not, try adding it by searching for the "Microsoft DirectX SDK (June 2010)" folder in "C:/Program Files (x86)".
* [freetype:x86-windows-static](https://vcpkg.io/en/packages.html)
  > Note: To install `vcpkg`, you'll need to download the binaries and add it to your path. Make sure to install the correct version, otherwise, the project will not compile.

### Recommended Plugins

* [Clang PowerTools](https://marketplace.visualstudio.com/items?itemName=caphyon.ClangPowerTools)
  > Note: This extension provides excellent integration with the already-setup `.clang-format` files. With this, you can efficiently format your code.
