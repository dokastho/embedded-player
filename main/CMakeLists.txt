# cmake_minimum_required(VERSION 3.22)

# project(embedded_player)

# set(CMAKE_CXX_COMPILER "clang++")
# set(CMAKE_C_COMPILER "clang")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -Wconversion -Wall -Werror -Wextra -pedantic")
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -DDEBUG")
# endif()

# if(CMAKE_BUILD_TYPE STREQUAL "Fast")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ofast")
# endif()

# file(GLOB SOURCES "src/*.c")
# list(FILTER SOURCES EXCLUDE REGEX "src/test_.*\\.c")

# add_executable(embedded_player_exe ${SOURCES})
# target_link_libraries(embedded_player_exe ${LLVM_LIBRARIES})
file(GLOB SOURCES "src/*.c")
idf_component_register(SRCS ${SOURCES}
                    INCLUDE_DIRS "")