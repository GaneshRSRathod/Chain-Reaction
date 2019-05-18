#include<gtk/gtk.h>

typedef struct square {
	int num_of_balls;
	int level;
	int kalar;
	int row;
	int column;
} square;

typedef struct board {
	int num_of_players;
	int num_of_players_static;
	int num_of_row;
	int num_of_col;
	struct square *box[11][23];
	int color[8];
	int clr;
	int balls;
	int moves;
	int move_play;
	int restart;
	int m;
} board;

typedef struct sg {
	GtkWidget *bt[11][23];
	GtkWidget *exbt[10];
	GtkWidget *gr;
	GtkWidget *im, *im2;
	GtkWidget *ib, *ic;
	GtkWidget *win;
	GtkWidget *win2;
	GtkWidget *lab;
	GtkWidget *img[11][23];
	struct board *b;
	struct sg *d;
	char image[8][3][20];
	int i;
	int j;
}sg;

typedef struct buttondata{
	struct sg *p;
	struct square *s;
}buttondata;
void initgtkwidgets(GtkWidget *but, sg *p);
void setboard(GtkWidget *b, sg *p);
void setgame(GtkWidget *but, sg *p);
void initimage(sg *p);
void game(GtkWidget *k, buttondata *b);
void cogame(buttondata *b);
void nextbt(buttondata *b);
void savegame(GtkWidget *a, sg *p);
int setsavedgame(GtkWidget *a, sg *p);
void sgame(sg *p, buttondata *b[11][23]);
void gam(GtkWidget *k, buttondata *b);
void undo(GtkWidget *n, sg *p);
void tgame(GtkWidget *but, sg *p);
void again(GtkWidget *but, sg *p);
