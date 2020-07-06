cmake_minimum_required(VERSION 3.0.0)
project(PROJECT VERSION 0.1.0)

#Год плюсов
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -lGL -lGLU -lglut")
#set(CMAKE_CXX_STANDARD 17) 

#Ищем все исполняемые файлы
file(GLOB _SOURSCES "*.cpp")
file(GLOB _HEADERS "*.h")

find_package(OpenGL)
find_package(GLUT)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

#Добавляем в сборку исполняемые файлы
add_executable(${PROJECT_NAME} ${_SOURSCES})

#Добавляем поддиректорию для поиска подфайла Cmake
add_subdirectory(Common)
add_subdirectory(Geometry)
add_subdirectory(Game)


#Линкуем
target_link_libraries(${PROJECT_NAME}
                      ${OPENGL_gl_LIBRARY}
                      ${GLUT_LIBRARIES}
                      Common Geometry Game)