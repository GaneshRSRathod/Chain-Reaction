
#include<gtk/gtk.h>
#include"cr.h"
void undo(GtkWidget *n, sg *p) {
	int i, j;
	if(p->b->balls == 0)
		return;
	sg *b[2];
	b[0] = p->d;
	b[1] = p;
	for(i = 0; i < p->b->num_of_row; i++) {
		for(j = 0; j < p->b->num_of_col; j++) {
			b[1]->b->box[i][j]->num_of_balls = b[0]->b->box[i][j]->num_of_balls;
			b[1]->b->box[i][j]->kalar = b[0]->b->box[i][j]->kalar;
		}
	}
	b[1]->b->num_of_players = b[0]->b->num_of_players;
	b[1]->b->clr = b[0]->b->clr;
	b[1]->b->balls = b[0]->b->balls;
	b[1]->b->moves = b[0]->b->moves;
	b[1]->b->m = b[0]->b->m;
	for(i = 0; i < 8; i++)
		for(j = 0; j < 3; j++)
			strcpy(b[1]->image[i][j], b[0]->image[i][j]);
	for(i = 0; i < b[1]->b->num_of_row; i++)
		for(j = 0; j < b[1]->b->num_of_col; j++) {
//			gtk_widget_destroy(b[1]->img[i][j]); 
			if(b[1]->b->box[i][j]->num_of_balls)
				b[1]->img[i][j] = gtk_image_new_from_file(b[1]->image[b[1]->b->box[i][j]->kalar][b[1]->b->box[i][j]->num_of_balls - 1]);
			else
				b[1]->img[i][j] = gtk_image_new_from_file(b[1]->image[0][0]);
			gtk_button_set_image(GTK_BUTTON(b[1]->bt[i][j]), b[1]->img[i][j]);
	}
	if(p->d->d) {
		sg *t;
		t = p->d;
		p->d = p->d->d;
		free(t);
	}
	p->im = gtk_image_new_from_file(p->image[p->b->clr][0]);
	gtk_button_set_image(GTK_BUTTON(p->exbt[6]),  p->im);
	gtk_widget_show_all(b[1]->win);
}
