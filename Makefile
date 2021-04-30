CC = gcc
LIBS = -lraylib -lGL -lpthread -ldl -lrt -lX11 -lm -lglfw
CFLAGS = -Wall

dragon:
	${CC} ${CFLAGS} dragon.c -o dragon ${LIBS}
