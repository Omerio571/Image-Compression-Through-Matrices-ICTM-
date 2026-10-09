cmake_minimum_required(VERSION 3.20)

# ==========================================
# 1. Automatically Detect Project Name
# ==========================================

# Get the current folder name (supports spaces)
get_filename_component(
    FOLDER_NAME
    "${CMAKE_CURRENT_SOURCE_DIR}"
    NAME
)

# CMake target names cannot contain spaces.
# Convert spaces and special characters to underscores.
string(MAKE_C_IDENTIFIER
    "${FOLDER_NAME}"
    PROJECT_TARGET
)

project(${PROJECT_TARGET} LANGUAGES CXX)

# Keep the original folder name for the executable
set(EXECUTABLE_NAME "${FOLDER_NAME}")

# ==========================================
# 2. C++ Configuration
# ==========================================

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ==========================================
# 3. Automatically Create Folders
# ==========================================

set(PROJECT_FOLDERS
    "src"
    "include"
    "assets"
    "assets/input"
    "assets/output"
    "assets/compressed"
    "tests"
    "bin"
)

foreach(FOLDER IN LISTS PROJECT_FOLDERS)
    file(MAKE_DIRECTORY
        "${PROJECT_SOURCE_DIR}/${FOLDER}"
    )
endforeach()

# ==========================================
# 4. Automatically Create main.cpp
# ==========================================

set(MAIN_FILE "${PROJECT_SOURCE_DIR}/src/main.cpp")

if(NOT EXISTS "${MAIN_FILE}")
    file(WRITE "${MAIN_FILE}"
        "int main()\n{\n    return 0;\n}\n"
    )
endif()

# ==========================================
# 5. Download Libraries
# ==========================================

include(FetchContent)

# stb contains:
# - stb_image.h
# - stb_image_write.h
FetchContent_Declare(
    stb
    GIT_REPOSITORY "https://github.com/nothings/stb.git"
    GIT_TAG master
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(stb)

# ==========================================
# 6. Automatically Find Source Files
# ==========================================

file(GLOB_RECURSE SOURCE_FILES
    CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# ==========================================
# 7. Create Executable
# ==========================================

add_executable(${PROJECT_TARGET}
    ${SOURCE_FILES}
 "include/grabInfo.h" "src/grabInfo.cpp")

# Use original folder name, including spaces
set_target_properties(${PROJECT_TARGET} PROPERTIES
    OUTPUT_NAME "${EXECUTABLE_NAME}"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)

# Keep all build configurations inside bin/
foreach(CONFIG DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
    set_target_properties(${PROJECT_TARGET} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${CONFIG}
        "${PROJECT_SOURCE_DIR}/bin"
    )
endforeach()

# ==========================================
# 8. Include Directories
# ==========================================

target_include_directories(${PROJECT_TARGET} PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
    "${stb_SOURCE_DIR}"
)

# ==========================================
# 9. Compiler Warnings
# ==========================================

if(MSVC)
    target_compile_options(${PROJECT_TARGET} PRIVATE
        /W4
        /EHsc
    )
else()
    target_compile_options(${PROJECT_TARGET} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# ==========================================
# 10. Visual Studio Startup Project
# ==========================================

set_property(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    PROPERTY VS_STARTUP_PROJECT ${PROJECT_TARGET}
)

# ==========================================
# 11. Configuration Information
# ==========================================

message(STATUS "====================================")
message(STATUS "Project: ${FOLDER_NAME}")
message(STATUS "CMake Target: ${PROJECT_TARGET}")
message(STATUS "Executable: ${EXECUTABLE_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Source: ${PROJECT_SOURCE_DIR}")
message(STATUS "====================================")
