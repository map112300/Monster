all : monster

monster : monster.c 
	gcc -g -Wall -Werror -Wvla -fsanitize=address monster.c -o monster

clean : 
	rm -rf monster 