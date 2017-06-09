project(kTools LANGUAGES CXX)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Debug)
#~ set(CMAKE_BUILD_TYPE Release)

file(COPY kTools.png DESTINATION ${PROJECT_BINARY_DIR})
file(COPY kTools-refresh.png DESTINATION ${PROJECT_BINARY_DIR})

set(CPPFILES
  main.cpp
  ktMainForm.cpp
  ktPnBar.cpp
  ktPnMenu.cpp
  ktPnWrk.cpp
  ktPnVideoImp.cpp
)
set(FLTK_LIBS fltk fltk_images)
set(BOOST_LIBS boost_system boost_filesystem)

#~ set(FLTK_DIR /home/kan/wrk/fltk-1.3.4-1/build)
#~ set(FLTK_DIR /home/kan/wrk/fltk-1.4.x-r12244/build)
set(FLTK_DIR /home/kan/wrk/fltk-1.4.x-r12247/build)

find_package(FLTK REQUIRED NO_MODULE)

include_directories(${FLTK_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} WIN32 ${CPPFILES})
# target_include_directories(hello PUBLIC ${FLTK_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${FLTK_LIBS} ${BOOST_LIBS})

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
message(DEBUG)
 set_target_properties(${PROJECT_NAME}
PROPERTIES COMPILE_FLAGS "-Wall -fsanitize=address"
LINK_FLAGS "-fsanitize=address"
)
endif()
set_target_properties(${PROJECT_NAME}
PROPERTIES CXX_STANDARD 14
)
