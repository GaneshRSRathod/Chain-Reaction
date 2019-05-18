#include"cr.h"
#include<gtk/gtk.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>

void initimage(sg *p) {
	int i = 0, fp, j = 0, k = 0;
	char st[8][3][20], c;
	fp = open("readimage.txt", O_RDONLY);
	while(read(fp, &c, 1)) {
		if(c == 10) {
			st[i][0][j] = '\0';
			i++;
			j = 0;
		}
		else {
			st[i][0][j] = c;
			j++;
		}
	}
	close(fp);
	int l;
	for(i = 0; i < 3; i++) {
		strcpy(p->image[0][i], st[0][i]);
	}
	for(i = 1; i <= p->b->num_of_players; i++) {
		for(j = 2; j >= 0 ; j--) {
			l = strlen(st[i][0]);
			for(k = l; k >= 0; k--)
				st[i][j][k + 1] = st[i][0][k];
			st[i][j][0] = j + '1';
			strcpy(p->image[i][j], st[i][j]);
		}
	}
	
}

