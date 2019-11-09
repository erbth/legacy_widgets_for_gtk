#include <string.h>
#include <math.h>
#include "lwgled.h"
#include "lwgledprivate.h"

/**
 * SECTION: lwgled
 * @Short_description: A LED widget for GTK+
 * @Title: LwgLed
 *
 * A LwgLed is a display widget which looks like a LED. The LED's color can
 * only be choosen during construction. If no color is specified, it will
 * default to green.
 */

#define LED_SPACING_MM		1
#define LED_RADIUS_MM		1.5

struct _LwgLedPrivate
{
	gint color;
	gfloat intensity;

	GdkRectangle led_rect;
	GdkRectangle bin_child_rect;

	gdouble led_cx, led_cy;
};

enum
{
	PROP_0,
	PROP_COLOR,
	NUM_PROPERTIES
};

static void			lwg_led_set_property (GObject*, guint, const GValue*, GParamSpec*);
static void			lwg_led_get_property (GObject*, guint, GValue*, GParamSpec*);

static void			lwg_led_get_mmpu	(LwgLed* led, gdouble* mmpu_x, gdouble* mmpu_y);

static void			lwg_led_get_preferred_width (GtkWidget*, gint*, gint*);
static void			lwg_led_get_preferred_height (GtkWidget*, gint*, gint*);
static void			lwg_led_get_preferred_width_for_height (GtkWidget*, gint, gint*, gint*);
static void			lwg_led_get_preferred_height_for_width (GtkWidget*, gint, gint*, gint*);
static void			lwg_led_size_allocate (GtkWidget* widget, GtkAllocation* allocation);

static void			lwg_led_realize		(GtkWidget*);
static gboolean		lwg_led_draw		(GtkWidget*, cairo_t* cr);

static void			lwg_led_update		(LwgLed* led);

static GParamSpec *led_props[NUM_PROPERTIES] = { NULL, };

G_DEFINE_TYPE_WITH_PRIVATE (LwgLed, lwg_led, GTK_TYPE_BIN)

static void lwg_led_class_init (LwgLedClass *class)
{
	GObjectClass*		object_class = G_OBJECT_CLASS (class);
	GtkWidgetClass* 	widget_class = GTK_WIDGET_CLASS (class);

	object_class->set_property = lwg_led_set_property;
	object_class->get_property = lwg_led_get_property;

	widget_class->get_preferred_width				= lwg_led_get_preferred_width;
	widget_class->get_preferred_height				= lwg_led_get_preferred_height;
	widget_class->get_preferred_width_for_height	= lwg_led_get_preferred_width_for_height;
	widget_class->get_preferred_height_for_width	= lwg_led_get_preferred_height_for_width;
	widget_class->size_allocate					= lwg_led_size_allocate;

	widget_class->realize							= lwg_led_realize;
	widget_class->draw								= lwg_led_draw;

	led_props[PROP_COLOR] =
		g_param_spec_uint("color",
				"Color",
				"The LED's color",
				0, LWG_LED_LAST_COLOR,
				0,
				G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);

	g_object_class_install_properties(object_class, NUM_PROPERTIES, led_props);
}

static void lwg_led_init (LwgLed *led)
{
	GtkWidget* widget = GTK_WIDGET (led);

	led->priv = G_TYPE_INSTANCE_GET_PRIVATE (led, LWG_TYPE_LED, LwgLedPrivate);
	led->priv->color = LWG_LED_COLOR_GREEN;
	led->priv->intensity = 0.0f;

	gtk_widget_set_has_window (widget, TRUE);
}

static void lwg_led_set_property (
		GObject* object,
		guint property_id,
		const GValue* value,
		GParamSpec* pspec)
{
	LwgLed* this = LWG_LED (object);

	switch (property_id)
	{
		case PROP_COLOR:
			this->priv->color = g_value_get_uint (value);
			break;

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

static void lwg_led_get_property (
		GObject* object,
		guint property_id,
		GValue* value,
		GParamSpec* pspec)
{
	LwgLed* this = LWG_LED (object);

	switch (property_id)
	{
		case PROP_COLOR:
			g_value_set_uint (value, this->priv->color);
			break;

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

static void lwg_led_get_mmpu (LwgLed* led, gdouble* mmpu_x, gdouble* mmpu_y)
{
	*mmpu_x = *mmpu_y = 96.0 / 25.4;
}

static void lwg_led_get_preferred_width (GtkWidget* w, gint* min, gint* natural)
{
	gdouble mmpu_x, mmpu_y;
	LwgLed* led;
	GtkWidget* child;
	gint child_min = 0, child_natural = 0;

	led = LWG_LED (w);
	lwg_led_get_mmpu (led, &mmpu_x, &mmpu_y);

	child = gtk_bin_get_child (GTK_BIN (led));

	if (child)
		gtk_widget_get_preferred_width (child, &child_min, &child_natural);

	gint led_width = ceilf ((LED_SPACING_MM + LED_RADIUS_MM) * 2 * mmpu_x);
	*min = led_width + child_min;
	*natural = led_width + child_natural;
}

static void lwg_led_get_preferred_height (GtkWidget* w, gint* pmin, gint* pnatural)
{
	gdouble mmpu_x, mmpu_y;
	LwgLed* led;
	GtkWidget* child;
	gint min, natural;
	gint child_min = 0, child_natural = 0;

	led = LWG_LED (w);
	lwg_led_get_mmpu (led, &mmpu_x, &mmpu_y);

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

static void lwg_led_get_preferred_width_for_height (
		GtkWidget* w,
		gint height,
		gint* min,
		gint* natural)
{
	gdouble mmpu_x, mmpu_y;
	LwgLed* led;
	GtkWidget* child;
	gint child_min = 0, child_natural = 0;

	led = LWG_LED (w);
	lwg_led_get_mmpu (led, &mmpu_x, &mmpu_y);

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

static void lwg_led_get_preferred_height_for_width (
		GtkWidget* w,
		gint width,
		gint* pmin,
		gint* pnatural)
{
	gdouble mmpu_x, mmpu_y;
	LwgLed* led;
	GtkWidget* child;
	gint min, natural;
	gint child_min = 0, child_natural = 0;

	led = LWG_LED (w);
	lwg_led_get_mmpu (led, &mmpu_x, &mmpu_y);

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

static void lwg_led_size_allocate (
		GtkWidget* widget,
		GtkAllocation* allocation)
{
	GdkWindow* window;
	GtkWidget* child;
	LwgLed* led;
	gdouble mmpu_x, mmpu_y;

	led = LWG_LED (widget);
	lwg_led_get_mmpu (led, &mmpu_x, &mmpu_y);

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

		lwg_led_get_mmpu (led, &mmpu_x, &mmpu_y);

		child_allocation.x = child_rect->x;
		child_allocation.y = child_rect->y;
		child_allocation.width = child_rect->width;
		child_allocation.height = child_rect->height;

		gtk_widget_size_allocate (child, &child_allocation);
	}
}

static void lwg_led_realize (GtkWidget* w)
{
	LwgLed* led;
	GtkAllocation allocation;
	GdkWindow* window;
	GdkWindowAttr attributes;

	led = LWG_LED (w);

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

static gboolean lwg_led_draw (GtkWidget* w, cairo_t *cr)
{
	gdouble mmpu_x, mmpu_y;
	LwgLed* led;
	GtkWidget* child = NULL;

	led = LWG_LED (w);
	lwg_led_get_mmpu (led, &mmpu_x, &mmpu_y);

	/* Draw the LED */
	cairo_save (cr);

	if (led->priv->intensity < 0.5)
		cairo_set_source_rgb (cr, 0, 0.2, 0);
	else
		cairo_set_source_rgb (cr, 0, 1, 0);

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

static void lwg_led_update (LwgLed* led)
{
	gdouble mmpu_x, mmpu_y;

	lwg_led_get_mmpu (led, &mmpu_x, &mmpu_y);

	gtk_widget_queue_draw_area (
			GTK_WIDGET (led),
			floorf (led->priv->led_cx - LED_RADIUS_MM * mmpu_x),
			floorf (led->priv->led_cy - LED_RADIUS_MM * mmpu_y),
			ceilf (LED_RADIUS_MM * 2 * mmpu_x) + 1,
			ceilf (LED_RADIUS_MM * 2 * mmpu_y) + 1);
}

GtkWidget* lwg_led_new (const gint color)
{
	return g_object_new (LWG_TYPE_LED, "color", color, NULL);
}

GtkWidget* lwg_led_new_with_label (const gint color, const gchar* label)
{
	GtkWidget* led = g_object_new (LWG_TYPE_LED, "color", color, NULL);

	GtkWidget* label_widget = gtk_label_new (label);
	gtk_label_set_xalign (GTK_LABEL (label_widget), 0);

	gtk_container_add (GTK_CONTAINER(led), label_widget);

	return led;
}

guint lwg_led_get_color (LwgLed* led)
{
	GValue val;
	g_object_get_property (G_OBJECT(led), "color", &val);

	return g_value_get_uint (&val);
}

void lwg_led_set_intensity (LwgLed* led, const gfloat intensity)
{
	g_return_if_fail (LWG_IS_LED (led));

	if (intensity < 0.0f || intensity > 1.0f)
	{
		g_print ("LwgLed::set_intensity: intensity not in valid range (must be "
				">= 0.0 and <= 1.0)\n");
		return;
	}

	led->priv->intensity = intensity;
	lwg_led_update (led);
}

gfloat lwg_led_get_intensity (LwgLed* led)
{
	g_return_val_if_fail (LWG_IS_LED (led), 0.0f);

	return led->priv->intensity;
}
