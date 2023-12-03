CC=mpic++
CFLAGS=-I/usr/lib/x86_64-linux-gnu/openmpi/include
LIBS=       
DEPS=       
OBJ = mpiprime.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test1: $(OBJ)
	mpirun -np 3 ./mpiprime 32
	
test2: $(OBJ)
	mpirun -np 3 ./mpiruncyclic 32
	
test3: $(OBJ)
	mpirun -np 3 ./mpiprimecyclic 32
	
test4: $(OBJ)
	mpirun -np 3 ./primenum 32
	
test5: $(OBJ)
	./prime 32
	
clean:
	rm -f *.o *~ core

