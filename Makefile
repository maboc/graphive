all : graphive file_test

file_test: file_test.c
	gcc -o file_test file_test.c -ggdb

graphive: graphive.o dll.o config.o logger.o network.o receiver.o base.o data.o parser.o attribute.o output.o
	gcc -o graphive graphive.o dll.o config.o logger.o network.o receiver.o base.o data.o parser.o attribute.o output.o -ggdb -lpthread

graphive.o: graphive.c graphive.h
	gcc -c graphive.c -ggdb

dll.o: dll.c dll.h
	gcc -c dll.c -ggdb

config.o: config.c config.h
	gcc -c config.c -ggdb

logger.o: logger.c logger.h
	gcc -c logger.c -ggdb

network.o: network.c network.h
	gcc -c network.c -ggdb

receiver.o: receiver.c receiver.h
	gcc -c receiver.c -ggdb

base.o: base.c base.h
	gcc -c base.c -ggdb

data.o: data.c data.h
	gcc -c data.c -ggdb

parser.o: parser.c parser.h
	gcc -c parser.c -ggdb

attribute.o: attribute.c attribute.h
	gcc -c attribute.c -ggdb

output.o: output.c output.h
	gcc -c output.c -ggdb

clean:
	rm -f graphive
	rm -f file_test
	rm -f *.o
	rm -f *~ 
