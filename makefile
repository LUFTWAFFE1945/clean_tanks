all:
	cc -g main.c read_and_save.c komunikacja.c interpretacja.c algorytm2.c mapowanie.c move.c -o explor_tank ../cJSON/cJSON.o -lcurl

test: all
	./explor_tank

memory: all
	valgrind -s ./explor_tank 