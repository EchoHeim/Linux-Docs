main:main.o
	gcc main.o -o main
main.o:main.s
	as main.s -o main.o
main.s:main.i
	gcc -S main.i -o main.s
main.i:main.c
	gcc -E main.c -o main.i
clean:
	rm main.i main.s main.o -rf
