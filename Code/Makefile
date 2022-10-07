CFLAGS=-g -W -Wall

OBJECT=object.o character.o main.o clos.o string.o package.o symbol.o\
       cons.o float.o integer.o ratio.o stream.o assert.o print.o\
       control.o function.o substandard-reader.o

all: $(OBJECT)
	gcc -g -o bocl $(OBJECT) -lgmp -lm

clean:
	rm -f bocl $(OBJECT)

object.o: object.h
character.o: character.h symbol.h character.c
string.o: string.h symbol.h string.c character.h
package.o: package.h symbol.h package.c
symbol.o: symbol.h symbol.c package.h
main.o: object.h character.h
cons.o: object.h symbol.h cons.h
float.o: object.h symbol.h float.h
integer.o: object.h symbol.h integer.h
ratio.o: object.h symbol.h ratio.h
stream.o: object.h symbol.h stream.h
assert.o: object.h symbol.h assert.h
print.o: object.h symbol.h character.h string.h cons.h integer.h print.h
substandard-reader.o: object.h package.h symbol.h cons.h integer.h substandard-reader.h
