# https://www.jianshu.com/p/c31b00acc57b
# https://blog.csdn.net/afei__/article/details/81201039

# CMake 最低版本要求
cmake_minimum_required(VERSION 3.15)

# 项目名
# set(APP_NAME LearnPBRT)
project(MosqSoftwareRenderer)

# 使用C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(GROUP_BY_EXPLORER ON) 

file(GLOB_RECURSE ALL_FILES "src/*.h*" "src/*.c*")

# 定义按目录结构归类的方法
function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)

foreach(_source IN ITEMS ${ALL_FILES})
    assign_source_group(${_source})
endforeach()


include_directories(${PROJECT_SOURCE_DIR})
include_directories ("${PROJECT_SOURCE_DIR}/src/core/sdl/include")
include_directories ("${PROJECT_SOURCE_DIR}/src/public")
include_directories ("${PROJECT_SOURCE_DIR}/src/core/renderer")


#include_directories ("${PROJECT_SOURCE_DIR}/src/core")
#include_directories ("${PROJECT_SOURCE_DIR}/src/ext")
#include_directories ("${PROJECT_SOURCE_DIR}/src/acceleratoprs")
#include_directories ("${PROJECT_SOURCE_DIR}/src/parser")
#include_directories ("${PROJECT_SOURCE_DIR}/third")
#include_directories ("${PROJECT_SOURCE_DIR}/third/glog")

# https://blog.csdn.net/qq_27550989/article/details/89240376
# 对应exe项目，glog需要加一个宏
# add_definitions(-D GOOGLE_GLOG_DLL_DECL=)

add_executable(MosqSoftwareRenderer ${ALL_FILES})

# 添加链接库
target_link_libraries(MosqSoftwareRenderer ${CMAKE_CURRENT_SOURCE_DIR}/src/core/sdl/SDL2.lib)
target_link_libraries(MosqSoftwareRenderer ${CMAKE_CURRENT_SOURCE_DIR}/src/core/sdl/SDL2main.lib)

#target_link_libraries(MosqSoftwareRenderer ${CMAKE_CURRENT_SOURCE_DIR}/src/ext/SDL/SDL2maind.lib)
#target_link_libraries(MosqSoftwareRenderer ${CMAKE_CURRENT_SOURCE_DIR}/src/ext/SDL/SDL2-staticd.lib)