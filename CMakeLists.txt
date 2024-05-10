cmake_minimum_required(VERSION 3.10)
project(SDL_ResearchWork)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

file(GLOB_RECURSE SRCS "src/*.cpp" "src/*.h")
include_directories(src)

file(COPY assets DESTINATION ${PROJECT_BINARY_DIR})

add_executable(mygame ${SRCS})
target_link_libraries(mygame SDL2::Main SDL2::Image SDL2::TTF)
