CC = g++

CFLAGS = -Wall -o

NAME = Onegin

all: ccomp cex

ccomp:
	$(CC) $(CFLAGS) $(NAME) main.cpp

cex:
	./$(NAME)
