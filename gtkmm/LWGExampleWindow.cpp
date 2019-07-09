// See https://developer.gnome.org/gtkmm-tutorial/stable/sec-custom-widgets.html.en

#include "LWGExampleWindow.h"

LWGExampleWindow::LWGExampleWindow () :
	m_HBox (Gtk::ORIENTATION_VERTICAL)
{
	set_title ("Legacy Widgets for GTK examples");
	set_border_width (6);
	set_default_size (400, 200);

	add (m_HBox);
	m_HBox.pack_start (m_led, Gtk::PACK_SHRINK);

	show_all_children ();
}

LWGExampleWindow::~LWGExampleWindow ()
{
}
