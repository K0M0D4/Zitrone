cmake_minimum_required(VERSION 3.24)
project(Zitrone VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)
set(SFML_STATIC_LIBRARIES TRUE)

add_subdirectory(dep/SFML)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/App.cpp
    
    src/fw/ResourceManager.cpp
    src/fw/Button.cpp
    src/fw/ImageButton.cpp
    src/fw/TextButton.cpp
    )

set_property(TARGET ${PROJECT_NAME} PROPERTY COMPILE_WARNING_AS_ERROR OFF)

target_include_directories(${PROJECT_NAME} PUBLIC dep/SFML/include)
target_compile_options(${PROJECT_NAME} PUBLIC -DSFML_STATIC)

target_link_libraries(${PROJECT_NAME}
    sfml-graphics sfml-system sfml-window sfml-audio sfml-network)

file(COPY res/ DESTINATION res/)