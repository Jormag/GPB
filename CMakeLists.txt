cmake_minimum_required(VERSION 3.8)
project(GPB)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BackTracking/BackTracking.cpp)
add_executable(GPB ${SOURCE_FILES})


INCLUDE_DIRECTORIES(  /usr/local/Cellar/allegro/5.0/include )
LINK_DIRECTORIES(  /usr/local/Cellar/allegro/5.0/lib )

file(GLOB LIBRARIES "/usr/local/Cellar/allegro/5.0lib/*.dylib")
message("LIBRARIES = ${LIBRARIES}")

TARGET_LINK_LIBRARIES(GPB  ${LIBRARIES})

TARGET_LINK_LIBRARIES(GPB  allegro_acodec
        allegro_audio
        allegro_color
        allegro_dialog
        allegro_image
        allegro_main
        allegro_memfile
        allegro_physfs
        allegro_primitives
        allegro_ttf
        allegro_font
        allegro)