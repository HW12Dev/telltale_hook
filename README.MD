# telltale_hook
Multi-purpose tool to execute Lua in Telltale Tool games at runtime.

Very WIP and is not ready for proper use.

## Compatibility
Any game not mentioned on this list is likely to be incompatible.

| Name                                        | Compatibility                                                                  |
|:--------------------------------------------|:-------------------------------------------------------------------------------|
|   Game of Thrones: A Telltale Games Series  | telltale_hook was developed on Game of Thrones, it should always be compatible |
|        Minecraft Story Mode: Season 1       |                                       Yes                                      |
| The Walking Dead: Definitive Series (Debug) |                                       Yes                                      |
| The Walking Dead: Definitive Series (Steam) |                                       Yes                                      |

## Installation
Copy `dinput8.dll` and `telltale_hook.dll` to the folder containing the games executable

## Compiling
It is recommended to compile telltale_tool in Visual Studio Code, with the CMake plugin installed,
using Visual Studio Community 2022's x86 compiler.
The Walking Dead: Definitive Series is 64bit, and must be compiled with Visual Studio Community 2022's amd64 compiler