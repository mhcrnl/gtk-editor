/*
* AUTHOR	: Mihai Cornel mhcrnl@gmail.com	
* COMPILE	: $ gcc -o editor editor.c `pkg-config --libs --cflags gtk+-2.0`
* FILE		: editor.c
* VERSION	: 25.12.2018
* ADDING 	: icon.png
* RUNING	: UBUNTU 18.04
*/
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>


const char* progname = "First editor";

const char* authors[] =
{
	"Josef Luštický",
	"Kačer Donald",
	NULL
};

const char* license = "GPLv3";

GdkPixbuf* create_pixbuf(const gchar* filename);


static void about_show(void)
{
	GtkWidget * about_dialog = gtk_about_dialog_new();
	gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about_dialog), authors);
	gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(about_dialog), license);
	gtk_dialog_run(GTK_DIALOG(about_dialog));
	gtk_widget_destroy(about_dialog);
}

int main(int argc, char* argv[])
{
	GdkPixbuf *icon = NULL;
	GtkWidget * vbox = NULL;

	gtk_init(&argc, &argv);

	g_set_prgname(progname);

	GtkAccelGroup * accel_group = gtk_accel_group_new();

	GtkWidget * window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "ICON");
	gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);



	icon = create_pixbuf("user.png");
	gtk_window_set_icon(GTK_WINDOW(window), icon);

	vbox = gtk_vbox_new(FALSE, 0);
	GtkWidget * menubar = gtk_menu_bar_new();
	GtkWidget * file_menu = gtk_menu_new();
	GtkWidget * help_menu = gtk_menu_new();
	GtkWidget * file_item = gtk_menu_item_new_with_mnemonic("_File");
	GtkWidget * new_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, accel_group);
	GtkWidget * open_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, accel_group);
	GtkWidget * quit_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, accel_group);
	GtkWidget * help_item = gtk_menu_item_new_with_mnemonic("_Help");
	GtkWidget * about_item = gtk_image_menu_item_new_from_stock(GTK_STOCK_ABOUT, accel_group);
	GtkWidget * textview = gtk_text_view_new();
	GtkWidget * statusbar = gtk_statusbar_new();

	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), new_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), quit_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), about_item);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_item), file_menu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_item), help_menu);

	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help_item);

	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), textview, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, FALSE, 0);

	gtk_container_add(GTK_CONTAINER(window), vbox);

	g_signal_connect_swapped(G_OBJECT(quit_item), "activate", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect_swapped(G_OBJECT(about_item), "activate", G_CALLBACK(about_show), NULL);
	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);

	g_object_unref(icon);

	gtk_main();

	return EXIT_SUCCESS;
}

GdkPixbuf* create_pixbuf(const gchar* filename)
{
	GdkPixbuf *pixbuf;
	GError *error = NULL;

	pixbuf = gdk_pixbuf_new_from_file(filename, &error);

	if(!pixbuf) {
		fprintf(stderr, "%s\n", error->message);
		g_error_free(error);
	}
	return pixbuf;
}
