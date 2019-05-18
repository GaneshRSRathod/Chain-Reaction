project:cr.o widgets.o setgame.o game.o image.o save.o undo.o
	cc `pkg-config --cflags gtk+-3.0` cr.o widgets.o setgame.o save.o game.o image.o undo.o `pkg-config --libs gtk+-3.0` -o project -Wall
save.o:save.c cr.h
	cc -c `pkg-config --cflags gtk+-3.0` save.c `pkg-config --libs gtk+-3.0` -Wall
cr.o:cr.c cr.h
	cc -c `pkg-config --cflags gtk+-3.0` cr.c `pkg-config --libs gtk+-3.0` -Wall
widgets.o:widgets.c cr.h
	cc -c `pkg-config --cflags gtk+-3.0` widgets.c `pkg-config --libs gtk+-3.0` -Wall
setgame.o:setgame.c cr.h
	cc -c `pkg-config --cflags gtk+-3.0` setgame.c `pkg-config --libs gtk+-3.0` -Wall
image.o: image.c cr.h
	cc -c `pkg-config --cflags gtk+-3.0` image.c `pkg-config --libs gtk+-3.0` -Wall
game.o:game.c cr.h
	cc -c `pkg-config --cflags gtk+-3.0` game.c `pkg-config --libs gtk+-3.0` -Wall
undo.o:undo.c cr.h
	cc -c `pkg-config --cflags gtk+-3.0` undo.c `pkg-config --libs gtk+-3.0` -Wall

