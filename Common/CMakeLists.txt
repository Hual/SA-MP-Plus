cmake_minimum_required (VERSION 2.6)
 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -m32 -fPIC -c -w -fpermissive")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -std=c++0x -m32 -fshort-wchar -static")

file(GLOB Common_SRC
    "*.cpp"
    "RakNet/*.cpp"
)

add_library(Common ${Common_SRC})
