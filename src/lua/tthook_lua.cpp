#include "tthook_lua.hpp"

#include "../telltale_hook.hpp"

#include <Windows.h>
#include <psapi.h>
#include <string>
#include <sstream>
#include <MinHook.h>
#include <TlHelp32.h>

#include "lua.hpp"
#include "../logging.hpp"

#define HOOK_FUNCTION(function_name)                                                                           \
    status = MH_CreateHook((LPVOID)function_name, &h_##function_name, reinterpret_cast<LPVOID *>(&o_##function_name)); \
    if (status != MH_OK)                                                                                               \
    {                                                                                                                  \
        telltale_hook::log::log("Failed to create ");                                                                  \
        telltale_hook::log::log(#function_name);                                                                       \
        telltale_hook::log::logln(" hook: " + std::string(MH_StatusToString(status)));                                 \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        telltale_hook::log::log("Successfully hooked ");                                                               \
        telltale_hook::log::logln(#function_name);                                                                     \
    }                                                                                                                  \
    status = MH_EnableHook((LPVOID)function_name);                                                                     \
    if (status != MH_OK)                                                                                               \
    {                                                                                                                  \
        telltale_hook::log::log("Failed to enable ");                                                                  \
        telltale_hook::log::log(#function_name);                                                                       \
        telltale_hook::log::logln(" hook: " + std::string(MH_StatusToString(status)));                                 \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        telltale_hook::log::log("Successfully enabled hook for ");                                                     \
        telltale_hook::log::logln(#function_name);                                                                     \
    }

#define POPULATE_OFFSET_FUNCTION(function_name) \
    function_name = (function_name##ptr)(((uint8_t*)GetModuleHandle(game_executable.c_str())) + function_name##offset);

static lua_State* L = NULL;

ScriptManager__LoadResourceptr o_ScriptManager__LoadResource = NULL;
lua_newstateptr o_lua_newstate = NULL;

int tthook_print(lua_State*L) {
    telltale_hook::log::logln(lua_tostring(L, -1));
    return 0;
}

int generic_true(lua_State*L) {
    lua_pushboolean(L, 1);
    return 1;
}

lua_State *h_lua_newstate(lua_Alloc f, void *ud)
{
    L = o_lua_newstate(f, ud);
    //telltale_hook::log::logln("[lua_newstate] Game has created a lua_State");
    return L;
}

#ifdef GAME_DEBUG
__int64 h_ScriptManager__LoadResource(lua_State *L, const char *filename, bool bAllowGlobals)
#elif defined(GAME_WIN64)
__int64 h_ScriptManager__LoadResource(lua_State *L, const char *filename)
#else
int h_ScriptManager__LoadResource(lua_State* L, char* filename)
#endif
{
    telltale_hook::log::log("[ScriptManager::LoadResource] Path: ");
    telltale_hook::log::logln(filename);
    lua_register(L, "tthookprint", tthook_print);

        // hack to redirect the games print calls and format them into one string
    luaL_dostring(L, "print = function(...)\n"
                     "  return tthookprint(string.format(...))\n"
                     "end");

    //lua_register(L, "IsDebugBuild", generic_true);

#ifdef GAME_DEBUG
    __int64 ret = o_ScriptManager__LoadResource(L, filename, bAllowGlobals);
#elif defined(GAME_WIN64)
    __int64 ret = o_ScriptManager__LoadResource(L, filename);
#else
    int ret = o_ScriptManager__LoadResource(L, filename);
#endif

    return ret;
}

CRC64_CaseInsensitiveptr o_CRC64_CaseInsensitive = NULL;
CRC32ptr o_CRC32 = NULL;

unsigned int h_CRC32(unsigned int crc, const char *const buffer, unsigned int count) {
    return o_CRC32(crc, buffer, count);
}

unsigned __int64 h_CRC64_CaseInsensitive(unsigned __int64 crc, const char* buf) {
    return o_CRC64_CaseInsensitive(crc, buf);
}

TTArchive2__Activateptr o_TTArchive2__Activate = NULL;


// hook left for future reference
int __fastcall h_TTArchive2__Activate(telltale_types::TTArchive2 *_this, telltale_types::Ptr<telltale_types::DataStream> a2)
{
    int ret = o_TTArchive2__Activate(_this, a2);
    return ret;
}

void telltale_hook::lua::setup_lua() {
    std::string game_executable = telltale_hook::get_current_game() + ".exe";

    #define PRINTSIZEOFTYPE(type) \
        telltale_hook::log::log("Size of "); \
        telltale_hook::log::log(#type); \
        telltale_hook::log::log(": "); \
        telltale_hook::log::logln(std::to_string(sizeof(type)));

    //PRINTSIZEOFTYPE(telltale_types::ResourceAddress);
    //PRINTSIZEOFTYPE(telltale_types::Ptr<telltale_types::DataStream>);
    //PRINTSIZEOFTYPE(telltale_types::DCArray<telltale_types::TTArchive2__ResourceEntry>);

    MH_STATUS status = MH_Initialize();
    if(status != MH_OK) {
        telltale_hook::log::logln("Failed to initialise MinHook: " + std::string(MH_StatusToString(status)));
    } else {
        telltale_hook::log::logln("Successfully initialised MinHook");
    }

    POPULATE_OFFSET_FUNCTION(lua_pcallk)

    POPULATE_OFFSET_FUNCTION(lua_pushcclosure)
    POPULATE_OFFSET_FUNCTION(lua_setglobal)

    POPULATE_OFFSET_FUNCTION(lua_tolstring)

    POPULATE_OFFSET_FUNCTION(luaL_loadfilex)
    POPULATE_OFFSET_FUNCTION(luaL_loadstring)

    POPULATE_OFFSET_FUNCTION(lua_pushboolean)

    POPULATE_OFFSET_FUNCTION(lua_gettop)

    //POPULATE_OFFSET_FUNCTION(CRC32)
    //HOOK_FUNCTION(CRC32)

    //POPULATE_OFFSET_FUNCTION(CRC64_CaseInsensitive)
    //HOOK_FUNCTION(CRC64_CaseInsensitive)

    POPULATE_OFFSET_FUNCTION(ScriptManager__LoadResource)
    HOOK_FUNCTION(ScriptManager__LoadResource)

    POPULATE_OFFSET_FUNCTION(lua_newstate)
    HOOK_FUNCTION(lua_newstate)

    bool key_down = false;
    while(true) {
        
        if(GetAsyncKeyState(VK_F1) & 0x1 && !key_down) {
            //luaL_dofile(L, "telltale_hook_test.lua");
            //luaL_dostring(L, "DebugMenu_ToggleButtons()");

            //save_db();
            key_down = true;
        }
        if(GetAsyncKeyState(VK_F2) & 0x1) {
            key_down = false;
        }
    }
}