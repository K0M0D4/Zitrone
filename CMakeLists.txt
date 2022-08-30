cmake_minimum_required(VERSION 3.24)
project(Zitrone)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SAHRED_LIBS FALSE)
set(SFML_STATIC_LIBRARIES FALSE)
set(CMAKE_BUILD_TYPE Debug)
add_subdirectory(dep/SFML)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/App.cpp
    
    src/fw/ResourceManager.cpp
    src/fw/Button.cpp
    )

target_include_directories(${PROJECT_NAME} PUBLIC dep/SFML/include)
target_compile_options(${PROJECT_NAME} PUBLIC -DSFML_STATIC)

target_link_libraries(${PROJECT_NAME}
    sfml-graphics sfml-system sfml-window sfml-audio sfml-network)

file(COPY res/ DESTINATION res/)