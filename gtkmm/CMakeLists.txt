cmake_minimum_required(VERSION 3.1)

project (LWG C CXX)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package (gtkmm-3.0 REQUIRED)

add_library(legacy_widgets_for_gtk SHARED lwg_led_cpp.cpp)

target_link_libraries (legacy_widgets_for_gtk ${GTKMM_3_0_LIBRARIES})
target_include_directories (legacy_widgets_for_gtk PRIVATE ${GTKMM_3_0_INCLUDE_DIRS})

add_executable (LWGExample main.cpp LWGExampleWindow.cpp)

target_link_libraries (LWGExample ${GTKMM_3_0_LIBRARIES} legacy_widgets_for_gtk)
target_include_directories (LWGExample PRIVATE ${GTKMM_3_0_INCLUDE_DIRS})

install(TARGETS legacy_widgets_for_gtk DESTINATION lib)
install(FILES lwg_led_cpp.h DESTINATION include)
