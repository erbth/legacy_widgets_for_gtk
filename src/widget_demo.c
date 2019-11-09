#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "lwgled.h"

typedef struct _led_timeout_private led_timeout_private;
struct _led_timeout_private
{
	gfloat delta;
	gfloat intensity;
	gboolean increasing;
	GtkWidget* led;
};

static gboolean led_timeout (gpointer data)
{
	led_timeout_private* ltp = data;

	if (ltp->increasing)
	{
		ltp->intensity += ltp->delta;
		
		if (ltp->intensity > 1.0f)
		{
			ltp->intensity = 1.0f - ltp->delta;
			ltp->increasing = FALSE;
		}
	}
	else
	{
		ltp->intensity -= ltp->delta;

		if (ltp->intensity < 0.0f)
		{
			ltp->intensity = 0.0f + ltp->delta;
			ltp->increasing = TRUE;
		}
	}

	lwg_led_set_intensity (LWG_LED (ltp->led), ltp->intensity);

	return TRUE;
}

static void destroy (GtkWidget* widget, gpointer data)
{
	gtk_main_quit();
}

int main(int argc, char** argv)
{
	int ret_code = EXIT_SUCCESS;
	led_timeout_private ltp;

	gtk_init(&argc, &argv);

	/* Create a window */
	GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Legacy Widgets for GTK+");

	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK (destroy), NULL);

	/* Create a LED */
	GtkWidget* led = lwg_led_new_with_label (LWG_LED_COLOR_GREEN, "Test LED");
	// GtkWidget* led = lwg_led_new (LWG_LED_COLOR_GREEN);
	gtk_container_add (GTK_CONTAINER (window), led);

	/* Set up a timeout for the LED */
	ltp.intensity = 0.0f;
	ltp.delta = 1.0f;
	ltp.led = led;
	ltp.increasing = FALSE;

	g_timeout_add_seconds (1, led_timeout, &ltp);

	gtk_widget_show_all(window);

	gtk_main();

END:
	return ret_code;

ERROR:
	ret_code = EXIT_FAILURE;
	goto END;
}
