#ifndef __LWG_RGB_LED_H__
#define __LWG_RGB_LED_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define LWG_TYPE_RGB_LED (lwg_rgb_led_get_type())
#define LWG_RGB_LED(obj) (G_TYPE_CHECK_INSTANCE_CAST (obj, LWG_TYPE_RGB_LED, LwgRGBLed))
#define LWG_RGB_LED_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST (klass, LWG_TYPE_LWD, LwgRGBLedClass))
#define LWG_IS_RGB_LED(obj) (G_TYPE_CHECK_INSTANCE_TYPE (obj, LWG_TYPE_RGB_LED))
#define LWG_IS_RGB_LED_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE (klass, LWG_TYPE_RGB_LED))
#define LWG_RGB_LED_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS (obj, LWG_TYPE_RGB_LED, LwgRGBLedClass))

typedef struct _LwgRGBLed LwgRGBLed;
typedef struct _LwgRGBLedPrivate LwgRGBLedPrivate;
typedef struct _LwgRGBLedClass LwgRGBLedClass;

struct _LwgRGBLedClass
{
	GtkBinClass parent_class;
};

struct _LwgRGBLed
{
	GtkBin bin;

	LwgRGBLedPrivate *priv;
};

GType		lwg_rgb_led_get_type		(void) G_GNUC_CONST;

GtkWidget*	lwg_rgb_led_new				();

/* A shortcut to create a rgb_led with a label */
GtkWidget*	lwg_rgb_led_new_with_label	(const gchar *label);

void		lwg_rgb_led_set_red		(LwgRGBLed *rgb_led, const gfloat red);
void		lwg_rgb_led_set_green	(LwgRGBLed *rgb_led, const gfloat green);
void		lwg_rgb_led_set_blue	(LwgRGBLed *rgb_led, const gfloat blue);

gfloat		lwg_rgb_led_get_red		(LwgRGBLed *rgb_led);
gfloat		lwg_rgb_led_get_green	(LwgRGBLed *rgb_led);
gfloat		lwg_rgb_led_get_blue	(LwgRGBLed *rgb_led);

G_END_DECLS

#endif
