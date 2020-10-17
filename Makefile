graphive : graphive.o logging.o
	gcc -o graphive -lpthread -ggdb graphive.o logging.o

graphive.o : graphive.c graphive.h
	gcc -ggdb -c graphive.c 

logging.o : logging.c logging.h
	gcc -ggdb -c logging.c

clean :
	rm *~
	rm *.o
