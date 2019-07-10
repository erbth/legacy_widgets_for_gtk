// See https://developer.gnome.org/gtkmm-tutorial/stable/sec-custom-widgets.html.en

#ifndef _LWG_EXAMPLE_WINDOW_H
#define _LWG_EXAMPLE_WINDOW_H

#include <gtkmm.h>
#include "lwgled.h"

class LWGExampleWindow : public Gtk::Window
{
public:
	LWGExampleWindow ();
	virtual ~LWGExampleWindow ();

protected:
	// Child widgets
	Gtk::Box m_VBox;

	Gtk::Box m_HBox1;
	Gtk::Frame m_frame1;
	lwgLED m_led1;
	Gtk::ToggleButton m_onoff1;

	Gtk::Box m_HBox2;
	Gtk::Frame m_frame2;
	lwgLED m_led2;
	Gtk::ToggleButton m_onoff2;

	Gtk::Box m_HBox3;
	Gtk::Frame m_frame3;
	lwgLED m_led3;
	Gtk::ToggleButton m_onoff3;

	Gtk::Box m_HBox4;
	Gtk::Frame m_frame4;
	lwgLED m_led4;
	Gtk::ToggleButton m_onoff4;

	// Signal handlers
	void on_onoff1_toggled ();
	void on_onoff2_toggled ();
	void on_onoff3_toggled ();
	void on_onoff4_toggled ();
};

#endif /* _LWG_EXAMPLE_WINDOW_H */
