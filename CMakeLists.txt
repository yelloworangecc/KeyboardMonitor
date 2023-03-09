cmake_minimum_required(VERSION 2.8.12.1)
cmake_policy(SET CMP0048 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CONFIGURATION_TYPES Debug Release)

project(KeybordMonitor VERSION 1.0.0)

include_directories( "${PROJECT_SOURCE_DIR}/include" )

file(GLOB_RECURSE SRC_LIST
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.h"
)
   
file(GLOB_RECURSE RC_LIST
    "${PROJECT_SOURCE_DIR}/res/*.rc"
)

add_executable(KeybordMonitor WIN32
    ${SRC_LIST}
    ${RC_LIST}
)

add_library(HookProc SHARED
  "${PROJECT_SOURCE_DIR}/src/HookProc.cxx"
)

target_link_libraries(KeybordMonitor
  HookProc
)
