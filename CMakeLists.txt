project(kTools LANGUAGES CXX)
cmake_minimum_required(VERSION 3.7)

set(CMAKE_BUILD_TYPE Debug)
#~ set(CMAKE_BUILD_TYPE Release)

file(COPY kTools.png DESTINATION ${PROJECT_BINARY_DIR})
file(COPY kt-refresh.png DESTINATION ${PROJECT_BINARY_DIR})

set(SRC_LIST
  #~ main.cpp
  ktApp.cpp
  ktMainWindow.cpp
  #~ ktMainForm.cpp
  #~ ktPnBar.cpp
  #~ ktPnMenu.cpp
  #~ ktPnWrk.cpp
  #~ ktPnVideoImp.cpp
  #~ ktPnVideoProxy.cpp
)
#~ set(BOOST_LIBS boost_system boost_filesystem)

#~ set(FLTK_DIR /home/kan/wrk/fltk-1.4.x-r12261/build)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

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
