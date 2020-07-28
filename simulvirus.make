SIMULVIRUS_C_FLAGS=-O2 -Wall -Wextra -Waggregate-return -Wcast-align -Wcast-qual -Wconversion -Wformat=2 -Winline -Wlong-long -Wmissing-prototypes -Wmissing-declarations -Wnested-externs -Wno-import -Wpointer-arith -Wredundant-decls -Wshadow -Wstrict-prototypes -Wwrite-strings

simulvirus: simulvirus.o
	gcc -o simulvirus simulvirus.o

simulvirus.o: simulvirus.c simulvirus.make
	gcc -c ${SIMULVIRUS_C_FLAGS} -o simulvirus.o simulvirus.c

clean:
	rm -f simulvirus simulvirus.o
