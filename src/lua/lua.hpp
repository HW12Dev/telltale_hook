/***
 * This file contains all offsets and function definitions from game executables
 * 
 * this should be one of the only files you need to modify to add compatibility to
 * other Telltale Tool games
*/

#pragma once

#include "../telltale_types.hpp"

#define FUNC_DEFINE(function_name, retn, ...) \
    typedef retn (*function_name##ptr)(__VA_ARGS__);                  \
    function_name##ptr function_name = NULL;

#define FUNC_DEFINE_THISCALL(function_name, retn, ...)        \
    typedef retn (__thiscall*function_name##ptr)(__VA_ARGS__); \
    function_name##ptr function_name = NULL;

#define FUNC_OFFSET(function_name, offset_from_executable) \
    const DWORD function_name##offset = offset_from_executable;

struct lua_State;

typedef int (*lua_CFunction)(lua_State *);
typedef void *(*lua_Alloc)(void *ud, void *ptr, size_t osize, size_t nsize);

#ifndef NULL
#define NULL 0
#endif

#pragma region Function Types

// Lua functions
FUNC_DEFINE(lua_newstate, lua_State *, lua_Alloc f, void *ud)

FUNC_DEFINE(lua_pcallk, lua_State *, lua_State *L, int nargs, int nresults, int errfunc,
            int ctx, lua_CFunction k)

FUNC_DEFINE(lua_pushcclosure, void, lua_State *L, lua_CFunction fn, int n)
FUNC_DEFINE(lua_setglobal, void, lua_State *L, const char *var)

FUNC_DEFINE(lua_tolstring, const char *, lua_State *L, int idx, size_t *len)

FUNC_DEFINE(luaL_loadfilex, int, lua_State *L, const char *filename, const char *mode)
FUNC_DEFINE(luaL_loadstring, int, lua_State *L, const char *s)

FUNC_DEFINE(lua_pushboolean, void, lua_State *L, int b)

FUNC_DEFINE(lua_gettop, int, lua_State* L)

// Telltale Tool / Engine functions

// ScriptManager::LoadResource has a boolean parameter in debug builds
#ifdef GAME_TWDDS_GAMEAPP
FUNC_DEFINE(ScriptManager__LoadResource, __int64, lua_State* L, const char* filename, bool bAllowGlobals)
#elif defined(GAME_TWDDS)
FUNC_DEFINE(ScriptManager__LoadResource, __int64, lua_State* L, const char* filename)
#else
FUNC_DEFINE(ScriptManager__LoadResource, int, lua_State *L, char *filename)
#endif

// return value changes to 64bit in TWD exe
FUNC_DEFINE(CRC32, unsigned int, unsigned int crc, const char* const buffer, unsigned int count)
FUNC_DEFINE(CRC64_CaseInsensitive, unsigned __int64, unsigned __int64 crc, const char *buf)

FUNC_DEFINE_THISCALL(TTArchive2__Activate, int, telltale_types::TTArchive2 *_this, telltale_types::Ptr<telltale_types::DataStream> a2)

#pragma endregion

// Game of Thrones: A Telltale Games Series
#ifdef GAME_THRONES

// Lua functions
FUNC_OFFSET(lua_newstate, 0x00588930)

FUNC_OFFSET(lua_pcallk, 0x00584E00)

FUNC_OFFSET(lua_pushcclosure, 0x005842A0)
FUNC_OFFSET(lua_setglobal, 0x00584820)

FUNC_OFFSET(lua_tolstring, 0x00583D60)

FUNC_OFFSET(luaL_loadfilex, 0x00586340)
FUNC_OFFSET(luaL_loadstring, 0x00586640)

FUNC_OFFSET(lua_pushboolean, 0x00584340)

// Telltale Tool / Engine functions
FUNC_OFFSET(ScriptManager__LoadResource, 0x000E67F0)

#endif

// Minecraft: Story Mode - A Telltale Games Series
#ifdef GAME_MINECRAFTSTORYMODE

// Lua functions
FUNC_OFFSET(lua_newstate, 0x00611C80)

FUNC_OFFSET(lua_pcallk, 0x0060D3B0)

FUNC_OFFSET(lua_pushcclosure, 0x0060C850)
FUNC_OFFSET(lua_setglobal, 0x0060CDD0)

FUNC_OFFSET(lua_tolstring, 0x0060C310)

FUNC_OFFSET(luaL_loadfilex, 0x0060E8F0)
FUNC_OFFSET(luaL_loadstring, 0x0060EBF0)

FUNC_OFFSET(lua_pushboolean, 0x0060C8F0)

FUNC_OFFSET(lua_gettop, 0x0060B860)

// Telltale Tool / Engine functions
FUNC_OFFSET(ScriptManager__LoadResource, 0x001139F0)

FUNC_OFFSET(CRC32, 0x0024A670)
FUNC_OFFSET(CRC64_CaseInsensitive, 0x0024A620)

FUNC_OFFSET(TTArchive2__Activate, 0x006003D0)

#endif

// The Walking Dead: The Telltale Definitive Series / Debug Build
#ifdef GAME_TWDDS_GAMEAPP

// Lua functions
FUNC_OFFSET(lua_newstate, 0x00000000008A5BA0)

FUNC_OFFSET(lua_pcallk, 0x00000000008A52C0)

FUNC_OFFSET(lua_pushcclosure, 0x00000000008A48B0)
FUNC_OFFSET(lua_setglobal, 0x00000000008A4DB0)

FUNC_OFFSET(lua_tolstring, 0x00000000008A4270)

FUNC_OFFSET(luaL_loadfilex, 0x00000000008A97B0)
FUNC_OFFSET(luaL_loadstring, 0x00000000008A9AD0)

FUNC_OFFSET(lua_pushboolean, 0x00000000008A4990)

FUNC_OFFSET(lua_gettop, 0x00000000008A3C70)

// Telltale Tool / Engine functions
FUNC_OFFSET(ScriptManager__LoadResource, 0x00000000002031F0)

FUNC_OFFSET(CRC32, 0x000000000044E730)
FUNC_OFFSET(CRC64_CaseInsensitive, 0x00000000000C9820)

FUNC_OFFSET(TTArchive2__Activate, 0x00000000000AD4B0)

#endif

// The Walking Dead: The Telltale Definitive Series / Steam Shipping Build
#ifdef GAME_TWDDS

// Lua functions
FUNC_OFFSET(lua_newstate, 0x00000000008A5BA0)

FUNC_OFFSET(lua_pcallk, 0x00000000008A52C0)

FUNC_OFFSET(lua_pushcclosure, 0x00000000008A48B0)
FUNC_OFFSET(lua_setglobal, 0x00000000008A4DB0)

FUNC_OFFSET(lua_tolstring, 0x00000000008A4270)

FUNC_OFFSET(luaL_loadfilex, 0x00000000008A97B0)
FUNC_OFFSET(luaL_loadstring, 0x00000000008A9AD0)

FUNC_OFFSET(lua_pushboolean, 0x00000000008A4990)

FUNC_OFFSET(lua_gettop, 0x00000000008A3C70)

// Telltale Tool / Engine functions
FUNC_OFFSET(ScriptManager__LoadResource, 0x00000000002031F0)

FUNC_OFFSET(CRC32, 0x0)
FUNC_OFFSET(CRC64_CaseInsensitive, 0x0)

FUNC_OFFSET(TTArchive2__Activate, 0x0)

#endif


// game independent definitions, usually definitions from lua source
#define lua_pushcfunction(L, f) lua_pushcclosure(L, (f), 0)
#define lua_register(L, n, f) (lua_pushcfunction(L, (f)), lua_setglobal(L, (n)))

#define lua_tostring(L, i) lua_tolstring(L, (i), NULL)

#define lua_pcall(L,n,r,f) lua_pcallk(L, (n), (r), (f), 0, NULL)

#define luaL_loadfile(L,f) luaL_loadfilex(L,f,NULL)

#define luaL_dofile(L, fn) \
    (luaL_loadfile(L, fn) || lua_pcall(L, 0, -1, 0))

#define luaL_dostring(L, s) \
    (luaL_loadstring(L, s) || lua_pcall(L, 0, -1, 0))