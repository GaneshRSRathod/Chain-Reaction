#include<gtk/gtk.h>
#include"cr.h"
#include<stdlib.h>

void tgame(GtkWidget *but, sg *p) {
	char c[20];
	int t, i;
	strcpy(c, gtk_entry_get_text(GTK_ENTRY(p->ib)));
	sscanf(c, "%d", &t);
	if(t < 2 || t > 7 || c[1] != '\0')
		return;
	p->b->num_of_players = t;
	p->b->num_of_players_static = t;
	p->ib = gtk_entry_new();
	p->ic = gtk_entry_new();
	gtk_widget_destroy(p->gr);
	p->gr = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(p->win), p->gr);
	for(i = 0; i < 44; i++) {
		p->lab = gtk_label_new("                                                                                                                                             ");
		gtk_grid_attach(GTK_GRID(p->gr), p->lab, 0, i, 1700, 10);
	}
	GtkWidget *lab1, *lab2;
	lab1 = gtk_label_new("ENTER NUMBER OF ROW FROM 3 TO 11");
	lab2 = gtk_label_new("ENTER NUMBER OF COLUMN FROM 3 TO 23");

	p->exbt[8] = gtk_button_new();
	p->exbt[9] = gtk_button_new();
	p->exbt[7] = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(p->exbt[8]), "DONE");
	gtk_button_set_label(GTK_BUTTON(p->exbt[9]), "QUIT");
	gtk_button_set_label(GTK_BUTTON(p->exbt[7]), "BACK");
	gtk_grid_attach(GTK_GRID(p->gr), lab1,1700, i*(i-1)/2, 100, 50);
	gtk_grid_attach(GTK_GRID(p->gr), p->ib, 1700, i*(i-1)/2 + 100, 100, 50);
	gtk_grid_attach(GTK_GRID(p->gr), lab2, 1700, i*(i-1)/2 + 200, 100, 50);
	gtk_grid_attach(GTK_GRID(p->gr), p->ic, 1700, i*(i-1)/2 + 300, 100, 50);
	gtk_grid_attach(GTK_GRID(p->gr), p->exbt[8], 1700, i*(i-1)/2 + 400, 100, 50);
	gtk_grid_attach(GTK_GRID(p->gr), p->exbt[7], 1700, i*(i-1)/2 + 500, 100, 50);
	gtk_grid_attach(GTK_GRID(p->gr), p->exbt[9], 1700, i*(i-1)/2 + 600, 100, 50);
	g_signal_connect(p->exbt[8], "clicked", G_CALLBACK(setgame), p);
	g_signal_connect(p->exbt[7], "clicked", G_CALLBACK(setboard), p);
	g_signal_connect(p->exbt[9], "clicked", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(p->win);
}

void setgame(GtkWidget *but, sg *p) {
	char c1[20], c2[20];
	int t1, t2;
	if(p->b->restart) {
		p->b->num_of_players = p->b->num_of_players_static;
		p->b->m = 0;
	}
	else {
		strcpy(c1, gtk_entry_get_text(GTK_ENTRY(p->ib)));
		strcpy(c2, gtk_entry_get_text(GTK_ENTRY(p->ic)));
		sscanf(c1, "%d", &t1);
		sscanf(c2, "%d", &t2);
		if(t1 < 3 || t1 > 11 || t2 < 3 || t2 > 23)
			return;
		p->b->num_of_row = t1;
		p->b->num_of_col = t2;
	}
	p->b->clr = 1;
	gtk_widget_destroy(p->gr);
	p->gr = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(p->win), p->gr);
	
	initimage(p);
	int i, j;
	for(i = 0; i < p->b->num_of_row; i++)
		for(j = 0; j < p->b->num_of_col; j++) {
			p->img[i][j] = gtk_image_new_from_file(p->image[0][0]);
			p->bt[i][j] = gtk_button_new();
			gtk_button_set_image(GTK_BUTTON(p->bt[i][j]),  p->img[i][j]);
			gtk_widget_set_size_request(p->bt[i][j], 70, 90);
			gtk_grid_attach(GTK_GRID(p->gr), p->bt[i][j], j * 60, i * 90, 60, 90);
		}
	p->exbt[0] = gtk_button_new_with_label("NEW GAME");
	p->exbt[1] = gtk_button_new_with_label("SAVE");
	p->exbt[2] = gtk_button_new_with_label("RESTART");
	p->exbt[5] = gtk_button_new_with_label("QUIT");
	p->exbt[3] = gtk_button_new_with_label("UNDO");
	p->exbt[6] = gtk_button_new_with_label("TURN");
	p->exbt[4] = gtk_button_new_with_label("HOME");
	GtkWidget *k;
	k = gtk_label_new("                        ");
	gtk_grid_attach(GTK_GRID(p->gr), k, p->b->num_of_col * 60, 0, 100, 25);
	p->b->restart = 1;
	for(i = 0; i <= 5; i++)
		gtk_grid_attach(GTK_GRID(p->gr), p->exbt[i], (p->b->num_of_col * 60) + 100, i * 50, 100, 45);
	gtk_grid_attach(GTK_GRID(p->gr), p->exbt[6], (p->b->num_of_col * 60) + 100, 400, 100, 45);
	g_signal_connect(p->exbt[0], "clicked", G_CALLBACK(setboard), p);
	g_signal_connect(p->exbt[2], "clicked", G_CALLBACK(setgame), p);
	g_signal_connect(p->exbt[1], "clicked", G_CALLBACK(savegame), p);
	g_signal_connect(p->exbt[5], "clicked", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(p->exbt[3], "clicked", G_CALLBACK(undo), p);
	g_signal_connect(p->exbt[4], "clicked", G_CALLBACK(again), p);
	p->im = gtk_image_new_from_file(p->image[1][0]);
	gtk_button_set_image(GTK_BUTTON(p->exbt[6]), p->im);
	buttondata *bd[11][23];
	for(i = 0; i < p->b->num_of_row; i++)
		for(j = 0; j < p->b->num_of_col; j++) {
			bd[i][j] = malloc(sizeof(buttondata));
			bd[i][j]->p = p;
			g_signal_connect(p->bt[i][j], "clicked", G_CALLBACK(game), bd[i][j]);
			p->b->box[i][j] = malloc(sizeof(square));
			bd[i][j]->s = p->b->box[i][j];
			p->b->box[i][j]->num_of_balls = 0;
			p->b->box[i][j]->kalar = 0;
			p->b->box[i][j]->row = i;
			p->b->box[i][j]->column = j;
			if((i == 0 || i == p->b->num_of_row - 1) && (j == 0 || j == p->b->num_of_col - 1))
				p->b->box[i][j]->level = 1;
			else if(i == 0 || i == p->b->num_of_row - 1 || j == 0 || j == p->b->num_of_col - 1)
				p->b->box[i][j]->level = 2;
			else
				p->b->box[i][j]->level = 3;
		}
	p->b->moves = 0;
	p->b->balls = 0;
	for(i = 0; i < 8; i++)
		p->b->color[i] = 0;
	for(i = 1; i <= p->b->num_of_players; i++)
		p->b->color[i] = 1;
	gtk_widget_show_all(p->win);
}

