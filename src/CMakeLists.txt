cmake_minimum_required(VERSION 3.1)

add_library (legacy_widgets_for_gtk SHARED
	lwgled.c
	lwgrgbled.c)

target_link_libraries(legacy_widgets_for_gtk ${GTK3_LIBRARIES})
target_include_directories(legacy_widgets_for_gtk PRIVATE ${GTK3_INCLUDE_DIRS})

set_target_properties (legacy_widgets_for_gtk PROPERTIES VERSION "${LWG_VERSION_MAJOR}.${LWG_VERSION_MINOR}.${LWG_VERSION_PATCH}" SOVERSION "${LWG_VERSION_MAJOR}.${LWG_VERSION_MINOR}")
set_target_properties (legacy_widgets_for_gtk PROPERTIES PUBLIC_HEADER "../include/lwgled.h;../include/lwgrgbled.h;../include/legacy_widgets_for_gtk.h")

# Create a pkg-config file
configure_file(legacy_widgets_for_gtk.pc.in "legacy_widgets_for_gtk-${LWG_VERSION_MAJOR}.${LWG_VERSION_MINOR}.pc")

install (TARGETS legacy_widgets_for_gtk LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)
install (FILES "${CMAKE_BINARY_DIR}/src/legacy_widgets_for_gtk-${LWG_VERSION_MAJOR}.${LWG_VERSION_MINOR}.pc" DESTINATION lib/pkgconfig)

# Optionally create and install gir/typlib files
if (GirScanner_FOUND)
	add_gir(legacy_widgets_for_gtk_gir legacy_widgets_for_gtk Lwg 1.0
		INCLUDES Gtk-3.0
		IDENTIFIER_PREFIX Lwg
		SYMBOL_PREFIX lwg)

	install_gir(legacy_widgets_for_gtk_gir DESTINATION share)

	if (GirCompiler_FOUND)
		add_typelib(legacy_widgets_for_gtk_typelib legacy_widgets_for_gtk_gir)
		install_typelib(legacy_widgets_for_gtk_typelib DESTINATION lib)
	endif()
endif()

# A demo application
add_executable(widget_demo widget_demo.c)
target_link_libraries(widget_demo ${GTK3_LIBRARIES} legacy_widgets_for_gtk)
target_include_directories(widget_demo PRIVATE ${GTK3_INCLUDE_DIRS})
