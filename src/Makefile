
CFLAGS  = -g -Wall

a.out: test.o libcosmos.a
	cc test.o -L. -lcosmos -lm

test.o: test.c vXc.h

libcosmos.a: vXc.o
	ar -rcs libcosmos.a vXc.o
	
v0c.o: vXc.c vXc.h -lm
 
install:
	cp libcosmos.a lib
	cp vc_defs.h include
	cp vXc.h include

clean:
	rm a.out test.o libcosmos.a vXc.o
