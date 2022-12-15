make:main.c libfun1.a libfun2.so
	gcc -o main1 main.c -L. -lfun1
	gcc -o main2 main.c -L. -lfun2
	cp libfun2.so /lib64/
libfun1.a:add.o sub.o mul.o div.o
	ar -rc libfun1.a Add.o Sub.o Mul.o Div.o
libfun2.so:add.c sub.c mul.c div.c
	gcc -fpic -shared -o libfun2.so -L. add.c sub.c mul.c div.c
Add.o:Add.c
	gcc -c Add.c
Sub.o:Sub.c
	gcc -c Sub.c
Mul.o:Mul.c
	gcc -c Mul.c
Div.o:Div.c
	gcc -c Div.c
clean:
	rm *.o *.so *.out main1 main2 *.a -f
