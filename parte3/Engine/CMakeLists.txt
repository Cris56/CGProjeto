cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

# Project Name
PROJECT(engine)

# set(OpenGL_GL_PREFERENCE LEGACY)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(${PROJECT_NAME} src/main.cpp 
                               src/world.cpp 
                               src/group.cpp 
                               src/camera.cpp
                               src/xmlParser.cpp
                               src/model.cpp
                               src/transform.cpp
                               src/pugixml.cpp
                               src/point.cpp)

add_library(pugi STATIC src/pugixml.cpp)
target_include_directories(pugi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} pugi)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if  (WIN32)

    message(STATUS "Toolkits_DIR set to: " ${CMAKE_CURRENT_SOURCE_DIR}/toolkits)
    set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")

    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/toolkits/glut/GL/glut.h" OR NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/toolkits/glut/glut32.lib")
        message(ERROR ": GLUT not found")
    endif (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/toolkits/glut/GL/glut.h" OR NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/toolkits/glut/glut32.lib")    

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/toolkits/glut )
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} 
                                          ${CMAKE_CURRENT_SOURCE_DIR}/toolkits/glut/glut32.lib)

    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/toolkits/glut/glut32.dll" )
        file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/toolkits/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
    endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/toolkits/glut/glut32.dll" )    
    
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    
else (WIN32) #Linux and Mac

    include_directories(/opt/homebrew/include)
    include_directories(/opt/homebrew/Cellar/glew/2.2.0_1/include)
    set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")
    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})
    find_package(GLEW 2.0 REQUIRED)
    include_directories(${GLEW_INCLUDE_DIR})
    link_directories(${GLEW_LIBRARY_DIRS})
    add_definitions(${GLEW_DEFINITIONS})

    target_link_libraries(${PROJECT_NAME} "-F${CMAKE_OSX_SYSROOT}/System/Library/Frameworks" "-framework GLUT")
    target_link_libraries(${PROJECT_NAME} "-F${CMAKE_OSX_SYSROOT}/System/Library/Frameworks" "-framework OpenGL")
    target_link_libraries(${PROJECT_NAME} GLEW::GLEW)

    if(NOT GLUT_FOUND)
       message(ERROR ": GLUT not found!")
    endif(NOT GLUT_FOUND)
    
endif(WIN32)

# Add preprocessor definitions
add_definitions(-DCMAKE_INTDIR="Debug")
add_definitions(-DGLUT_BUILDING_LIB)
