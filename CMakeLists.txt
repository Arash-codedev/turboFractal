################################################################################
#          Warning: auto-generated code and subjected to be overwritten        #
#                   Generator function: (code_generator_cmake)                 #
################################################################################


cmake_minimum_required(VERSION 2.8.9)
project (main)

find_package(Threads)

if(APPLE)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
endif()

include_directories(.)

# Detect operating system
message(STATUS "Detected operating system: ${CMAKE_SYSTEM_NAME}")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_definitions(-DSYSTEM_LINUX)
endif()
if(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    add_definitions(-DSYSTEM_FREEBSD)
endif()
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions(-DSYSTEM_WINDOWS)
endif()

# Libraries
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS filesystem regex system thread date_time wave) 

if(NOT Boost_FOUND)
	message( FATAL_ERROR "Boost 1.45.0 not found." )
endif()
include_directories(SYSTEM ${Boost_INCLUDE_DIR})

# Flags
set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -Wconversion -Wfatal-errors -Wextra -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(${Boost_INCLUDE_DIRS}) 

# pre executable commands


add_executable(main
    types/complex.cpp
    manager/manager.cpp
    fractal/mandelbrot.cpp
    fractal/fast_mandelbrot.cpp
    colorize/escape_time.cpp
    colorize/smooth.cpp
    main.cpp
)


# Link
target_link_libraries(main ${Boost_LIBRARIES})
target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT})

find_package(OpenSSL)
target_link_libraries(main ${OPENSSL_LIBRARIES})
target_link_libraries(main ${SSL_LIB})
target_link_libraries(main ${CRYPTO_LIB})


if(OPENSSL_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_OPENSSL")
    target_link_libraries(main ${OPENSSL_LIBRARIES})
    include_directories(SYSTEM ${OPENSSL_INCLUDE_DIR})
endif()

if(MSYS)
    target_link_libraries(main ws2_32 wsock32)
endif()

# post executable commands
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})
target_link_libraries(main ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(main ${SDL2_LIBRARIES})
target_link_libraries(main gmp)
