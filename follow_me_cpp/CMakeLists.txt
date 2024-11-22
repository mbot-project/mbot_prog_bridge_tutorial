cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(follow_me)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(mbot_bridge REQUIRED)

# Follow me executable.
add_executable(follow_me src/follow_me.cpp
)
target_link_libraries(follow_me
  mbot_bridge_cpp
)
target_include_directories(follow_me PRIVATE
)

if (CMAKE_BUILD_TYPE MATCHES Test)
endif()
