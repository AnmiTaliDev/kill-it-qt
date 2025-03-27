#include <gtk//gtk.h>
#include <glib.h>
#include <stdio.h>
#include "parse_config.h"

static parse_result config;

void 
set_margins (GtkWidget *widget, int margin) 
{
    gtk_widget_set_margin_start (widget, margin);
    gtk_widget_set_margin_end (widget, margin);
    gtk_widget_set_margin_top (widget, margin);
    gtk_widget_set_margin_bottom (widget, margin);
}

static void
on_poweroff_button_clicked (GtkWidget *widget,
							gpointer   data)
{
    g_spawn_command_line_async (config.poweroff_command, NULL);
}

static void
on_suspend_button_clicked (GtkWidget *widget,
							gpointer   data)
{
    g_spawn_command_line_async (config.suspend_command,NULL);
}

static void
on_reboot_button_clicked (GtkWidget *widget,
							gpointer   data)
{
    g_spawn_command_line_async (config.reboot_command, NULL);
}

static void
on_hibernate_button_clicked (GtkWidget *widget,
							gpointer   data)
{
    g_spawn_command_line_async (config.hibernate_command, NULL);
}

static void
activate (GtkApplication* app,
		  gpointer        user_data)
{
	GtkWidget *window;

	GtkWidget *cancel_button;
	GtkWidget *poweroff_button;
	GtkWidget *suspend_button;
	GtkWidget *reboot_button;
	GtkWidget *hibernate_button;
	GtkWidget *label;

	GtkWidget *box;
	GtkWidget *vbox;

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "kill it");
	gtk_window_set_default_size (GTK_WINDOW (window), 100, 75); 

    GtkSettings *default_settings = gtk_settings_get_default();
    gtk_window_set_resizable(window, FALSE);

	vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
	box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,10);

    set_margins(vbox, 10);
    
	gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign (box, GTK_ALIGN_CENTER);
	
	gtk_window_set_child (GTK_WINDOW (window), vbox);

	label = gtk_label_new_with_mnemonic  ("Kill it? v1.4");

	cancel_button = gtk_button_new_with_label ("Cancel");
	poweroff_button = gtk_button_new_with_label ("Poweroff");
	suspend_button = gtk_button_new_with_label ("Suspend");
	reboot_button = gtk_button_new_with_label ("Reboot");
	hibernate_button = gtk_button_new_with_label ("Hibernate");

    g_signal_connect_swapped (cancel_button, "clicked", G_CALLBACK (gtk_window_destroy), window);

	g_signal_connect (poweroff_button, "clicked", G_CALLBACK (on_poweroff_button_clicked), NULL);
	g_signal_connect_swapped (poweroff_button, "clicked", G_CALLBACK (gtk_window_destroy), window);
	
	g_signal_connect (suspend_button, "clicked", G_CALLBACK (on_suspend_button_clicked), NULL);
	g_signal_connect_swapped (suspend_button, "clicked", G_CALLBACK (gtk_window_destroy), window);

	g_signal_connect (reboot_button, "clicked", G_CALLBACK (on_reboot_button_clicked), NULL);
	g_signal_connect_swapped (reboot_button, "clicked", G_CALLBACK (gtk_window_destroy), window);

	g_signal_connect (hibernate_button, "clicked", G_CALLBACK (on_hibernate_button_clicked), NULL);
	g_signal_connect_swapped (hibernate_button, "clicked", G_CALLBACK (gtk_window_destroy), window);
    
	gtk_box_append (GTK_BOX (box), cancel_button);
    
    if (config.reboot_enabled)
        gtk_box_append (GTK_BOX (box), reboot_button);

    if (config.poweroff_enabled)
        gtk_box_append (GTK_BOX (box), poweroff_button);

    if (config.suspend_enabled)
        gtk_box_append (GTK_BOX (box), suspend_button);

    if (config.hibernate_enabled)
        gtk_box_append (GTK_BOX (box), hibernate_button);

	gtk_box_append (GTK_BOX (vbox), label);
	gtk_box_append (GTK_BOX (vbox), box);

	gtk_window_present (GTK_WINDOW (window));
}

int
main (int	argc,
	  char **argv)
{
    config = parse_config();
	GtkApplication *app;
	int status;

	app = gtk_application_new ("org.ruzen42.killit", G_APPLICATION_REPLACE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	return status;
}
