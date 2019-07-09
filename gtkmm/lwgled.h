// See https://developer.gnome.org/gtkmm-tutorial/stable/sec-custom-widgets.html.en

#ifndef _LWGLED_H
#define _LWGLED_H

#include <gtkmm/widget.h>

class lwgLED : public Gtk::Widget
{
public:
	lwgLED (int diameter = 5);
	virtual ~lwgLED ();

	void set_brightness (double b);

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

	int m_diameter;
	int min_width, min_height;

	double m_brightness = 0.;
	Gdk::RGBA m_color;

	Glib::RefPtr<Gdk::Window> m_refGdkWindow;
};

#endif /* _LWGLED_H */
