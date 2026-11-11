cmake_minimum_required(VERSION 3.20)
project(bbman CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

find_package(OpenSSL REQUIRED)

FetchContent_Declare(httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib
    GIT_TAG        master
)
FetchContent_MakeAvailable(httplib)

add_executable(bbman src/main.cpp)

target_compile_definitions(bbman PRIVATE CPPHTTPLIB_OPENSSL_SUPPORT)

target_link_libraries(bbman PRIVATE
    httplib::httplib
    OpenSSL::SSL
)
