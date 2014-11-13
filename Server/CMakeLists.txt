cmake_minimum_required (VERSION 2.6)
 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -m32 -fPIC -fpermissive -w")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -fPIC -Wno-pointer-to-int-cast -Wno-attributes")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -std=c++0x -m32 -fshort-wchar -shared")

file(GLOB Server_SRC
    "*.cpp"
    "SDK/*.c"
    "SDK/*.cpp"
)

add_library(Server SHARED ${Server_SRC})

target_link_libraries(Server Common)

add_custom_command(TARGET Server
                   POST_BUILD
                   COMMAND rm ARGS -f sampp_server.so libCommon.a
                   COMMAND mv ARGS libServer.so sampp_server.so
                   WORKING_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
                   VERBATIM)
