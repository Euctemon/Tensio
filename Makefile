CC=gcc
CFLAGS=-g -Wall -Wpedantic -std=c23

SRC=source/quadtree.c source/svg.c source/main.c
TEST_SRC=source/quadtree.c test/quadtree_test.c

TARGET=tensio
TEST_TARGET=test_tensio


all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

test: $(TEST_SRC)
	$(CC) $(CFLAGS) -Itest -o $(TEST_TARGET) $(TEST_SRC)

clean:
	rm -f $(TARGET) $(TEST_TARGET)