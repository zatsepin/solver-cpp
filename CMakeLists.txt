#
# solver-cpp - C++ sudoku solver
#
CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)

PROJECT(solver-cpp CXX)

# ################################################################################
# Defaults
#
OPTION(DEBUG_MODE          "Enable debug output [default: OFF]" OFF)
OPTION(ENABLE_OPTIMIZATION "Enable optimization [default: OFF]" ON)

# ################################################################################
# Macroses
#
# Standard CMake macroses
INCLUDE(CheckIncludeFiles)
INCLUDE(CheckCXXCompilerFlag)
INCLUDE(CheckCXXSourceCompiles)
INCLUDE(CheckSymbolExists)
INCLUDE(CheckLibraryExists)

# ################################################################################
# Version
#
SET(SOLVER_VERSION_MAJOR 0)
SET(SOLVER_VERSION_MINOR 1)
SET(SOLVER_VERSION_PATCH 0)
SET(SOLVER_VERSION "${SOLVER_VERSION_MAJOR}.${SOLVER_VERSION_MINOR}.${SOLVER_VERSION_PATCH}")
MESSAGE(STATUS "#### Version is: ${SOLVER_VERSION}")

# ################################################################################
# Set system-specific data
#
MESSAGE(STATUS "#### System name is: ${CMAKE_SYSTEM_NAME}")

CHECK_CXX_COMPILER_FLAG("-std=c++0x" CXX0X_SUPPORTED)
IF(CXX0X_SUPPORTED)
	MESSAGE(STATUS "C++0x seems supported, using std::shared_ptr")
	SET(HAS_STD_SHARED_PTR 1)
ELSE(CXX0X_SUPPORTED)
	MESSAGE(STATUS "C++0x seems not supported, will try using std::tr1::shared_ptr")
	SET(HAS_STD_SHARED_PTR 0)
ENDIF(CXX0X_SUPPORTED)

INCLUDE_DIRECTORIES(include)

IF("${CMAKE_SYSTEM_NAME}" MATCHES "FreeBSD")
        MESSAGE(STATUS "Building for FreeBSD...")
ENDIF("${CMAKE_SYSTEM_NAME}" MATCHES "FreeBSD")

IF("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
	MESSAGE(STATUS "Building for Linux...")
ENDIF("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")

IF("${CMAKE_SYSTEM_NAME}" MATCHES "SunOS")
	MESSAGE(STATUS "Building for SunOS...")
ENDIF("${CMAKE_SYSTEM_NAME}" MATCHES "SunOS")

IF("${CMAKE_COMPILER_IS_GNUCXX}" MATCHES "1")
	SET(CMAKE_CXX_WARN_FLAGS " -Wall -pedantic -Wno-long-long -Wno-inline -finline-functions -Werror -Wno-variadic-macros ")
	IF(HAS_STD_SHARED_PTR)
		SET(CMAKE_CXX_PARAMS "${CMAKE_CXX_PARAMS} -std=c++0x ")
	ELSE()
		SET(CMAKE_CXX_PARAMS "${CMAKE_CXX_PARAMS} -DUSE_TR1_SHARED_PTR ")
	ENDIF()

	IF("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
		SET(CMAKE_CXX_PARAMS "${CMAKE_CXX_PARAMS} -Dlinux ")
	ENDIF("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
	IF(ENABLE_OPTIMIZATION MATCHES "ON")
		MESSAGE(STATUS "Optimizaton is enabled")
		SET(CMAKE_CXX_FLAGS "${CXX_FLAGS} ${CMAKE_CXX_WARN_FLAGS} ${CMAKE_CXX_PARAMS} -O3 -fomit-frame-pointer -funroll-loops ")
	ELSE(ENABLE_OPTIMIZATION MATCHES "OFF")
		SET(CMAKE_CXX_FLAGS "${CXX_FLAGS} ${CMAKE_CXX_WARN_FLAGS} ${CMAKE_CXX_PARAMS} ")
	ENDIF(ENABLE_OPTIMIZATION MATCHES "ON")

	IF(DEBUG_MODE MATCHES "ON")
		MESSAGE(STATUS "Debug is enabled")
		SET(CMAKE_CXX_FLAGS "${CXX_FLAGS} ${CMAKE_CXX_WARN_FLAGS} ${CMAKE_CXX_PARAMS} -g -D_DEBUG ")
	ENDIF(DEBUG_MODE MATCHES "ON")
ENDIF("${CMAKE_COMPILER_IS_GNUCXX}" MATCHES "1")

# ################################################################################
# Sources of main library
#
SET(SOLVER_LIB_SRCS src/engine/cell.cpp
                    src/engine/desk.cpp)

ADD_LIBRARY(libsolver-cpp STATIC ${SOLVER_LIB_SRCS})
SET_TARGET_PROPERTIES(libsolver-cpp PROPERTIES OUTPUT_NAME solver)
SET_TARGET_PROPERTIES(libsolver-cpp PROPERTIES LINKER_LANGUAGE CXX)
SET_TARGET_PROPERTIES(libsolver-cpp PROPERTIES VERSION ${SOLVER_VERSION})

ADD_EXECUTABLE(console src/test/console.cpp
                       src/test/command.cpp)
TARGET_LINK_LIBRARIES(console libsolver-cpp)