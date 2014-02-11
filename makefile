
FLAGS = -pthread -g 


all: jigsaw

jigsaw: 
	gcc $(FLAGS) -o jigsaw effort.c helper.c

clean:
	rm -rf *o jigsaw
