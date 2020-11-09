# Analogy-cpp-Logging
C++ gRPC client that streams messages to Analogy Log Server.

## Windows

steps to install gRPC C++ library/dependencies:

1. install [vcpkg](https://github.com/microsoft/vcpkg). See [Quick start for windows](https://github.com/microsoft/vcpkg#quick-start-windows).
2. install gRPC C++ from the command line:
  -  32 bit: `vcpkg install grpc:x86-windows` or `vcpkg install grpc`
  -  64 bit: `vcpkg install grpc:x64-windows`
3.  If zlib support is desired, you'll also need to install the zlib feature: `vcpkg install protobuf[zlib]` or `vcpkg install protobuf[zlib]:x64-windows` 
4.  Once installed, you can find the installed packages in the vcpkg directory under the folder <vcpkg_installed_path>\packages. In order to make the packages available system-wide, you need to issue the command `vcpkg integrate install`
