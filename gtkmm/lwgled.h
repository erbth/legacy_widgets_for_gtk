// See https://developer.gnome.org/gtkmm-tutorial/stable/sec-custom-widgets.html.en

#ifndef _LWGLED_H
#define _LWGLED_H

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

#endif /* _LWGLED_H */
