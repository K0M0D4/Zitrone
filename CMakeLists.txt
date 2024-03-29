cmake_minimum_required(VERSION 3.22)
project(Zitrone VERSION 0.1.1 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)
set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_BUILD_AUDIO FALSE)
set(SFML_BUILD_NETWORK FALSE)

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(NFD
    GIT_REPOSITORY https://github.com/btzy/nativefiledialog-extended
    GIT_TAG master)
FetchContent_MakeAvailable(NFD)

set(TGUI_SHARED_LIBS FALSE)
set(TGUI_CXX_STANDARD 20)
set(TGUI_BUILD_GUI_BUILDER FALSE)
set(TGUI_USE_STATIC_STD_LIBS TRUE)

FetchContent_Declare(TGUI
    GIT_REPOSITORY https://github.com/texus/TGUI
    GIT_TAG 0.9)
FetchContent_MakeAvailable(TGUI)

add_executable(${PROJECT_NAME}    
    src/fw/ResourceManager.cpp
    src/fw/Theme.cpp
    src/fw/Line.cpp
    src/fw/DashLine.cpp

    src/main.cpp
    src/App.cpp
    src/Grid.cpp
    src/GridHints.cpp
    src/Note.cpp
    src/Project.cpp
    src/Config.cpp
    src/Settings.cpp
    )

target_compile_options(${PROJECT_NAME} PUBLIC -DSFML_STATIC)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-system sfml-window
    nfd tgui)

file(COPY res/ DESTINATION res/)
file(COPY config DESTINATION .)
