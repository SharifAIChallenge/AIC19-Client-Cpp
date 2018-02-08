set (CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Og -g")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O2")

file (GLOB_RECURSE Sources src/*)

add_executable (client ${Sources})

target_include_directories (client PRIVATE src/)

find_package(Threads REQUIRED)
target_link_libraries (client jsoncpp_lib_static Threads::Threads)
