cmake_minimum_required(VERSION 3.10) # Example minimum version
set(CMAKE_CXX_STANDARD 17)

# Attempt to find Catch2 on the system
find_package(Catch2 3.5.3 QUIET)

if(NOT Catch2_FOUND)
    # Catch2 not found on the system, so fetch it from the repository
    include(FetchContent)
    FetchContent_Declare(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.3 # Or your desired version
    )
    FetchContent_MakeAvailable(Catch2)
endif()

# Create a test executable
add_executable(tests test.cpp) 

target_link_libraries(tests PRIVATE SocketClusterClientCPP Catch2::Catch2WithMain)
