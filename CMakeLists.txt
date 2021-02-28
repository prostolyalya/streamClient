cmake_minimum_required(VERSION 3.17)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
project(streamClient LANGUAGES CXX)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/headers
    ${CMAKE_CURRENT_SOURCE_DIR}/sources
)
#/home/ykulevskyi/Qt/6.0.0/gcc_64/lib/cmake/Qt6
set(SRC_LIST
    "sources/thread_pool.cpp"
    "sources/client.cpp"
    "sources/receiver.cpp"
    "sources/sender.cpp"
    "sources/ui_controller.cpp"
    "sources/stream_client.cpp"
    "sources/cryptor.cpp"
    "sources/serializer.cpp"
    "sources/authentificator.cpp"
)
set(HDRS_LIST
    "include/headers/thread_pool.h"
    "include/headers/client.h"
    "include/headers/sender.h"
    "include/headers/receiver.h"
    "include/headers/stream_client.h"
    "include/headers/ui_controller.h"
    "include/headers/cryptor.h"
    "include/headers/serializer.h"
    "include/headers/authentificator.h"
    "qml.qrc"
)
#set(CMAKE_PREFIX_PATH "/home/main/Qt/5.15.0/gcc_64/lib/cmake")
find_package(Qt5 REQUIRED COMPONENTS Core Network Qml Quick MultimediaWidgets Multimedia)
#find_package(Boost COMPONENTS thread system REQUIRED)
#include_directories(include/lib/boost)
#include_directories(${Boost_INCLUDE_DIR})
add_executable(streamClient
  main.cpp
  ${SRC_LIST}
  ${HDRS_LIST}
)
#target_compile_definitions(streamClient
#  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(streamClient Qt::Core Qt::Network Qt::Qml Qt::Quick Qt::Widgets Qt::Multimedia Qt::MultimediaWidgets)#${Boost_LIBRARIES}
target_include_directories(streamClient PUBLIC include)
