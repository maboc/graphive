graphive : graphive.o logging.o io.o
	gcc -o graphive -lpthread -ggdb graphive.o logging.o io.o

graphive.o : graphive.c graphive.h
	gcc -ggdb -c graphive.c 

logging.o : logging.c logging.h
	gcc -ggdb -c logging.c

io.o : io.c io.h
	gcc -ggdb -c io.c

clean :
	rm *.o
	rm *~

