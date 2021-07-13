simpletron: simpletron.o simpletron_io.o simpletron_memory.o
	clang -o simpletron simpletron.o simpletron_io.o simpletron_memory.o
simpletron.o: simpletron.c
	clang -c simpletron.c
simpletron_io.o: simpletron_io.c
	clang -c simpletron_io.c
simpletron_memory.o: simpletron_memory.c
	clang -c simpletron_memory.c
clean:
	rm *~ .*~ *.o simpletron
