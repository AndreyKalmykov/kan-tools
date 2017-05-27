project(kTools LANGUAGES CXX)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)

file(COPY kTools.png DESTINATION ${PROJECT_BINARY_DIR})

set(CPPFILES
  main.cpp
  ktMainForm.cpp
  ktPnBar.cpp
  ktPnMenu.cpp
  ktPnWrk.cpp
)


#~ set(FLTK_DIR /home/kan/wrk/libs/share/fltk)
#~ set(FLTK_DIR /home/kan/wrk/fltk-1.3.4-1/build)
set(FLTK_DIR /home/kan/wrk/fltk-1.4.x-r12244/build)

find_package(FLTK REQUIRED NO_MODULE)

include_directories(${FLTK_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} WIN32 ${CPPFILES})
# target_include_directories(hello PUBLIC ${FLTK_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} fltk fltk_images)

set_target_properties(${PROJECT_NAME}
PROPERTIES CXX_STANDARD 14
COMPILE_FLAGS "-Wall -fsanitize=address"
LINK_FLAGS "-fsanitize=address"
)
