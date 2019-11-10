#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "legacy_widgets_for_gtk.h"

/* Some LEDs */
GtkWidget* led1 = NULL;
GtkWidget* led2 = NULL;
GtkWidget* led3 = NULL;
GtkWidget* led4 = NULL;
GtkWidget* led5 = NULL;

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

static void s5_r_changed (GtkRange *range, void *data)
{
	lwg_rgb_led_set_red (LWG_RGB_LED(led5), gtk_range_get_value(range));
}

static void s5_g_changed (GtkRange *range, void *data)
{
	lwg_rgb_led_set_green(LWG_RGB_LED(led5), gtk_range_get_value(range));
}

static void s5_b_changed (GtkRange *range, void *data)
{
	lwg_rgb_led_set_blue (LWG_RGB_LED(led5), gtk_range_get_value(range));
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
	led5 = lwg_rgb_led_new ();

	GtkWidget* frame1 = gtk_frame_new(NULL);
	GtkWidget* frame2 = gtk_frame_new(NULL);
	GtkWidget* frame3 = gtk_frame_new(NULL);
	GtkWidget* frame4 = gtk_frame_new(NULL);
	GtkWidget* frame5 = gtk_frame_new(NULL);

	gtk_container_add(GTK_CONTAINER(frame1), led1);
	gtk_container_add(GTK_CONTAINER(frame2), led2);
	gtk_container_add(GTK_CONTAINER(frame3), led3);
	gtk_container_add(GTK_CONTAINER(frame4), led4);
	gtk_container_add(GTK_CONTAINER(frame5), led5);

	GtkWidget* hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget* hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget* hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget* hbox4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget* hbox5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

	gtk_box_pack_start(GTK_BOX(hbox1), frame1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox2), frame2, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox3), frame3, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox4), frame4, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox5), frame5, FALSE, FALSE, 0);

	GtkWidget *bt1 = gtk_toggle_button_new_with_label("LED 1");
	GtkWidget *bt2 = gtk_toggle_button_new_with_label("LED 2");
	GtkWidget *bt3 = gtk_toggle_button_new_with_label("LED 3");
	GtkWidget *bt4 = gtk_toggle_button_new_with_label("LED 4");

	GtkWidget *s5_r = gtk_scale_new_with_range (GTK_ORIENTATION_VERTICAL, 0, 1, 0.01);
	GtkWidget *s5_g = gtk_scale_new_with_range (GTK_ORIENTATION_VERTICAL, 0, 1, 0.01);
	GtkWidget *s5_b = gtk_scale_new_with_range (GTK_ORIENTATION_VERTICAL, 0, 1, 0.01);

	gtk_range_set_inverted (GTK_RANGE(s5_r), TRUE);
	gtk_range_set_inverted (GTK_RANGE(s5_g), TRUE);
	gtk_range_set_inverted (GTK_RANGE(s5_b), TRUE);

	gtk_box_pack_start(GTK_BOX(hbox1), bt1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox2), bt2, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox3), bt3, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox4), bt4, FALSE, FALSE, 0);

	gtk_box_pack_start(GTK_BOX(hbox5), s5_r, FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(hbox5), s5_g, FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(hbox5), s5_b, FALSE, FALSE, 10);

	gtk_box_pack_start(GTK_BOX(main_vbox), hbox1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_vbox), hbox2, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_vbox), hbox3, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_vbox), hbox4, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_vbox), hbox5, TRUE, TRUE, 0);

	/* Connect button clicked signals */
	g_signal_connect (G_OBJECT(bt1), "toggled", G_CALLBACK(bt1_toggled), NULL);
	g_signal_connect (G_OBJECT(bt2), "toggled", G_CALLBACK(bt2_toggled), NULL);
	g_signal_connect (G_OBJECT(bt3), "toggled", G_CALLBACK(bt3_toggled), NULL);
	g_signal_connect (G_OBJECT(bt4), "toggled", G_CALLBACK(bt4_toggled), NULL);

	g_signal_connect (G_OBJECT(s5_r), "value-changed", G_CALLBACK(s5_r_changed), NULL);
	g_signal_connect (G_OBJECT(s5_g), "value-changed", G_CALLBACK(s5_g_changed), NULL);
	g_signal_connect (G_OBJECT(s5_b), "value-changed", G_CALLBACK(s5_b_changed), NULL);

	gtk_widget_show_all(window);

	gtk_main();

END:
	return ret_code;

ERROR:
	ret_code = EXIT_FAILURE;
	goto END;
}
