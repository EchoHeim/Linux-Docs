main:main.c libfun.so
	gcc main.c libfun.so -o main
libfun.so:fun.o
	gcc -fpic -shared fun.o -o libfun.so
	cp libfun.so /lib
fun.o:fun.c
	gcc -c fun.c
clean:
	rm *so *o main -rf

  
