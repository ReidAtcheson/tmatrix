#CUnit directories
TESTINC:=/usr/local/include/
TESTBIN:=/usr/local/lib/

all : RUN

RUN : test_matrix
	./test_matrix

test_matrix : test_matrix.o
	$(LD) $(LDFLAGS) test_matrix.o -L$(TESTBIN) -lCUnit -lhatdg -o test_matrix

test_matrix.o : test_matrix.c
	$(CC) $(CFLAGS) -I$(TESTINC) test_matrix.c -o test_matrix.o

.PHONY: clean all


clean:
	rm -rf ./*.o
	rm -rf ./test_matrix
