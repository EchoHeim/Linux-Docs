main:main.c libfun.a
	gcc main.c libfun.a -o main
libfun.a:fun.o
	ar -rc libfun.a fun.o
fun.o:fun.c
	gcc -c fun.c
clean:
	rm *.a *.o main -rf
