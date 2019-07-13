cmake_minimum_required(VERSION 3.1)

project (legacy-widgets-for-gtk C CXX)

set(LWG_VERSION_MAJOR 1)
set(LWG_VERSION_MINOR 0)
set(LWG_VERSION_PATCH 0)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package (gtkmm-3.0 REQUIRED)

add_library(legacy_widgets_for_gtk SHARED lwg_led_cpp.cpp)
set_target_properties(legacy_widgets_for_gtk PROPERTIES VERSION "${LWG_VERSION_MAJOR}.${LWG_VERSION_MINOR}.${LWG_VERSION_PATCH}" SOVERSION ${LWG_VERSION_MAJOR})

target_link_libraries (legacy_widgets_for_gtk ${GTKMM_3_0_LIBRARIES})
target_include_directories (legacy_widgets_for_gtk PRIVATE ${GTKMM_3_0_INCLUDE_DIRS})

add_executable (LWGExample main.cpp LWGExampleWindow.cpp)

target_link_libraries (LWGExample ${GTKMM_3_0_LIBRARIES} legacy_widgets_for_gtk)
target_include_directories (LWGExample PRIVATE ${GTKMM_3_0_INCLUDE_DIRS})

install(TARGETS legacy_widgets_for_gtk DESTINATION lib)
install(FILES lwg_led_cpp.h DESTINATION include)
install(FILES legacy-widgets-for-gtk.h DESTINATION include)

# Packaging
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${LWG_VERSION_MAJOR}.${LWG_VERSION_MINOR}.${LWG_VERSION_PATCH}") 
set(CPACK_SOURCE_IGNORE_FILES "/build/;.*\.swp;mysession.vim;${CPACK_SOURCE_IGNORE_FILES}")
include(CPack)
