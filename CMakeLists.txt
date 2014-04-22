cmake_minimum_required (VERSION 2.8)
project (FrustumCulling)
set(VERSION "0.1.0")

# Required libraries in this source dir
# add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)

find_package(OPENGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# use GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

# include paths
# include_directories(${GLUT_INCLUDE_DIRS} lib/glfw/include src)
include_directories(${GLUT_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} src)

if (NOT APPLE)
    # HACK: This is NOTFOUND on OS X 10.8
    include_directories(${OPENGL_INCLUDE_DIR})
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

file(GLOB_RECURSE frustum_SOURCE "src/frustum/*.cpp" "src/engine/*.cpp")
file(GLOB_RECURSE woods_SOURCE "src/woods/*.cpp" "src/engine/*.cpp")

if (APPLE)
    set(OSX_ICON_FILES ${CMAKE_CURRENT_SOURCE_DIR}/icons/Woods.icns)
    # set where in the bundle to put the icns files
    set_source_files_properties(${OSX_ICON_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    # include the icns files in the target
    set( woods_SOURCE ${woods_SOURCE} ${OSX_ICON_FILES} )
endif()

add_executable(FrustumCulling WIN32 ${frustum_SOURCE})
add_executable(Woods WIN32 MACOSX_BUNDLE ${woods_SOURCE})

if (APPLE)
    set_target_properties(FrustumCulling PROPERTIES
                          MACOSX_BUNDLE_BUNDLE_NAME "FrustumCulling"
                          MACOSX_BUNDLE_ICON_FILE   "FrustumCulling"
                          MACOSX_BUNDLE_SHORT_VERSION_STRING ${VERSION}
                          MACOSX_BUNDLE_LONG_VERSION_STRING "FrustumCulling - Version ${VERSION}")
    set_target_properties(Woods PROPERTIES
                          MACOSX_BUNDLE_BUNDLE_NAME "Woods"
                          MACOSX_BUNDLE_ICON_FILE   "Woods"
                          MACOSX_BUNDLE_SHORT_VERSION_STRING ${VERSION}
                          MACOSX_BUNDLE_LONG_VERSION_STRING "Woods - Version ${VERSION}")
endif()

if (MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(FrustumCulling PROPERTIES
                          LINK_FLAGS "/ENTRY:mainCRTStartup")
    set_target_properties(Woods PROPERTIES
                          LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

set(CMAKE_CXX_FLAGS "-stdlib=libc++")
#target_link_libraries(FrustumCulling glfw ${GLFW_LIBRARIES} ${GLUT_LIBRARIES})

target_link_libraries(FrustumCulling ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
target_link_libraries(Woods ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

