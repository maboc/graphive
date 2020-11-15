graphive : graphive.o logging.o io.o dll.o startup_creation.o base.o attribute.o node.o listener.o handler.o output.o
	gcc -o graphive -lpthread -ggdb graphive.o logging.o io.o dll.o startup_creation.o base.o attribute.o node.o listener.o handler.o output.o

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

node.o : node.c node.h
	gcc -ggdb -c node.c

listener.o : listener.c listener.h
	gcc -ggdb -c listener.c

handler.o : handler.c handler.h
	gcc -ggdb -c handler.c

output.o : output.h output.c
	gcc -ggdb -c output.c
clean :
	rm *.o
	rm *~

remove : rmdat rmlog

rmdat :
	rm *.dat

rmlog :
	rm *.log
