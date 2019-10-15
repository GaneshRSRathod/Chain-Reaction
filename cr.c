#include<stdio.h>
#include<gtk/gtk.h>
#include"cr.h"

//commented
int main(int argc, char* argv[]) {
	int i, j;
	gtk_init(&argc, &argv);
	sg *p;
	p = malloc(sizeof(sg));
	p->win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	p->win2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(p->win), "CHAIN REACTION");
	gtk_window_set_title(GTK_WINDOW(p->win2), "CHAIN REACTION");
	p->im = gtk_image_new();
	p->im2 = gtk_image_new();
	p->ib = gtk_entry_new();
	p->ic = gtk_entry_new();
	for(i = 0; i < 11; i++)
		for(j = 0; j < 23; j++)
			p->img[i][j] = gtk_image_new();
	initgtkwidgets(p->exbt[9], p);
	gtk_widget_show_all(p->win);
	g_signal_connect(p->win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_main();
	return 0;
}

