cmake_minimum_required(VERSION 4.0)
project(poem LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include directories
include_directories(src)

# Add executable
add_executable(${PROJECT_NAME}
    src/main.c
)

set(ABS_BIN_DIR ${CMAKE_SOURCE_DIR}/out/build/bin)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${ABS_BIN_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${ABS_BIN_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${ABS_BIN_DIR}
)

# Compiler-specific options
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Debug-only flags (safe for all generators)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

if(NOT MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:-g -O0>
    )
endif()

# Enable testing
# enable_testing()

# Install target
# install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
