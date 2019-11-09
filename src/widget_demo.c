#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "lwgled.h"

/* Some LEDs */
GtkWidget* led1 = NULL;
GtkWidget* led2 = NULL;
GtkWidget* led3 = NULL;
GtkWidget* led4 = NULL;

static void destroy (GtkWidget* widget, gpointer data)
{
	gtk_main_quit();
}

static void bt1_toggled(GtkToggleButton *bt, void *data)
{
	if (gtk_toggle_button_get_active(bt))
		lwg_led_set_intensity (LWG_LED(led1), 1.);
	else
		lwg_led_set_intensity (LWG_LED(led1), 0.);
}

static void bt2_toggled(GtkToggleButton *bt, void *data)
{
	if (gtk_toggle_button_get_active(bt))
		lwg_led_set_intensity (LWG_LED(led2), 1.);
	else
		lwg_led_set_intensity (LWG_LED(led2), 0.);
}

static void bt3_toggled(GtkToggleButton *bt, void *data)
{
	if (gtk_toggle_button_get_active(bt))
		lwg_led_set_intensity (LWG_LED(led3), 1.);
	else
		lwg_led_set_intensity (LWG_LED(led3), 0.);
}

static void bt4_toggled(GtkToggleButton *bt, void *data)
{
	if (gtk_toggle_button_get_active(bt))
		lwg_led_set_intensity (LWG_LED(led4), 1.);
	else
		lwg_led_set_intensity (LWG_LED(led4), 0.);
}

int main(int argc, char** argv)
{
	int ret_code = EXIT_SUCCESS;

	gtk_init(&argc, &argv);

	/* Create a window */
	GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Legacy Widgets for GTK+");

	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK (destroy), NULL);

	GtkWidget* main_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add (GTK_CONTAINER (window), main_vbox);

	/* Create LEDs with corresponding buttons */
	led1 = lwg_led_new (LWG_LED_COLOR_GREEN);
	led2 = lwg_led_new (LWG_LED_COLOR_RED);
	led3 = lwg_led_new (LWG_LED_COLOR_YELLOW);
	led4 = lwg_led_new (LWG_LED_COLOR_BLUE);

	GtkWidget* frame1 = gtk_frame_new(NULL);
	GtkWidget* frame2 = gtk_frame_new(NULL);
	GtkWidget* frame3 = gtk_frame_new(NULL);
	GtkWidget* frame4 = gtk_frame_new(NULL);

	gtk_container_add(GTK_CONTAINER(frame1), led1);
	gtk_container_add(GTK_CONTAINER(frame2), led2);
	gtk_container_add(GTK_CONTAINER(frame3), led3);
	gtk_container_add(GTK_CONTAINER(frame4), led4);

	GtkWidget* hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget* hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget* hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget* hbox4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

	gtk_box_pack_start(GTK_BOX(hbox1), frame1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox2), frame2, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox3), frame3, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox4), frame4, FALSE, FALSE, 0);

	GtkWidget *bt1 = gtk_toggle_button_new_with_label("LED 1");
	GtkWidget *bt2 = gtk_toggle_button_new_with_label("LED 1");
	GtkWidget *bt3 = gtk_toggle_button_new_with_label("LED 1");
	GtkWidget *bt4 = gtk_toggle_button_new_with_label("LED 1");

	gtk_box_pack_start(GTK_BOX(hbox1), bt1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox2), bt2, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox3), bt3, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox4), bt4, FALSE, FALSE, 0);

	gtk_box_pack_start(GTK_BOX(main_vbox), hbox1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_vbox), hbox2, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_vbox), hbox3, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_vbox), hbox4, FALSE, FALSE, 0);

	/* Connect button clicked signals */
	g_signal_connect (G_OBJECT(bt1), "toggled", G_CALLBACK(bt1_toggled), NULL);
	g_signal_connect (G_OBJECT(bt2), "toggled", G_CALLBACK(bt2_toggled), NULL);
	g_signal_connect (G_OBJECT(bt3), "toggled", G_CALLBACK(bt3_toggled), NULL);
	g_signal_connect (G_OBJECT(bt4), "toggled", G_CALLBACK(bt4_toggled), NULL);

	gtk_widget_show_all(window);

	gtk_main();

END:
	return ret_code;

ERROR:
	ret_code = EXIT_FAILURE;
	goto END;
}
