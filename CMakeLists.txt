cmake_minimum_required(VERSION 3.20)
project(bbman CXX)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

find_package(OpenSSL REQUIRED)

FetchContent_Declare(httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib
    GIT_TAG        master
)
FetchContent_MakeAvailable(httplib)

FetchContent_Declare(tinyxml2
    GIT_REPOSITORY https://github.com/leethomason/tinyxml2
    GIT_TAG        master
)
FetchContent_MakeAvailable(tinyxml2)

add_executable(bbman src/main.cpp src/eoutln.cpp)

target_compile_definitions(bbman PRIVATE CPPHTTPLIB_OPENSSL_SUPPORT)

target_link_libraries(bbman PRIVATE
    httplib::httplib
    OpenSSL::SSL
    tinyxml2::tinyxml2
)
