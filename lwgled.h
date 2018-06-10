#ifndef __LWG_LED_H__
#define __LWG_LED_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define LWG_TYPE_LED (lwg_led_get_type())
#define LWG_LED(obj) (G_TYPE_CHECK_INSTANCE_CAST (obj, LWG_TYPE_LED, LwgLed))
#define LWG_LED_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST (klass, LWG_TYPE_LWD, LwgLedClass))
#define LWG_IS_LED(obj) (G_TYPE_CHECK_INSTANCE_TYPE (obj, LWG_TYPE_LED))
#define LWG_IS_LED_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE (klass, LWG_TYPE_LED))
#define LWG_LED_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS (obj, LWG_TYPE_LED, LwgLedClass))

typedef struct _LwgLed LwgLed;
typedef struct _LwgLedPrivate LwgLedPrivate;
typedef struct _LwgLedClass LwgLedClass;

struct _LwgLedClass
{
	GtkBinClass parent_class;
};

struct _LwgLed
{
	GtkBin bin;

	LwgLedPrivate *priv;
};

enum
{
	LWG_LED_COLOR_GREEN,
	LWG_LED_COLOR_RED,
	LWG_LED_COLOR_YELLOW,
	LWG_LED_LAST_COLOR
};

GType		lwg_led_get_type		(void) G_GNUC_CONST;

GtkWidget*	lwg_led_new				(const gint color);

/* A shortcut to create a led with a label */
GtkWidget*	lwg_led_new_with_label	(const gint color, const gchar *label);

guint		lwg_led_get_color		(LwgLed* led);

void		lwg_led_set_intensity	(LwgLed *led, const gfloat intensity);
gfloat		lwg_led_get_intensity	(LwgLed *led);

G_END_DECLS

#endif
