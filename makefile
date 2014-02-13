
FLAGS = -pthread -g 


all: jigsaw

jigsaw: 
	gcc $(FLAGS) -o jigsaw puzzler.c helper.c

clean:
	rm -rf *o jigsaw
