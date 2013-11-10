MATRIX_SRC = Matrix.c \
						 Matrix.tc\
						 Matrix.th\
						 Matrix.h


OBJECTS = Matrix.o

export CC
export LD
export CFLAGS
export LDFLAGS
 
all: $(OBJECTS)
	 
Matrix.o: $(MATRIX_SRC)
	$(CC) $(CFLAGS) Matrix.c -o Matrix.o

.PHONY: clean test


test:
	$(MAKE) -C ./test


clean:
	rm -rf $(OBJECTS)
	$(MAKE) clean -C ./test
