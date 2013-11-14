MATRIX_SRC = Matrix.c \
						 Matrix.tc\
						 Matrix.th\
						 Matrix.h


OBJECTS = Matrix.o

CC := clang
CFLAGS := -c -g -Wall

all: $(OBJECTS)
	 
Matrix.o: $(MATRIX_SRC)
	$(CC) $(CFLAGS) Matrix.c -o Matrix.o

.PHONY: clean test


test:
	$(MAKE) -C ./test


clean:
	rm -rf $(OBJECTS)
	$(MAKE) clean -C ./test
