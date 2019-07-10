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
	m_onoff4 ("LED 4"),
	m_label5 ("LED 5"),
	m_5_r (Gtk::ORIENTATION_VERTICAL),
	m_5_g (Gtk::ORIENTATION_VERTICAL),
	m_5_b (Gtk::ORIENTATION_VERTICAL) 
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

	// LED 5
	m_5_r.set_range (0,1);
	m_5_r.set_value (0);
	m_5_r.set_digits (2);
	m_5_r.set_inverted (true);

	m_5_g.set_range (0,1);
	m_5_g.set_value (0);
	m_5_g.set_digits (2);
	m_5_g.set_inverted (true);

	m_5_b.set_range (0,1);
	m_5_b.set_value (0);
	m_5_b.set_digits (2);
	m_5_b.set_inverted (true);

	m_VBox.pack_start (m_HBox5);
	m_HBox5.pack_start (m_frame5, Gtk::PACK_SHRINK);
	m_frame5.add (m_led5);
	m_HBox5.pack_start (m_label5, Gtk::PACK_SHRINK);
	m_HBox5.pack_start (m_5_r, Gtk::PACK_SHRINK, 10);
	m_HBox5.pack_start (m_5_g, Gtk::PACK_SHRINK, 10);
	m_HBox5.pack_start (m_5_b, Gtk::PACK_SHRINK, 10);

	// Connect signal handlers
	m_onoff1.signal_toggled().connect (
			sigc::mem_fun (this, &LWGExampleWindow::on_onoff1_toggled));

	m_onoff2.signal_toggled().connect (
			sigc::mem_fun (this, &LWGExampleWindow::on_onoff2_toggled));

	m_onoff3.signal_toggled().connect (
			sigc::mem_fun (this, &LWGExampleWindow::on_onoff3_toggled));

	m_onoff4.signal_toggled().connect (
			sigc::mem_fun (this, &LWGExampleWindow::on_onoff4_toggled));


	m_5_r.signal_value_changed().connect (
			sigc::mem_fun (this, &LWGExampleWindow::on_5_r_changed));

	m_5_g.signal_value_changed().connect (
			sigc::mem_fun (this, &LWGExampleWindow::on_5_g_changed));

	m_5_b.signal_value_changed().connect (
			sigc::mem_fun (this, &LWGExampleWindow::on_5_b_changed));

	show_all ();
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


void LWGExampleWindow::on_5_r_changed ()
{
	m_led5.set_red (m_5_r.get_value());
}

void LWGExampleWindow::on_5_g_changed ()
{
	m_led5.set_green (m_5_g.get_value());
}

void LWGExampleWindow::on_5_b_changed ()
{
	m_led5.set_blue (m_5_b.get_value());
}
