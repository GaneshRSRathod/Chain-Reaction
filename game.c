#include<stdio.h>
#include<gtk/gtk.h>
#include"cr.h"
#include<stdlib.h>

void game(GtkWidget *k, buttondata *b) {
	if(b->s->kalar && b->s->kalar != b->p->b->clr)
		return;
	int i = 0, j = 0;
	sg *ka;
	ka = malloc(sizeof(sg));
	ka->b = malloc(sizeof(board));
	ka->b->num_of_players = b->p->b->num_of_players;
	ka->b->clr = b->p->b->clr;
	ka->b->balls = b->p->b->balls;
	ka->b->moves = b->p->b->moves;
	ka->b->m = b->p->b->m;
	for(i = 0; i < 8; i++)
		for(j = 0; j < 3; j++)
			strcpy(ka->image[i][j], b->p->image[i][j]);

	for(i = 0; i < b->p->b->num_of_row; i++)
		for(j = 0; j < b->p->b->num_of_col; j++) {
			ka->b->box[i][j] = malloc(sizeof(square));
			ka->b->box[i][j]->num_of_balls = b->p->b->box[i][j]->num_of_balls;
			ka->b->box[i][j]->kalar = b->p->b->box[i][j]->kalar;
	}
	if(b->p->d)
		ka->d = b->p->d;
	b->p->d = ka;
	b->p->b->moves = 0;
	b->s->num_of_balls = b->s->num_of_balls + 1;
	if(b->s->num_of_balls > b->s->level) {
		b->s->num_of_balls = 0;
		b->s->kalar = 0;
		b->p->img[b->s->row][b->s->column] = gtk_image_new_from_file(b->p->image[b->s->kalar][b->s->num_of_balls]);
		gtk_button_set_image(GTK_BUTTON(b->p->bt[b->s->row][b->s->column]), b->p->img[b->s->row][b->s->column]);
		b->p->b->move_play = 0;
		nextbt(b);
	}
	else {
		b->s->kalar = b->p->b->clr;
		b->p->img[b->s->row][b->s->column] = gtk_image_new_from_file(b->p->image[b->p->b->clr][b->s->num_of_balls - 1]);
		gtk_button_set_image(GTK_BUTTON(b->p->bt[b->s->row][b->s->column]), b->p->img[b->s->row][b->s->column]);
	}
	int l[10], u, v;
	for(i = 0; i < 10; i++)
		l[i] = 0;
	for(i = 0; i < b->p->b->num_of_row;  i++)
		for(j = 0; j < b->p->b->num_of_col; j++) {
			l[b->p->b->box[i][j]->kalar] = l[b->p->b->box[i][j]->kalar] + 1;
		}
	if(b->p->b->m) {
		for(i = b->p->b->num_of_players; i >= 1; i--) {
			if(l[i] == 0) {
				for(j = i; j < b->p->b->num_of_players; j++) {
					strcpy(b->p->image[j][0], b->p->image[j + 1][0]);
					strcpy(b->p->image[j][1], b->p->image[j + 1][1]);
					strcpy(b->p->image[j][2], b->p->image[j + 1][2]);
				}
				for(u = 0; u < b->p->b->num_of_row; u++)
					for(v = 0; v < b->p->b->num_of_col; v++)
						if(b->p->b->box[u][v]->kalar > i)
							(b->p->b->box[u][v]->kalar)--;
							
				if(i < b->p->b->clr)
					b->p->b->clr = b->p->b->clr - 1;
				b->p->b->color[i] = 0;
				b->p->b->num_of_players = b->p->b->num_of_players - 1;
			}
		}
		if(b->p->b->num_of_players == 1) {
			b->p->im2 = gtk_image_new_from_file(b->p->image[1][0]);
			b->p->exbt[7] = gtk_button_new_with_label("Player Won");
			gtk_button_set_image(GTK_BUTTON(b->p->exbt[7]), b->p->im2);
			gtk_grid_attach(GTK_GRID(b->p->gr), b->p->exbt[7], (b->p->b->num_of_col * 60) + 50 , 500, 150, 50);
			int nm, mn;
			for(nm = 0; nm < b->p->b->num_of_row; nm++)
				for(mn = 0; mn < b->p->b->num_of_col; mn++)
					gtk_widget_set_sensitive(b->p->bt[nm][mn], 0);
			gtk_widget_set_sensitive(b->p->exbt[1], 0);
			gtk_widget_set_sensitive(b->p->exbt[3], 0);
			gtk_widget_show_all(b->p->win);
		}
	}
				
	b->p->b->clr = b->p->b->clr + 1;
	if(b->p->b->num_of_players < b->p->b->clr) {
		b->p->b->m = 1;
		b->p->b->clr = 1;
	}
	b->p->im = gtk_image_new_from_file(b->p->image[b->p->b->clr][0]);
	gtk_button_set_image(GTK_BUTTON(b->p->exbt[6]), b->p->im);;
	(b->p->b->balls)++;
	return;
}

int checkrow(int i, board *b) {
	if(i >= 0 && i <= b->num_of_row - 1)
		return 1;
	return 0;
}
int checkcol(int i, board *b) {
	if(i >= 0 && i <= b->num_of_col - 1)
		return 1;
	return 0;
}

void nextbt(buttondata *b) {
	if(checkrow(b->s->row + 1, b->p->b)) {
		b->s = b->p->b->box[b->s->row + 1][b->s->column];
		cogame(b);
		b->s = b->p->b->box[b->s->row - 1][b->s->column];
	}
	if(checkrow(b->s->row - 1, b->p->b)) {
                b->s = b->p->b->box[b->s->row - 1][b->s->column];
                cogame(b);
		b->s = b->p->b->box[b->s->row + 1][b->s->column];
        }
	if(checkcol(b->s->column + 1, b->p->b)) {
                b->s = b->p->b->box[b->s->row][b->s->column + 1];
                cogame(b);
		b->s = b->p->b->box[b->s->row][b->s->column - 1];
        }
	if(checkcol(b->s->column - 1, b->p->b)) {
                b->s = b->p->b->box[b->s->row][b->s->column - 1];
                cogame(b);
		b->s = b->p->b->box[b->s->row][b->s->column + 1];
        }
}

void cogame(buttondata *b) {
	b->s->num_of_balls = b->s->num_of_balls + 1;
	if(b->s->num_of_balls > b->s->level) {
		if(b->p->b->move_play > b->p->b->num_of_row * b->p->b->num_of_col) {
			return;
		}
		b->p->b->move_play++;
		(b->p->b->moves)++;
		b->s->num_of_balls = 0;
		b->s->kalar = 0;
		b->p->img[b->s->row][b->s->column] = gtk_image_new_from_file(b->p->image[b->s->kalar][b->s->num_of_balls]);
		gtk_button_set_image(GTK_BUTTON(b->p->bt[b->s->row][b->s->column]), b->p->img[b->s->row][b->s->column]);
		nextbt(b);
	}
	else {
		b->s->kalar = b->p->b->clr;
		b->p->img[b->s->row][b->s->column] = gtk_image_new_from_file(b->p->image[b->p->b->clr][b->s->num_of_balls - 1]);
		gtk_button_set_image(GTK_BUTTON(b->p->bt[b->s->row][b->s->column]), b->p->img[b->s->row][b->s->column]);
	}
}
