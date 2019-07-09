// See https://developer.gnome.org/gtkmm-tutorial/stable/sec-custom-widgets.html.en

#include <cstring>
#include <gdkmm/general.h>
#include <iostream>
#include "lwgled.h"

using namespace std;

lwgLED::lwgLED (int diameter) :
	Glib::ObjectBase("lwgLED"),
	Gtk::Widget ()
{
	set_has_window (true);
	set_name ("lwg-led");

	m_diameter = diameter;

	min_width = min_height = (int) ((m_diameter) * 96 / 25.4);

	cout << "min_height: " << min_height << endl;
}

lwgLED::~lwgLED ()
{
}

Gtk::SizeRequestMode lwgLED::get_request_mode_vfunc () const
{
	return Gtk::Widget::get_request_mode_vfunc ();
}


void lwgLED::set_brightness (double b)
{
	m_brightness = b;

	const auto a = get_allocation ();
	Gdk::Rectangle r (0, 0, a.get_width(), a.get_height());

	if (m_refGdkWindow)
		m_refGdkWindow->invalidate_rect (r, false);
}


void lwgLED::get_preferred_width_vfunc (int &minimum_width, int &natural_width) const
{
	minimum_width = natural_width = min_width;
}

void lwgLED::get_preferred_height_for_width_vfunc (int width, int &minimum_height, int &natural_height) const
{
	minimum_height = min_height;
	natural_height = width;
}

void lwgLED::get_preferred_height_vfunc (int &minimum_height, int &natural_height) const
{
	minimum_height = natural_height = min_height;
}

void lwgLED::get_preferred_width_for_height_vfunc (int height, int &minimum_width, int &natural_width) const
{
	minimum_width = min_width;
	natural_width = height;
}

void lwgLED::on_size_allocate (Gtk::Allocation &allocation)
{
	set_allocation (allocation);

	if (m_refGdkWindow)
	{
		m_refGdkWindow->move_resize (
				allocation.get_x(),
				allocation.get_y(),
				allocation.get_width(),
				allocation.get_height()
				);
	}
}

void lwgLED::on_map ()
{
	Gtk::Widget::on_map();
}

void lwgLED::on_unmap ()
{
	Gtk::Widget::on_unmap();
}

void lwgLED::on_realize ()
{
	set_realized ();

	if (!m_refGdkWindow)
	{
		GdkWindowAttr attributes;
		memset (&attributes, 0, sizeof (attributes));

		const auto allocation = get_allocation ();

		attributes.x = allocation.get_x ();
		attributes.y = allocation.get_y ();
		attributes.width = allocation.get_width ();
		attributes.height = allocation.get_height ();

		attributes.event_mask = get_events () | Gdk::EXPOSURE_MASK;
		attributes.window_type = GDK_WINDOW_CHILD;
		attributes.wclass = GDK_INPUT_OUTPUT;

		m_refGdkWindow = Gdk::Window::create (
				get_parent_window (),
				&attributes,
				GDK_WA_X | GDK_WA_Y);

		set_window (m_refGdkWindow);

		m_refGdkWindow->set_user_data (gobj ());
	}
}

void lwgLED::on_unrealize ()
{
	m_refGdkWindow.reset();

	Gtk::Widget::on_unrealize ();
}

bool lwgLED::on_draw (const Cairo::RefPtr<Cairo::Context> &cr)
{
	const auto allocation = get_allocation ();
	auto refStyleContext = get_style_context ();

	refStyleContext->render_background (
			cr,
			allocation.get_x(), allocation.get_y(),
			allocation.get_width(), allocation.get_height());

	double x = allocation.get_width() / 2.;
	double y = allocation.get_height() / 2.;

	double r1 = m_diameter * 96 / 25.4 / 2;
	double r2 = r1 + 96 / 25.4;

	cr->set_source_rgba (1, 0, 0, 1);
	cr->arc (x, y, 2.5, 0, 360);
	cr->fill ();

	cr->set_source_rgba (0, 0, 0, 1);
	cr->arc (x, y, r2 + 0.5, 0, 360);
	cr->stroke ();

	return true;
}
