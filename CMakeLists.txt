cmake_minimum_required(VERSION 3.5)
project(assn3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_VERBOSE_MAKEFILE ON)

set(ASSN3_SOURCE_FILES
        main.cpp
        TrimeshLoader.h
        Trimesh.h
        Trimesh.cpp
        OpenGLInterface.cpp
        OpenGLInterface.h
        Constants.h
        GLLight.cpp
        GLLight.h
        Scene.cpp
        Scene.h
        TrimeshLoader.cpp
        )

# set(GTEST_LIB_DIR         lib/libgtest.a)

# if (APPLE)
#     add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
#     add_definitions(-D__GLIBCXX__)
# endif (APPLE)

# Your-external "mylib"
# add_library( gtest SHARED IMPORTED )
# You can define two import-locations: one for debug and one for release.
# set_target_properties( gtest PROPERTIES IMPORTED_LOCATION ${GTEST_LIB_DIR} )

include_directories(include/gtest)

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

add_executable(assn3 ${ASSN3_SOURCE_FILES})

add_executable(tests

        TrimeshLoader.h
        Trimesh.h
        Trimesh.cpp
        OpenGLInterface.cpp
        OpenGLInterface.h
        Constants.h
        GLLight.cpp
        GLLight.h
        Scene.cpp
        Scene.h
        TrimeshLoader.cpp
        tests.cpp
        )

target_link_libraries(assn3 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )
target_link_libraries(tests ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )
#target_link_libraries(assn3 gtest)