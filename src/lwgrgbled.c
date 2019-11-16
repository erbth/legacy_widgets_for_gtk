#include <string.h>
#include <math.h>
#include "lwgrgbled.h"
#include "lwgrgbledprivate.h"

/**
 * SECTION: lwgrgbled
 * @Short_description: A RGB LED widget for GTK+
 * @Title: LwgRGBLed
 *
 * A LwgRGBLed is a display widget which looks like a RGB LED.
 */

#define LED_SPACING_MM		1
#define LED_RADIUS_MM		1.5

struct _LwgRGBLedPrivate
{
	gint color;
	gfloat red, green, blue;

	GdkRectangle led_rect;
	GdkRectangle bin_child_rect;

	gdouble led_cx, led_cy;
};

enum
{
	PROP_0,
	NUM_PROPERTIES
};

static void			lwg_rgb_led_set_property (GObject*, guint, const GValue*, GParamSpec*);
static void			lwg_rgb_led_get_property (GObject*, guint, GValue*, GParamSpec*);

static void			lwg_rgb_led_get_mmpu	(LwgRGBLed* led, gdouble* mmpu_x, gdouble* mmpu_y);

static void			lwg_rgb_led_get_preferred_width (GtkWidget*, gint*, gint*);
static void			lwg_rgb_led_get_preferred_height (GtkWidget*, gint*, gint*);
static void			lwg_rgb_led_get_preferred_width_for_height (GtkWidget*, gint, gint*, gint*);
static void			lwg_rgb_led_get_preferred_height_for_width (GtkWidget*, gint, gint*, gint*);
static void			lwg_rgb_led_size_allocate (GtkWidget* widget, GtkAllocation* allocation);

static void			lwg_rgb_led_realize		(GtkWidget*);
static gboolean		lwg_rgb_led_draw		(GtkWidget*, cairo_t* cr);

static void			lwg_rgb_led_update		(LwgRGBLed* led);

static GParamSpec *rgb_led_props[NUM_PROPERTIES] = { NULL, };

G_DEFINE_TYPE_WITH_PRIVATE (LwgRGBLed, lwg_rgb_led, GTK_TYPE_BIN)

static void lwg_rgb_led_class_init (LwgRGBLedClass *class)
{
	GObjectClass*		object_class = G_OBJECT_CLASS (class);
	GtkWidgetClass* 	widget_class = GTK_WIDGET_CLASS (class);

	object_class->set_property = lwg_rgb_led_set_property;
	object_class->get_property = lwg_rgb_led_get_property;

	widget_class->get_preferred_width				= lwg_rgb_led_get_preferred_width;
	widget_class->get_preferred_height				= lwg_rgb_led_get_preferred_height;
	widget_class->get_preferred_width_for_height	= lwg_rgb_led_get_preferred_width_for_height;
	widget_class->get_preferred_height_for_width	= lwg_rgb_led_get_preferred_height_for_width;
	widget_class->size_allocate						= lwg_rgb_led_size_allocate;

	widget_class->realize							= lwg_rgb_led_realize;
	widget_class->draw								= lwg_rgb_led_draw;

	/* led_props[PROP_COLOR] =
		g_param_spec_uint("color",
				"Color",
				"The LED's color",
				0, lwg_rgb_led_LAST_COLOR,
				0,
				G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE); */

	// g_object_class_install_properties(object_class, NUM_PROPERTIES, led_props);
}

static void lwg_rgb_led_init (LwgRGBLed *led)
{
	GtkWidget* widget = GTK_WIDGET (led);

	led->priv = G_TYPE_INSTANCE_GET_PRIVATE (led, LWG_TYPE_RGB_LED, LwgRGBLedPrivate);
	led->priv->red = led->priv->green = led->priv->blue = 0.0f;

	gtk_widget_set_has_window (widget, TRUE);
}

static void lwg_rgb_led_set_property (
		GObject* object,
		guint property_id,
		const GValue* value,
		GParamSpec* pspec)
{
	LwgRGBLed* this = LWG_RGB_LED (object);

	switch (property_id)
	{
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

static void lwg_rgb_led_get_property (
		GObject* object,
		guint property_id,
		GValue* value,
		GParamSpec* pspec)
{
	LwgRGBLed* this = LWG_RGB_LED (object);

	switch (property_id)
	{
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

static void lwg_rgb_led_get_mmpu (LwgRGBLed* led, gdouble* mmpu_x, gdouble* mmpu_y)
{
	*mmpu_x = *mmpu_y = 96.0 / 25.4;
}

static void lwg_rgb_led_get_preferred_width (GtkWidget* w, gint* min, gint* natural)
{
	gdouble mmpu_x, mmpu_y;
	LwgRGBLed* led;
	GtkWidget* child;
	gint child_min = 0, child_natural = 0;

	led = LWG_RGB_LED (w);
	lwg_rgb_led_get_mmpu (led, &mmpu_x, &mmpu_y);

	child = gtk_bin_get_child (GTK_BIN (led));

	if (child)
		gtk_widget_get_preferred_width (child, &child_min, &child_natural);

	gint led_width = ceilf ((LED_SPACING_MM + LED_RADIUS_MM) * 2 * mmpu_x);
	*min = led_width + child_min;
	*natural = led_width + child_natural;
}

static void lwg_rgb_led_get_preferred_height (GtkWidget* w, gint* pmin, gint* pnatural)
{
	gdouble mmpu_x, mmpu_y;
	LwgRGBLed* led;
	GtkWidget* child;
	gint min, natural;
	gint child_min = 0, child_natural = 0;

	led = LWG_RGB_LED (w);
	lwg_rgb_led_get_mmpu (led, &mmpu_x, &mmpu_y);

	child = gtk_bin_get_child (GTK_BIN (led));

	if (child)
		gtk_widget_get_preferred_height (child, &child_min, &child_natural);

	gint led_width = ceilf ((LED_SPACING_MM + LED_RADIUS_MM) * 2 * mmpu_y);
	min = led_width;
	natural = led_width;

	min = child_min > min ? child_min : min;
	natural = child_natural > natural ? child_natural : natural;

	*pmin = min;
	*pnatural = natural;
}

static void lwg_rgb_led_get_preferred_width_for_height (
		GtkWidget* w,
		gint height,
		gint* min,
		gint* natural)
{
	gdouble mmpu_x, mmpu_y;
	LwgRGBLed* led;
	GtkWidget* child;
	gint child_min = 0, child_natural = 0;

	led = LWG_RGB_LED (w);
	lwg_rgb_led_get_mmpu (led, &mmpu_x, &mmpu_y);

	child = gtk_bin_get_child (GTK_BIN (led));

	if (child)
	{
		gtk_widget_get_preferred_width_for_height (
				child, height, &child_min, &child_natural);
	}

	gint led_width = ceilf ((LED_SPACING_MM + LED_RADIUS_MM) * 2 * mmpu_x);
	*min = led_width + child_min;
	*natural = led_width + child_natural;
}

static void lwg_rgb_led_get_preferred_height_for_width (
		GtkWidget* w,
		gint width,
		gint* pmin,
		gint* pnatural)
{
	gdouble mmpu_x, mmpu_y;
	LwgRGBLed* led;
	GtkWidget* child;
	gint min, natural;
	gint child_min = 0, child_natural = 0;

	led = LWG_RGB_LED (w);
	lwg_rgb_led_get_mmpu (led, &mmpu_x, &mmpu_y);

	child = gtk_bin_get_child (GTK_BIN (led));

	if (child)
	{
		gtk_widget_get_preferred_height_for_width (
				child, width, &child_min, &child_natural);
	}

	gint led_width = ceilf ((LED_SPACING_MM + LED_RADIUS_MM) * 2 * mmpu_y);
	min = led_width;
	natural = led_width;

	min = child_min > min ? child_min : min;
	natural = child_natural > natural ? child_natural : natural;

	*pmin = min;
	*pnatural = natural;
}

static void lwg_rgb_led_size_allocate (
		GtkWidget* widget,
		GtkAllocation* allocation)
{
	GdkWindow* window;
	GtkWidget* child;
	LwgRGBLed* led;
	gdouble mmpu_x, mmpu_y;

	led = LWG_RGB_LED (widget);
	lwg_rgb_led_get_mmpu (led, &mmpu_x, &mmpu_y);

	/* Update internal private size information */
	GdkRectangle *led_rect = &led->priv->led_rect;
	led_rect->x = allocation->x;
	led_rect->y = allocation->y;
	led_rect->width = ceilf ((LED_SPACING_MM + LED_RADIUS_MM) * 2 * mmpu_x);
	led_rect->height = allocation->height;

	led->priv->led_cx = ceilf ((LED_SPACING_MM + LED_RADIUS_MM) * mmpu_x);
	led->priv->led_cy = allocation->height / 2;

	GdkRectangle *child_rect = &led->priv->bin_child_rect;
	child_rect->x = allocation->x + led_rect->width;
	child_rect->y = allocation->y;
	child_rect->width = allocation->width - led_rect->width;
	child_rect->height = allocation->height;

	gtk_widget_set_allocation (widget, allocation);

	window = gtk_widget_get_window (widget);
	if (window)
		gdk_window_move_resize (
				window,
				allocation->x, allocation->y,
				allocation->width, allocation->height);

	child = gtk_bin_get_child (GTK_BIN (widget));
	if (child && gtk_widget_get_visible (child))
	{
		GtkAllocation child_allocation;
		gdouble mmpu_x, mmpu_y;

		lwg_rgb_led_get_mmpu (led, &mmpu_x, &mmpu_y);

		child_allocation.x = child_rect->x;
		child_allocation.y = child_rect->y;
		child_allocation.width = child_rect->width;
		child_allocation.height = child_rect->height;

		gtk_widget_size_allocate (child, &child_allocation);
	}
}

static void lwg_rgb_led_realize (GtkWidget* w)
{
	LwgRGBLed* led;
	GtkAllocation allocation;
	GdkWindow* window;
	GdkWindowAttr attributes;

	led = LWG_RGB_LED (w);

	gtk_widget_set_realized (w, TRUE);
	gtk_widget_get_allocation (w, &allocation);

	memset (&attributes, 0, sizeof (attributes));

	attributes.x = allocation.x;
	attributes.y = allocation.y;
	attributes.width = allocation.width;
	attributes.height = allocation.height;

	attributes.event_mask =
		gtk_widget_get_events (w) |
		GDK_EXPOSURE_MASK;

	attributes.window_type = GDK_WINDOW_CHILD;
	attributes.wclass = GDK_INPUT_OUTPUT;

	window = gdk_window_new (
			gtk_widget_get_parent_window (w),
			&attributes,
			GDK_WA_X | GDK_WA_Y);

	gtk_widget_set_window (w, window);
	gtk_widget_register_window (w, window);

	/* Realize child if you have one */
	GtkWidget* child = gtk_bin_get_child (GTK_BIN (led));
	if (child)
	{
		gtk_widget_realize (child);
	}
}

static gboolean lwg_rgb_led_draw (GtkWidget* w, cairo_t *cr)
{
	gdouble mmpu_x, mmpu_y;
	LwgRGBLed* led;
	GtkWidget* child = NULL;

	led = LWG_RGB_LED (w);
	lwg_rgb_led_get_mmpu (led, &mmpu_x, &mmpu_y);

	/* Draw the LED */
	cairo_save (cr);

	cairo_set_source_rgb (cr, led->priv->red, led->priv->green, led->priv->blue);
	cairo_arc (cr,
			led->priv->led_cx, led->priv->led_cy,
			LED_RADIUS_MM * mmpu_x,
			0, 2 * G_PI);

	cairo_fill (cr);

	cairo_restore (cr);

	/* Draw the child */
	child = gtk_bin_get_child (GTK_BIN (w));

	if (child)
	{
		/* Draw in millimeters */
		cairo_translate (cr, 5 * mmpu_x, 0);

		gtk_widget_draw (child, cr);
	}

	return FALSE;
}

static void lwg_rgb_led_update (LwgRGBLed* led)
{
	gdouble mmpu_x, mmpu_y;

	lwg_rgb_led_get_mmpu (led, &mmpu_x, &mmpu_y);

	gtk_widget_queue_draw_area (
			GTK_WIDGET (led),
			floorf (led->priv->led_cx - LED_RADIUS_MM * mmpu_x),
			floorf (led->priv->led_cy - LED_RADIUS_MM * mmpu_y),
			ceilf (LED_RADIUS_MM * 2 * mmpu_x) + 1,
			ceilf (LED_RADIUS_MM * 2 * mmpu_y) + 1);
}

GtkWidget* lwg_rgb_led_new ()
{
	return g_object_new (LWG_TYPE_RGB_LED, NULL);
}

GtkWidget* lwg_rgb_led_new_with_label (const gchar* label)
{
	GtkWidget* led = g_object_new (LWG_TYPE_RGB_LED, NULL);

	GtkWidget* label_widget = gtk_label_new (label);
	gtk_label_set_xalign (GTK_LABEL (label_widget), 0);

	gtk_container_add (GTK_CONTAINER(led), label_widget);

	return led;
}

void lwg_rgb_led_set_red (LwgRGBLed* led, const gfloat red)
{
	g_return_if_fail (LWG_IS_RGB_LED (led));

	if (red < 0.0f || red > 1.0f)
	{
		g_print ("LwgRGBLed::set_red: intensity not in valid range (must be "
				">= 0.0 and <= 1.0)\n");
		return;
	}

	led->priv->red = red;
	lwg_rgb_led_update (led);
}

void lwg_rgb_led_set_green (LwgRGBLed* led, const gfloat green)
{
	g_return_if_fail (LWG_IS_RGB_LED (led));

	if (green < 0.0f || green > 1.0f)
	{
		g_print ("LwgRGBLed::set_green: intensity not in valid range (must be "
				">= 0.0 and <= 1.0)\n");
		return;
	}

	led->priv->green = green;
	lwg_rgb_led_update (led);
}

void lwg_rgb_led_set_blue (LwgRGBLed* led, const gfloat blue)
{
	g_return_if_fail (LWG_IS_RGB_LED (led));

	if (blue < 0.0f || blue > 1.0f)
	{
		g_print ("LwgRGBLed::set_blue: intensity not in valid range (must be "
				">= 0.0 and <= 1.0)\n");
		return;
	}

	led->priv->blue = blue;
	lwg_rgb_led_update (led);
}

gfloat lwg_rgb_led_get_red (LwgRGBLed* led)
{
	g_return_val_if_fail (LWG_IS_RGB_LED (led), 0.0f);

	return led->priv->red;
}

gfloat lwg_rgb_led_get_green (LwgRGBLed* led)
{
	g_return_val_if_fail (LWG_IS_RGB_LED (led), 0.0f);

	return led->priv->green;
}

gfloat lwg_rgb_led_get_blue (LwgRGBLed* led)
{
	g_return_val_if_fail (LWG_IS_RGB_LED (led), 0.0f);

	return led->priv->blue;
}
