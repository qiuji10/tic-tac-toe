cmake_minimum_required(VERSION 3.20)

project(tic-tac-toe
    VERSION 1.0.0
    DESCRIPTION "A simple Tic Tac Toe game"
    LANGUAGES CXX
)

# =============================================================================
# COMPILER SETTINGS
# =============================================================================


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    # Windows - Visual Studio compiler
    add_compile_options(/W4)        # High warning level
    add_compile_options(/WX)        # Treat warnings as errors
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Mac/Linux - Clang or GCC
    add_compile_options(-Wall -Wextra -Werror)  # All warnings, treat as errors
endif()

# Debug vs Release configurations
if(MSVC)
    # Let MSVC handle Debug/Release flags automatically
    # Debug: /Od /RTC1 /MDd (automatic)
    # Release: /O2 /MD (automatic)
    add_compile_definitions($<$<CONFIG:Debug>:DEBUG_MODE>)
    add_compile_definitions($<$<CONFIG:Release>:RELEASE_MODE>)
else()
    # GCC/Clang manual configuration
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_definitions(DEBUG_MODE)
        add_compile_options(-O0 -g)
    else()
        add_compile_definitions(RELEASE_MODE)
        add_compile_options(-O3)
    endif()
endif()


# =============================================================================
# PROJECT STRUCTURE
# =============================================================================

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# =============================================================================
# PLATFORM-SPECIFIC SETTINGS
# =============================================================================

# Windows specific
if(WIN32)
    # Enable console on Windows
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
endif()

# macOS specific
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE FALSE  # Console app, not bundle
    )
endif()