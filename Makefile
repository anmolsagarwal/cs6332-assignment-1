CC=gcc
CFLAGS=-g

all: part0 part1 part2 part3 part4 part5

part0: driver0.c memsets.c
	$(CC) $(CFLAGS) -o $@  $<
	@echo "===" $@ "==="
	./$@

part1: driver1.c memsets.c 
	$(CC) -c $^
	$(CC) driver1.o memsets.o -o $@
	@echo "==========="

part2: driver1.c memsets.c
	$(CC) -c $^
	ar -crs libmemsets.a memsets.o
	$(CC) driver1.o libmemsets.a -o $@
	./$@
	@echo "==========="
	@echo ""

part3: driver1.c memsets.c
	$(CC) -c $^
	$(CC) -shared -o libmemsets.so memsets.o
	$(CC) -o $@ $< -L. -l memsets
	export LD_LIBRARY_PATH=".";./$@	

	@echo "==========="
	@echo ""

part4: driver4.c part3
	$(CC) $< -ldl -o $@
	./$@
	@echo "==========="
	@echo ""

part5: part3
	$(CC) -c ./memset1.c
	$(CC) -shared -o memset1.so memset1.o
	export LD_LIBRARY_PATH="."; LD_PRELOAD=./memset1.so ./$<

	@echo "==========="
	@echo ""

clean:
	rm -f part? *.a *.o *.so

