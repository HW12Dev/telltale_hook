cmake_minimum_required(VERSION 3.18)
project(telltale_hook LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TELLTALE_GAME SMSTW_REMASTERED)

set(IMGUI_DIR "Dependencies/imgui-1.90/")
set(NLOHMANN_JSON_DIR "Dependencies/nlohmann-json/")

message("Compiling for ${TELLTALE_GAME}")

add_subdirectory("Dependencies/minhook")

set(IMGUI_INCLUDE
    ${IMGUI_DIR})

set(IMGUI_SOURCES
    ${IMGUI_DIR}imconfig.h
    ${IMGUI_DIR}imgui_demo.cpp
    ${IMGUI_DIR}imgui_draw.cpp
    ${IMGUI_DIR}imgui_internal.h
    ${IMGUI_DIR}imgui_tables.cpp
    ${IMGUI_DIR}imgui_widgets.cpp
    ${IMGUI_DIR}imgui.cpp
    ${IMGUI_DIR}imgui.h
    ${IMGUI_DIR}imstb_rectpack.h
    ${IMGUI_DIR}imstb_textedit.h
    ${IMGUI_DIR}imstb_truetype.h
    
    ${IMGUI_DIR}backends/imgui_impl_dx9.cpp
    ${IMGUI_DIR}backends/imgui_impl_dx9.h
    ${IMGUI_DIR}backends/imgui_impl_win32.cpp
    ${IMGUI_DIR}backends/imgui_impl_win32.h)

add_compile_definitions(GAME_${TELLTALE_GAME})

file(GLOB_RECURSE SOURCE src/*.cpp src/*.h)

include_directories(
    include
    ${NLOHMANN_JSON_DIR}include
    Dependencies/minhook/include
    #${IMGUI_INCLUDE}
    )

add_library(telltale_hook SHARED
            #${IMGUI_SOURCES}
            ${SOURCE})

target_link_libraries(telltale_hook minhook)

add_library(dinput8 SHARED
            proxy/src/main.cpp)