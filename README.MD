# telltale_hook
Multi-purpose tool to execute Lua in Telltale Tool games at runtime.

Very WIP and is not ready for proper use.

## Compatibility
Any game not mentioned on this list is likely to be incompatible.

| Name                                               | Compatibility                                                                  | Compile with       |
|:---------------------------------------------------|:-------------------------------------------------------------------------------|:-------------------|
|    Game of Thrones: A Telltale Games Series (Disc) | telltale_hook was developed on Game of Thrones, it should always be compatible |       THRONES      |
|            Minecraft Story Mode: Season 1          |                                       Yes                                      | MINECRAFTSTORYMODE |
|     The Walking Dead: Definitive Series (Debug)    |                                       Yes                                      |    TWDDS_GAMEAPP   |
|     The Walking Dead: Definitive Series (Steam)    |                                       Yes                                      |        TWDDS       |
|   Sam And Max: Save The World Remastered (Steam)   |                                       Yes                                      |  SMSTW_REMASTERED  |

## Installation
Copy `dinput8.dll` and `telltale_hook.dll` to the folder containing the games executable

## Compiling
It is recommended to compile telltale_tool in Visual Studio Code, with the CMake plugin installed,
using Visual Studio Community 2022's x86 compiler.
The Walking Dead: Definitive Series is 64bit, and must be compiled with Visual Studio Community 2022's amd64 compiler

## Engine Versions
This section of the README is intended to document internal changes between Telltale Tool engine versions.

The only version where the engine version is included in the executable seems to be v28.

### v28
Date, in executable: July 2018 (07/2018)
Used by:
- Sam & Max: Save the World Remastered
- The Walking Dead: Definitive Series (Debug)
- The Walking Dead: Definitive Series (Steam)