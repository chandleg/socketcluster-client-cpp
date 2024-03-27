cmake_minimum_required(VERSION 3.10) # Example minimum version
set(CMAKE_CXX_STANDARD 17)

#### Catch2 Fetch ####
FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.3 # Or your desired version
)
FetchContent_MakeAvailable(Catch2)
####

# Create a test executable
add_executable(tests test.cpp) 

target_link_libraries(tests PRIVATE SocketClusterClientCPP Catch2::Catch2WithMain) 