# Makefile - Alternative Build System
#
# Provides manual compilation options for systems without CMake.
# Supports building the library, executable, and tests.

CC = gcc
CFLAGS = -Wall -Wextra -I./include
LDFLAGS = -L.
LDLIBS = -lcalculator

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)
TEST_SRCS = $(wildcard tests/*.c)
TEST_BINS = $(TEST_SRCS:.c=.bin)

.PHONY: all clean test

# Build everything
all: calculator $(TEST_BINS)

# Create static library
libcalculator.a: $(OBJS)
	ar rcs $@ $^

# Build main executable
calculator: src/main.c libcalculator.a
	$(CC) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

# Build test executables
%.bin: %.c libcalculator.a
	$(CC) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

# Run tests
test: $(TEST_BINS)
	for test in $(TEST_BINS); do ./$$test; done

# Clean build artifacts
clean:
	rm -f $(OBJS) calculator libcalculator.a $(TEST_BINS) *.o