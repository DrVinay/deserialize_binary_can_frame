cmake_minimum_required(VERSION 3.14)
project(DeserializeBinaryCanFrame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(include)

# Create library target
add_library(canframe_lib
    src/deserialize_binary_can_frame.cpp
)

# Create test executable
add_executable(tests
    tests/test_can_parser.cpp
)

# Link library to tests
target_link_libraries(tests PRIVATE canframe_lib)