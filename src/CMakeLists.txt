cmake_minimum_required(VERSION 3.10)
project(StatusFetch C)

set(CMAKE_C_STANDARD 11)

set(SOURCES program.c)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND SOURCES linux.c)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list(APPEND SOURCES windows.c)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    list(APPEND SOURCES macos.c)
else()
    message(FATAL_ERROR "Unsupported OS: ${CMAKE_SYSTEM_NAME}")
endif()

find_package(CURL REQUIRED)

add_executable(statusfetch ${SOURCES})

target_include_directories(statusfetch PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(statusfetch PRIVATE ${CURL_LIBRARIES})

