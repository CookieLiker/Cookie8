cmake_minimum_required(VERSION 3.0.0)
project(Cookie8)

set(CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS system graphics audio REQUIRED)

include_directories(
    ${PROJECT_NAME}
    include
    ${SFML_INCLUDE_DIR}
)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/Application.cpp
    src/Chip8.cpp
    src/Display.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    sfml-graphics sfml-system sfml-audio
)