
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(socketcluster_client)


# random bullshit
# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()
# end random bs

# find dependencies
find_package(jsonc REQUIRED)
find_package(boostbeast REQUIRED)

set(SOURCES)
set(dependencies
    jsonc
    boostbeast
)

add_executable(main src/main.cpp dependencies)


install(
    TARGETS maininstall(DIRECTORY
    config
    DESTINATION share/${PROJECT_NAME}
  )
)
