// See https://developer.gnome.org/gtkmm-tutorial/stable/sec-custom-widgets.html.en

#include <gtkmm/application.h>
#include "LWGExampleWindow.h"

int main (int argc, char **argv)
{
	auto app = Gtk::Application::create (argc, argv, "gmx.erbesdobler.t.lwgexample");

	LWGExampleWindow w;

	return app->run (w);
}
