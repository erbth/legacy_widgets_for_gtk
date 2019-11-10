cmake_minimum_required(VERSION 3.1)

add_library (legacy_widgets_for_gtk_c SHARED
	lwgled.c
	lwgrgbled.c)

target_link_libraries(legacy_widgets_for_gtk_c ${GTK3_LIBRARIES})
target_include_directories(legacy_widgets_for_gtk_c PRIVATE ${GTK3_INCLUDE_DIRS})

set_target_properties (legacy_widgets_for_gtk_c PROPERTIES VERSION "${LWG_VERSION_MAJOR}.${LWG_VERSION_MINOR}.${LWG_VERSION_PATCH}" SOVERSION "${LWG_VERSION_MAJOR}.${LWG_VERSION_MINOR}")
set_target_properties (legacy_widgets_for_gtk_c PROPERTIES PUBLIC_HEADER "../include/lwgled.h")

install (TARGETS legacy_widgets_for_gtk_c LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)

# A demo application
add_executable(widget_demo widget_demo.c)
target_link_libraries(widget_demo ${GTK3_LIBRARIES} legacy_widgets_for_gtk_c)
target_include_directories(widget_demo PRIVATE ${GTK3_INCLUDE_DIRS})
