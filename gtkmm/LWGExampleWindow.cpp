// See https://developer.gnome.org/gtkmm-tutorial/stable/sec-custom-widgets.html.en

#include "LWGExampleWindow.h"

LWGExampleWindow::LWGExampleWindow () :
	m_VBox (Gtk::ORIENTATION_VERTICAL),
	m_HBox1 (Gtk::ORIENTATION_HORIZONTAL),
	m_led2 (lwgLED::color::red),
	m_led3 (lwgLED::color::yellow),
	m_led4 (lwgLED::color::blue),
	m_onoff1 ("LED 1"),
	m_onoff2 ("LED 2"),
	m_onoff3 ("LED 3"),
	m_onoff4 ("LED 4")
{
	set_title ("Legacy Widgets for GTK examples");
	set_border_width (2);
	set_default_size (400, 200);

	add (m_VBox);

	// LED 1
	m_VBox.pack_start (m_HBox1, Gtk::PACK_SHRINK);
	m_HBox1.pack_start (m_frame1, Gtk::PACK_SHRINK);
	m_frame1.add (m_led1);
	m_HBox1.pack_start (m_onoff1, Gtk::PACK_SHRINK);

	// LED 2
	m_VBox.pack_start (m_HBox2, Gtk::PACK_SHRINK);
	m_HBox2.pack_start (m_frame2, Gtk::PACK_SHRINK);
	m_frame2.add (m_led2);
	m_HBox2.pack_start (m_onoff2, Gtk::PACK_SHRINK);

	// LED 3
	m_VBox.pack_start (m_HBox3, Gtk::PACK_SHRINK);
	m_HBox3.pack_start (m_frame3, Gtk::PACK_SHRINK);
	m_frame3.add (m_led3);
	m_HBox3.pack_start (m_onoff3, Gtk::PACK_SHRINK);

	// LED 4
	m_VBox.pack_start (m_HBox4, Gtk::PACK_SHRINK);
	m_HBox4.pack_start (m_frame4, Gtk::PACK_SHRINK);
	m_frame4.add (m_led4);
	m_HBox4.pack_start (m_onoff4, Gtk::PACK_SHRINK);

	// Connect signal handlers
	m_onoff1.signal_toggled().connect (
			sigc::mem_fun (this, &LWGExampleWindow::on_onoff1_toggled));

	m_onoff2.signal_toggled().connect (
			sigc::mem_fun (this, &LWGExampleWindow::on_onoff2_toggled));

	m_onoff3.signal_toggled().connect (
			sigc::mem_fun (this, &LWGExampleWindow::on_onoff3_toggled));

	m_onoff4.signal_toggled().connect (
			sigc::mem_fun (this, &LWGExampleWindow::on_onoff4_toggled));

	show_all_children ();
}

LWGExampleWindow::~LWGExampleWindow ()
{
}


// Signal handlers
void LWGExampleWindow::on_onoff1_toggled ()
{
	m_led1.set_intensity (m_onoff1.get_active() ? 1. : 0.);
}

void LWGExampleWindow::on_onoff2_toggled ()
{
	m_led2.set_intensity (m_onoff2.get_active() ? 1. : 0.);
}

void LWGExampleWindow::on_onoff3_toggled ()
{
	m_led3.set_intensity (m_onoff3.get_active() ? 1. : 0.);
}

void LWGExampleWindow::on_onoff4_toggled ()
{
	m_led4.set_intensity (m_onoff4.get_active() ? 1. : 0.);
}
