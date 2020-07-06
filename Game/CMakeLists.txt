cmake_minimum_required(VERSION 3.0.0)
#Ищем все исполняемые файлы
file(GLOB_RECURSE _SOURSCES "*.cpp")
file(GLOB_RECURSE _HEADERS "*.h")

set(_NAME Game)

add_library(${_NAME} STATIC ${_SOURSCES} ${_HEADERS} ${_TAMPLATES} )
target_include_directories(${_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
