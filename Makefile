graphive : graphive.o logging.o io.o dll.o startup_creation.o base.o attribute.o
	gcc -o graphive -lpthread -ggdb graphive.o logging.o io.o dll.o startup_creation.o base.o attribute.o

graphive.o : graphive.c graphive.h
	gcc -ggdb -c graphive.c 

logging.o : logging.c logging.h
	gcc -ggdb -c logging.c

io.o : io.c io.h
	gcc -ggdb -c io.c

dll.o : dll.h dll.c
	gcc -ggdb -c dll.c

startup_creation.o : startup_creation.c startup_creation.h
	gcc -ggdb -c startup_creation.c

base.o : base.c base.h
	gcc -ggdb -c base.c

attribute.o : attribute.c attribute.h
	gcc -ggdb -c attribute.c

clean :
	rm *.o
	rm *~

remove : rmdat rmlog

rmdat :
	rm *.dat

rmlog :
	rm *.log
