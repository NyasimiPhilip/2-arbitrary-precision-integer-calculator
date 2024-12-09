CC = gcc
CFLAGS = -Wall -Wextra -I./include
LDFLAGS = -L.
LDLIBS = -lcalculator

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)
TEST_SRCS = $(wildcard tests/*.c)
TEST_BINS = $(TEST_SRCS:.c=.bin)

.PHONY: all clean test

all: calculator $(TEST_BINS)

libcalculator.a: $(OBJS)
	ar rcs $@ $^

calculator: src/main.c libcalculator.a
	$(CC) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

%.bin: %.c libcalculator.a
	$(CC) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

test: $(TEST_BINS)
	for test in $(TEST_BINS); do ./$$test; done

clean:
	rm -f $(OBJS) calculator libcalculator.a $(TEST_BINS) *.o