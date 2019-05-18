#include"cr.h"
#include<gtk/gtk.h>

void again(GtkWidget *but, sg *p) {
	gtk_widget_destroy(p->gr);
	free(p->b);
	initgtkwidgets(p->exbt[9], p);
	gtk_widget_show_all(p->win);
	return;
}
void initgtkwidgets(GtkWidget *but, sg *p) {
	p->gr = gtk_grid_new();
        gtk_window_set_default_size(GTK_WINDOW(p->win), 3000, 3000);
	gtk_window_set_position(GTK_WINDOW(p->win), GTK_WIN_POS_CENTER);
        gtk_container_add(GTK_CONTAINER(p->win), p->gr);
	int i;
	p->b = malloc(sizeof(board));
 	for(i = 0; i < 50; i++) {
		p->lab = gtk_label_new("                                                                                                                                                                          ");
		gtk_grid_attach(GTK_GRID(p->gr), p->lab, 0, i, 2000, 10);
	}
	p->exbt[0] = gtk_button_new();
	p->exbt[1] = gtk_button_new();
	p->exbt[2] = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(p->exbt[0]), "NEW GAME");
	gtk_button_set_label(GTK_BUTTON(p->exbt[1]), "CONTINUE");
	gtk_button_set_label(GTK_BUTTON(p->exbt[2]), "QUIT");
	for(i = 0; i < 3; i++)
		gtk_grid_attach(GTK_GRID(p->gr), p->exbt[i], 2000, 1000 + (i + 1) * 100, 100, 50);
	g_signal_connect(p->exbt[0], "clicked", G_CALLBACK(setboard), p);
	g_signal_connect(p->exbt[2], "clicked", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(p->exbt[1], "clicked", G_CALLBACK(setsavedgame), p);
        return;
}

void setboard(GtkWidget *b, sg *p) {
	int i;
	gtk_widget_destroy(p->gr);
	p->gr = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(p->win), p->gr);
	p->exbt[3] = gtk_button_new();
	p->exbt[4] = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(p->exbt[3]), "DONE");
	p->exbt[2] = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(p->exbt[2]), "QUIT");
	gtk_button_set_label(GTK_BUTTON(p->exbt[4]), "BACK");
	for(i = 0; i < 47; i++) {
		p->lab = gtk_label_new("                                                                                                                                              ");
		gtk_grid_attach(GTK_GRID(p->gr), p->lab, 0, i, 1700, 10);
	}
	
	GtkWidget *lab;
	p->b->m = 0;
	p->ib = gtk_entry_new();
	lab = gtk_label_new("ENTER NUMBER OF PLAYERS FROM 2 TO 7");
	gtk_grid_attach(GTK_GRID(p->gr), lab, 1700, i * (i - 1)/2, 100, 50);
	gtk_grid_attach(GTK_GRID(p->gr), p->ib, 1700, i * (i - 1)/2 + 100, 100, 50);
	gtk_grid_attach(GTK_GRID(p->gr), p->exbt[3], 1700, i * (i - 1) / 2 + 200, 100, 50);
	gtk_grid_attach(GTK_GRID(p->gr), p->exbt[2], 1700, i * (i - 1) / 2 + 400, 100, 50);
	gtk_grid_attach(GTK_GRID(p->gr), p->exbt[4], 1700, i * (i - 1) / 2 + 300, 100, 50);
	p->b->restart = 0;
	g_signal_connect(p->exbt[3], "clicked", G_CALLBACK(tgame), p);
	g_signal_connect(p->exbt[2], "clicked", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(p->exbt[4], "clicked", G_CALLBACK(again), p);
	gtk_widget_show_all(p->win);
	return;
}

