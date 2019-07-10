// See https://developer.gnome.org/gtkmm-tutorial/stable/sec-custom-widgets.html.en

#include <cmath>
#include <cstring>
#include <gdkmm/general.h>
#include <iostream>
#include "lwgled.h"

using namespace std;

lwgLED::lwgLED (int color, int diameter) :
	Glib::ObjectBase("lwgLED"),
	Gtk::Widget ()
{
	set_has_window (true);
	set_name ("lwg-led");

	m_radius_mm = diameter / 2.;

	if (
			color != lwgLED::color::red &&
			color != lwgLED::color::green &&
			color != lwgLED::color::yellow &&
			color != lwgLED::color::blue
	   )
	{
		m_color = lwgLED::color::green;
	}
	else
		m_color = color;
}

lwgLED::~lwgLED ()
{
}

Gtk::SizeRequestMode lwgLED::get_request_mode_vfunc () const
{
	return Gtk::Widget::get_request_mode_vfunc ();
}


void lwgLED::set_intensity (double i)
{
	i = MIN (MAX (i, 0.), 1.);
	m_intensity = i;

	const auto a = get_allocation ();

	Gdk::Rectangle r (
			floorf (m_led_cx - m_radius_mm * mmpu_x),
			floorf (m_led_cy - m_radius_mm * mmpu_y),
			ceilf (m_radius_mm * 2 * mmpu_x),
			ceilf (m_radius_mm * 2 * mmpu_y));

	if (m_refGdkWindow)
		m_refGdkWindow->invalidate_rect (r, false);
}


void lwgLED::get_preferred_width_vfunc (int &minimum_width, int &natural_width) const
{
	int led_width = ceilf ((m_spacing_mm + m_radius_mm) * 2 * mmpu_x);

	minimum_width = led_width;
	natural_width = led_width;
}

void lwgLED::get_preferred_height_for_width_vfunc (int width, int &minimum_height, int &natural_height) const
{
	get_preferred_height (minimum_height, natural_height);
}

void lwgLED::get_preferred_height_vfunc (int &minimum_height, int &natural_height) const
{
	int led_height = ceilf ((m_spacing_mm + m_radius_mm) * 2 * mmpu_y);

	minimum_height = led_height;
	natural_height = led_height;
}

void lwgLED::get_preferred_width_for_height_vfunc (int height, int &minimum_width, int &natural_width) const
{
	get_preferred_width (minimum_width, natural_width);
}

void lwgLED::on_size_allocate (Gtk::Allocation &allocation)
{
	set_allocation (allocation);

	m_led_cx = ceilf ((m_spacing_mm + m_radius_mm) * mmpu_x);
	m_led_cy = allocation.get_height() / 2;

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

	double v = 0.2 + 0.8 * m_intensity;

	if (m_color == color::red)
		cr->set_source_rgba (v, 0, 0, 1);
	else if (m_color == color::yellow)
		cr->set_source_rgba (v, v, 0, 1);
	else if (m_color == color::blue)
		cr->set_source_rgba (0, 0, v, 1);
	else
		cr->set_source_rgba (0, v, 0, 1);

	cr->arc (m_led_cx, m_led_cy, m_radius_mm * mmpu_x, 0, 2 * M_PI);

	cr->fill ();

	return true;
}


/* lwgRGBLED (dirty) */
lwgRGBLED::lwgRGBLED (int diameter) :
	lwgLED (diameter = diameter)
{
	m_intensity = 1.;
}

void lwgRGBLED::set_red (double red)
{
	m_red = MIN (MAX (red, 0.), 1.);

	Gdk::Rectangle r (
			floorf (m_led_cx - m_radius_mm * mmpu_x),
			floorf (m_led_cy - m_radius_mm * mmpu_y),
			ceilf (m_radius_mm * 2 * mmpu_x),
			ceilf (m_radius_mm * 2 * mmpu_y));

	if (m_refGdkWindow)
		m_refGdkWindow->invalidate_rect (r, false);
}

void lwgRGBLED::set_green (double green)
{
	m_green = MIN (MAX (green, 0.), 1.);

	Gdk::Rectangle r (
			floorf (m_led_cx - m_radius_mm * mmpu_x),
			floorf (m_led_cy - m_radius_mm * mmpu_y),
			ceilf (m_radius_mm * 2 * mmpu_x),
			ceilf (m_radius_mm * 2 * mmpu_y));

	if (m_refGdkWindow)
		m_refGdkWindow->invalidate_rect (r, false);
}

void lwgRGBLED::set_blue (double blue)
{
	m_blue = MIN (MAX (blue, 0.), 1.);

	Gdk::Rectangle r (
			floorf (m_led_cx - m_radius_mm * mmpu_x),
			floorf (m_led_cy - m_radius_mm * mmpu_y),
			ceilf (m_radius_mm * 2 * mmpu_x),
			ceilf (m_radius_mm * 2 * mmpu_y));

	if (m_refGdkWindow)
		m_refGdkWindow->invalidate_rect (r, false);
}


bool lwgRGBLED::on_draw (const Cairo::RefPtr<Cairo::Context> &cr)
{
	const auto allocation = get_allocation ();
	auto refStyleContext = get_style_context ();

	refStyleContext->render_background (
			cr,
			allocation.get_x(), allocation.get_y(),
			allocation.get_width(), allocation.get_height());

	cr->set_source_rgba (
			m_red * m_intensity,
			m_green * m_intensity,
			m_blue * m_intensity,
			1);

	cr->arc (m_led_cx, m_led_cy, m_radius_mm * mmpu_x, 0, 2 * M_PI);

	cr->fill ();

	return true;
}
