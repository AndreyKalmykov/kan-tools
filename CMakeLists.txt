project(kTools)
cmake_minimum_required(VERSION 2.8)

set(CPPFILES
  main.cpp
  ktMainForm.cpp
  ktPnMenu.cpp
  ktPnWrk.cpp
)

set(NANA_LIB "/home/kan/wrk/libs/lib/libnana.a")
set(NANA_INC "/home/kan/wrk/libs/include")

include_directories(${NANA_INC})

find_package(Freetype)
include_directories( ${FREETYPE_INCLUDE_DIRS})

set(STD_LIBS -lX11 -lpthread -lXft -lfontconfig -lstdc++fs)

add_executable(${PROJECT_NAME} ${CPPFILES})

target_link_libraries(${PROJECT_NAME} ${NANA_LIB} ${STD_LIBS})

set_property( TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14 )
