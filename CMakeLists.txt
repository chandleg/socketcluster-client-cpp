cmake_minimum_required(VERSION 3.10) # Example minimum version
set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -coverage")
# set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage -O0")
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0")

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

# Build Library
# Find source files
file(GLOB_RECURSE LIBRARY_SOURCES src/*.cpp)

# Create the library
add_library(SocketClusterClientCPP SHARED ${LIBRARY_SOURCES}) 

# Link against json-c
target_link_libraries(SocketClusterClientCPP PRIVATE jsoncpp_static)

# Update include directories to find json-c headers
target_include_directories(SocketClusterClientCPP PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${JsonCpp_SOURCE_DIR}/_deps/jsoncpp-src/include> 
    $<BUILD_INTERFACE:${websocketpp_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${asio_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${jsoncpp_SOURCE_DIR}/include>
)

# Install targets and headers
install(TARGETS SocketClusterClientCPP 
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(DIRECTORY src/ 
        DESTINATION include)

# Coverage
option(BUILD_TESTING "Builds only the test executable." ON)
option(CODE_COVERAGE "Collect coverage from test library" ON)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
    add_test(NAME project_tests COMMAND ./bin/tests)

    if(CODE_COVERAGE AND CMAKE_BUILD_TYPE MATCHES Debug)
      # Set the coverage report output directory
      set(COVERAGE_DIR ${CMAKE_BINARY_DIR}/coverage)

      # Clean the coverage directory
      add_custom_target(coverage_clean
          COMMAND ${CMAKE_COMMAND} -E rm -rf ${COVERAGE_DIR}
      )

      # Add a target to run the tests and collect coverage information
      add_custom_target(coverage
          COMMAND ${CMAKE_COMMAND} -E make_directory ${COVERAGE_DIR}
          COMMAND ${CMAKE_COMMAND} -E env LCOV_OPTS="--rc lcov_branch_coverage=1 geninfo_unexecuted_blocks=1" $<TARGET_FILE:tests>
          WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
          DEPENDS tests coverage_clean
          COMMENT "Running tests and collecting coverage data..."
      )

      # Add a target to generate the coverage report
      # Add a target to generate the coverage report
      # Add a target to generate the coverage report
      add_custom_target(coverage_report
        COMMAND lcov --capture --directory . --output-file ${COVERAGE_DIR}/coverage.info --ignore-errors source,unused
        # Remove coverage data for external libraries, including Catch2
        COMMAND lcov --remove ${COVERAGE_DIR}/coverage.info "/usr/*" "${CMAKE_BINARY_DIR}/_deps/*" --output-file ${COVERAGE_DIR}/filtered.info --ignore-errors source,unused
        # Optional: Add more --remove lines as needed to exclude other directories or files
        COMMAND lcov --list ${COVERAGE_DIR}/filtered.info
        COMMAND genhtml -o ${COVERAGE_DIR}/html ${COVERAGE_DIR}/filtered.info 
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS coverage
        COMMENT "Generating coverage report..."
      )


    endif()


    # if(CODE_COVERAGE)
    #     set(CODE_COVERAGE_VERBOSE TRUE)
    #     include(CodeCoverage.cmake)
    #     # append_coverage_compiler_flags()
    #     append_coverage_compiler_flags_to_target(SocketClusterClientCPP)
    #     # set(COVERAGE_EXCLUDES "src/*")
    #     setup_target_for_coverage_lcov(
    #       NAME coverage
    #       EXECUTABLE ./bin/tests
    #       # BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/src/"
    #       # EXCLUDE "*.cpp"
    #     )
        
    #     # setup_target_for_coverage_lcov(
    #     #     NAME coverage
    #     #     EXECUTABLE ./bin/tests
    #     #     EXCLUDE "${PROJECT_SOURCE_DIR}/_deps/*"
    #     #             "${PROJECT_BINARY_DIR}/*"
    #     #             "${PROJECT_SOURCE_DIR}/test/*"
    #     # )
    # endif()
endif()





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
