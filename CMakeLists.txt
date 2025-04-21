cmake_minimum_required(VERSION 3.10)
project(cppnb)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(third_party/imgui)
add_subdirectory(third_party/TextEditor)
add_subdirectory(third_party/imgui_markdown)
add_subdirectory(third_party/ImPlot)

find_package(SDL2 REQUIRED)

# Add glad source file
add_library(glad STATIC third_party/glad/src/glad.c)

target_include_directories(glad PUBLIC third_party/glad/include)

message(STATUS "SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_LIBRARIES: ${SDL2_LIBRARIES}")

# Explicitly list all source files to ensure they are included
set(SRC
    main.cpp
    src/ui/notebook.cpp
    src/ui/code_cell.cpp
    src/ui/markdown_cell.cpp
    src/utils/logger.cpp
)

add_executable(cppnb ${SRC})

target_include_directories(cppnb PRIVATE
    third_party/imgui
    third_party/imgui/backends  # Ensure imgui backends include directory is added
    third_party/TextEditor
    third_party/imgui_markdown
    third_party/ImPlot
    third_party/glad/include  # Add glad include directory
    src  # Add src directory
    ${SDL2_INCLUDE_DIRS}
)

# Link libraries using the keyword signature
target_link_libraries(cppnb PRIVATE
    glad
    imgui
    TextEditor
    imgui_markdown
    ImPlot
    ${SDL2_LIBRARIES}
)

# Set the architecture explicitly
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64")  # Use "x86_64" for Intel-based Macs
endif()

# Explicitly link OpenGL framework on macOS
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64")  # Use "x86_64" for Intel-based Macs
    target_link_libraries(cppnb PRIVATE "-framework OpenGL")
else()
    target_link_libraries(cppnb PRIVATE OpenGL::GL)
endif()
