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
	Gtk::Box m_HBox;
	lwgLED m_led;
};

#endif /* _LWG_EXAMPLE_WINDOW_H */
