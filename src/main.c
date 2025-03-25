#include <gtk//gtk.h>
#include <glib.h>
#include <stdio.h>

static void
on_poweroff_button_clicked (GtkWidget *widget,
							gpointer   data)
{
    g_spawn_command_line_async ("loginctl poweroff", NULL);
}

static void
on_suspend_button_clicked (GtkWidget *widget,
							gpointer   data)
{
    g_spawn_command_line_async ("loginctl suspend", NULL);
}

static void
on_reboot_button_clicked (GtkWidget *widget,
							gpointer   data)
{
    g_spawn_command_line_async ("loginctl reboot ", NULL);
}

static void
activate (GtkApplication* app,
		 gpointer          user_data)
{
	GtkWidget *window;

	GtkWidget *cancel_button;
	GtkWidget *poweroff_button;
	GtkWidget *suspend_button;
	GtkWidget *reboot_button;
	GtkWidget *label;

	GtkWidget *box;
	GtkWidget *vbox;

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "kill it");
	gtk_window_set_default_size (GTK_WINDOW (window), 400, 100); 

    GtkSettings *default_settings = gtk_settings_get_default();

	box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
	vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
	gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign (box, GTK_ALIGN_CENTER);
	
	gtk_window_set_child (GTK_WINDOW (window), vbox);

	cancel_button = gtk_button_new_with_label ("Cancel");
	label = gtk_label_new_with_mnemonic  ("Kill it?");
	poweroff_button = gtk_button_new_with_label ("Poweroff");
	suspend_button = gtk_button_new_with_label ("Suspend");
	reboot_button = gtk_button_new_with_label ("Reboot");

    g_signal_connect_swapped (cancel_button, "clicked", G_CALLBACK (gtk_window_destroy), window);

	g_signal_connect (poweroff_button, "clicked", G_CALLBACK (on_poweroff_button_clicked), NULL);
	g_signal_connect_swapped (poweroff_button, "clicked", G_CALLBACK (gtk_window_destroy), window);
	
	g_signal_connect (suspend_button, "clicked", G_CALLBACK (on_suspend_button_clicked), NULL);
	g_signal_connect_swapped (suspend_button, "clicked", G_CALLBACK (gtk_window_destroy), window);

	g_signal_connect (reboot_button, "clicked", G_CALLBACK (on_reboot_button_clicked), NULL);
	g_signal_connect_swapped (reboot_button, "clicked", G_CALLBACK (gtk_window_destroy), window);

	gtk_box_append (GTK_BOX (box), cancel_button);
	gtk_box_append (GTK_BOX (box), poweroff_button);
	gtk_box_append (GTK_BOX (box), suspend_button);
	gtk_box_append (GTK_BOX (box), reboot_button);

	gtk_box_append (GTK_BOX (vbox), label);
	gtk_box_append (GTK_BOX (vbox), box);

	gtk_window_present (GTK_WINDOW (window));
}

int
main (int	argc,
	  char **argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new ("org.ruzen42.killit", G_APPLICATION_REPLACE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	return status;
}
