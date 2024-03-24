cmake_minimum_required(VERSION 3.10) # Example minimum version
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")


project(SocketClusterClientCPP)

include(FetchContent)

# === JsonCPP ===
FetchContent_Declare(JsonCpp
  GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
  GIT_TAG 1.9.5 # Or your desired version
)
FetchContent_MakeAvailable(JsonCpp)
# === ===

# Fetch WebSocket++
FetchContent_Declare(
  websocketpp
  GIT_REPOSITORY https://github.com/zaphoyd/websocketpp.git
  GIT_TAG master # It's better to use a specific commit or tag for reproducibility
)

# Make WebSocket++ available for #include
FetchContent_GetProperties(websocketpp)
if(NOT websocketpp_POPULATED)
  FetchContent_Populate(websocketpp)
  include_directories(${websocketpp_SOURCE_DIR})
endif()

# Fetch Asio (standalone version, without Boost)
FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG asio-1-18-1 # Use a specific tag or commit to ensure reproducibility
)

# Make Asio available for #include
FetchContent_GetProperties(asio)
if(NOT asio_POPULATED)
  FetchContent_Populate(asio)
  include_directories(${asio_SOURCE_DIR}/asio/include)
  add_definitions(-DASIO_STANDALONE)
endif()


#### Catch2 Fetch ####
FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.3 # Or your desired version
)
FetchContent_MakeAvailable(Catch2)
####

# Find source files
file(GLOB_RECURSE LIBRARY_SOURCES src/*.cpp)

# Create the library
add_library(SocketClusterClientCPP SHARED ${LIBRARY_SOURCES}) 

# Specify public include directories
target_include_directories(SocketClusterClientCPP PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

# Link against json-c
target_link_libraries(SocketClusterClientCPP PRIVATE jsoncpp_lib)

message(STATUS "JsonCpp_SOURCE_DIR is set to ${JsonCpp_SOURCE_DIR}")

# Update include directories to find json-c headers
target_include_directories(SocketClusterClientCPP PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${JsonCpp_SOURCE_DIR}/_deps/jsoncpp-src/include> 
    $<BUILD_INTERFACE:${websocketpp_SOURCE_DIR}/include
    $<BUILD_INTERFACE:${asio_SOURCE_DIR}/include
    build/_deps/jsoncpp-src/include
)
# todo remove bad jsoncpp target include 

# Install targets and headers
install(TARGETS SocketClusterClientCPP 
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(DIRECTORY src/ 
        DESTINATION include)

# Create a test executable
add_executable(tests test/test.cpp) 

# Link libraries
target_link_libraries(tests PRIVATE SocketClusterClientCPP Catch2::Catch2WithMain) 




# # === websocket++ ===
# FetchContent_Declare(websocketpp
#     GIT_REPOSITORY https://github.com/zaphoyd/websocketpp.git
#     GIT_TAG 0.8.2
# )
# FetchContent_GetProperties(websocketpp)
# if(NOT websocketpp_POPULATED)
#   FetchContent_Populate(websocketpp)
#   add_subdirectory(${websocketpp_SOURCE_DIR} ${websocketpp_BINARY_DIR} EXCLUDE_FROM_ALL)
# endif()
# add_library(Websockets INTERFACE)
# # === ===

# # === boost++ ===
# FetchContent_Declare(
#   Boost
#   GIT_REPOSITORY https://github.com/boostorg/boost.git
#   GIT_TAG boost-1.80.0 # Replace with your desired version
# )
# FetchContent_MakeAvailable(Boost)
