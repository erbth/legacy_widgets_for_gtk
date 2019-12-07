/* legacy-widgets-for-gtk: LEDs for GTK
 *  Copyright (C) 2019  Thomas Erbesdobler <t.erbesdobler@gmx.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>. */

// See also: https://developer.gnome.org/gtkmm-tutorial/stable/sec-custom-widgets.html.en

#ifndef _LWG_LED_CPP_H
#define _LWG_LED_CPP_H

#include <gtkmm/widget.h>

class lwgLED : public Gtk::Widget
{
public:
	lwgLED (int color = color::green, int diameter_mm = 3);
	virtual ~lwgLED ();

	void set_intensity (double i);

	class color {
	public:
		static const int red = 0;
		static const int green = 1;
		static const int yellow = 2;
		static const int blue = 3;
	};

protected:
	// Overrides
	Gtk::SizeRequestMode get_request_mode_vfunc () const override;
	void get_preferred_width_vfunc (int &minimum_width, int &natural_width) const override;
	void get_preferred_height_for_width_vfunc (int width, int &minimum_height, int &natural_height) const override;
	void get_preferred_height_vfunc (int &minimum_height, int &natural_height) const override;
	void get_preferred_width_for_height_vfunc (int height, int &minimum_width, int &natural_width) const override;

	void on_size_allocate (Gtk::Allocation &allocation) override;
	void on_map () override;
	void on_unmap () override;
	void on_realize () override;
	void on_unrealize () override;
	bool on_draw (const Cairo::RefPtr<Cairo::Context> &cr) override;

	int m_color;
	const double m_spacing_mm = 1;
	double m_radius_mm;
	double m_led_cx, m_led_cy;

	double mmpu_x = 96 / 25.4;
	double mmpu_y = 96 / 25.4;

	double m_intensity = 0.;

	Glib::RefPtr<Gdk::Window> m_refGdkWindow;
};

class lwgRGBLED : public lwgLED
{
public:
	lwgRGBLED (int diameter_mm = 3);

	void set_red (double red);
	void set_green (double green);
	void set_blue (double blue);

protected:
	bool on_draw (const Cairo::RefPtr<Cairo::Context> &cr) override;

	double m_red = 0., m_green = 0., m_blue = 0.;
};

#endif /* _LWG_LED_CPP_H */
