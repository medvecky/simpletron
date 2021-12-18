CFLAGS=-g -O2 -Wall -Wextra $(OPTFLAGS)
CC=clang

simpletron: simpletron.o simpletron_io.o simpletron_memory.o simpletron_cpu.o
	$(CC) -o simpletron $(CFLAGS) simpletron.o simpletron_io.o simpletron_memory.o simpletron_cpu.o
simpletron.o: simpletron.c
	$(CC) -c $(CFLAGS)  simpletron.c
simpletron_io.o: simpletron_io.c
	$(CC) -c $(CFLAGS)  simpletron_io.c
simpletron_memory.o: simpletron_memory.c
	$(CC) -c $(CFLAGS)  simpletron_memory.c
simpletron_cpu.o: simpletron_cpu.c
	$(CC) -c $(CFLAGS)  simpletron_cpu.c
clean:
	rm *~ .*~ *.o simpletron
