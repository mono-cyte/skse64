# SKSE64 Project Rebuilt with Xmake

Due to dissatisfaction with the bloated Visual Studio (VS) and the cumbersome configuration of CMake, I opted for Xmake for building, which provides readable and maintainable configuration files.

This project references a forked common library from my personal repository, as the corresponding content is not available in the official Xmake repository, and I do not intend to submit this package to the official repository.

The project includes multiple subprojects: `*_common` is static library, `skse64` is an injection DLL related to the game version, and `skse64_loader` is an executable program.

For user:

| project              | kind   | description                                          | Required           |
| -------------------- | ------ | ---------------------------------------------------- | ------------------ |
| skse64_version       | phony  | Provide version info for other projects              | :x:                |
| skse64_common        | static | Common utilities and helper functions                | :x:                |
| skse64_loader_common | static | Common code for the loader component                 | :x:                |
| skse64               | shared | Main SKSE64 DLL that gets injected                   | :heavy_check_mark: |
| skse64_loader        | binary | Standalone executable to launch the game with SKSE64 | :heavy_check_mark: |
