#include<gtk/gtk.h>
#include"cr.h"
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>


void savegame(GtkWidget *a, sg *p) {
	int fp;
	fp = open("cr.txt", O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
	write(fp, p->b, sizeof(board));
	int i, j;
	for(i = 0; i < p->b->num_of_row; i++)
		for(j = 0; j < p->b->num_of_col; j++)
			write(fp, p->b->box[i][j], sizeof(square));
	write(fp, p->image, sizeof(p->image));
	close(fp);
}

void sgame(sg *p, buttondata *b[11][23]) {
	int i, j;
	gtk_widget_destroy(p->gr);
	
	p->gr = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(p->win), p->gr);
	for(i = 0; i < p->b->num_of_row; i++)
		for(j = 0; j < p->b->num_of_col; j++) {
			p->img[i][j] = gtk_image_new();
			p->bt[i][j] = gtk_button_new();
			b[i][j]->p = p;
			b[i][j]->s = p->b->box[i][j];
		}
	i = 0;
	j = 0;
	while(i < p->b->num_of_row) {
		if(p->b->box[i][j]->num_of_balls) {
			p->img[i][j] = gtk_image_new_from_file(b[i][j]->p->image[p->b->box[i][j]->kalar][p->b->box[i][j]->num_of_balls - 1]);
		}
		else {
			p->img[i][j] = gtk_image_new_from_file(p->image[0][0]);
		}
		gtk_widget_set_size_request(p->bt[i][j], 70, 90);	
		gtk_button_set_image(GTK_BUTTON(p->bt[i][j]), p->img[i][j]);
		gtk_grid_attach(GTK_GRID(p->gr), p->bt[i][j], j * 60, i * 90, 60, 90);
		g_signal_connect(p->bt[i][j], "clicked", G_CALLBACK(game), b[i][j]);
		j++;
		if(j == p->b->num_of_col) {
			j = 0;
			i++;
		}
	}
	p->exbt[0] = gtk_button_new_with_label("NEW GAME");
        p->exbt[1] = gtk_button_new_with_label("SAVE");
        p->exbt[2] = gtk_button_new_with_label("RESTART");
        p->exbt[5] = gtk_button_new_with_label("QUIT");
        p->exbt[3] = gtk_button_new_with_label("UNDO");
	p->exbt[4] = gtk_button_new_with_label("HOME");
	p->exbt[6] = gtk_button_new_with_label("TURN");
        GtkWidget *k;
        k = gtk_label_new("                        ");
        gtk_grid_attach(GTK_GRID(p->gr), k, p->b->num_of_col * 60, 0, 100, 25);
        p->b->restart = 1;
        for(i = 0; i <= 5; i++)
                gtk_grid_attach(GTK_GRID(p->gr), p->exbt[i], (p->b->num_of_col * 60) + 100, i * 50, 100, 45);
	gtk_grid_attach(GTK_GRID(p->gr), p->exbt[6], (p->b->num_of_col * 60  + 100), 400, 100, 45);
	p->im = gtk_image_new_from_file(p->image[p->b->clr][0]);
	gtk_button_set_image(GTK_BUTTON(p->exbt[6]), p->im);
        g_signal_connect(p->exbt[0], "clicked", G_CALLBACK(setboard), p);
        g_signal_connect(p->exbt[2], "clicked", G_CALLBACK(setgame), p);
        g_signal_connect(p->exbt[1], "clicked", G_CALLBACK(savegame), p);
        g_signal_connect(p->exbt[5], "clicked", G_CALLBACK(gtk_main_quit), NULL);
        g_signal_connect(p->exbt[3], "clicked", G_CALLBACK(undo), p);
	g_signal_connect(p->exbt[4], "clicked", G_CALLBACK(again), p);
}

int setsavedgame(GtkWidget *a, sg *p) {
	int fp;
	fp = open("cr.txt", O_RDONLY);
	if(fp == -1)
		return 0;
	read(fp, p->b, sizeof(board));
	int i, j;
	square s;
	for(i = 0; i < p->b->num_of_row; i++) {
		for(j = 0; j < p->b->num_of_col; j++) {
			read(fp, &s, sizeof(square));
			p->b->box[i][j] = malloc(sizeof(square));
			p->b->box[i][j]->num_of_balls = s.num_of_balls;
			p->b->box[i][j]->level = s.level;
			p->b->box[i][j]->kalar = s.kalar;
			p->b->box[i][j]->row = s.row;
			p->b->box[i][j]->column = s.column;
		}
	}
	for(i = 0; i <= p->b->num_of_players; i++)
		for(j = 0; j < 3; j++)
			read(fp, p->image[i][j], sizeof(p->image[0][0]));
	close(fp);
	buttondata *b[11][23];
	for(i = 0; i < p->b->num_of_row; i++)
		for(j = 0; j < p->b->num_of_col; j++)
			b[i][j] = malloc(sizeof(buttondata));
	sgame(p, b);
	p->b->restart = 1;
	p->d = malloc(sizeof(sg));
	p->d->b = malloc(sizeof(board));
	p->d->b->num_of_players = p->b->num_of_players;
	p->d->b->clr = p->b->clr;
	p->d->b->balls = p->b->balls;
	p->d->b->moves = p->b->moves;
	p->d->b->m = p->b->m;
	p->d->b->num_of_row = p->b->num_of_row;
	p->d->b->num_of_col = p->b->num_of_col;
	p->d->d = NULL;
	for(i = 0; i < 8; i++)
		for(j = 0; j < 3; j++)
			strcpy(p->d->image[i][j], p->image[i][j]);

	for(i = 0; i < p->b->num_of_row; i++)
		for(j = 0; j < p->b->num_of_col; j++) {
			p->d->b->box[i][j] = malloc(sizeof(square));
			p->d->b->box[i][j]->num_of_balls = p->b->box[i][j]->num_of_balls;
			p->d->b->box[i][j]->kalar = p->b->box[i][j]->kalar;

		}

	gtk_widget_show_all(p->win);
	return 0;
}

