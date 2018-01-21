set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")

file (GLOB_RECURSE Sources src/*)

add_executable (client ${Sources})

find_package(Threads REQUIRED)
target_link_libraries (client jsoncpp_lib_static Threads::Threads)
