cmake_minimum_required(VERSION 3.1)

project(legacy_widgets_for_gtk C CXX)

# A version number
set(LWG_VERSION_MAJOR 1)
set(LWG_VERSION_MINOR 0)
set(LWG_VERSION_PATCH 0)

# Set CFLAGS and CXXFLAGS
set (CMAKE_C_FLAGS "-std=c11 -O3")
set (CMAKE_C_FLAGS_DEBUG "-gdwarf-2 -DDEBUG")

set (CMAKE_CXX_FLAGS "-std=c++17 -O3")
set (CMAKE_CXX_FLAGS_DEBUG "-gdwarf-2 -DDEBUG")

# Find required packages
find_package (PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

include_directories(include)

add_subdirectory(src)
