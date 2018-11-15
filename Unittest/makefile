# Based on:
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

CC = gcc
LIBRARIES = -llibcunit
BUILDDIR = build
INCLUDE = -I../include -Icunit_headers
CFLAGS = $(INCLUDE) $(LIBRARIES) -Wall

null:all

#=======================================================================

SOURCE_RING = ../source/ring_buffer.c ring_test.c
BINNAME_RING = ring_test
BINRUN_RING = $(addsuffix _run, $(BINNAME_RING))
_RING_DEPS = ring_buffer.h
RING_DEPS = $(patsubst %, $(INCLUDE)/%, $(_RING_DEPS))
_RING_OBJ = ring_buffer.o ring_buffer_test.o
RING_OBJ = $(patsubst %, $(BUILDDIR)/%, $(_RING_OBJ))

$(BUILDDIR)/%.o: $(SOURCE_RING) $(RING_DEPS)
	mkdir -p $(BUILDDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINNAME_RING): $(SOURCE_RING)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BINRUN_RING): $(BINNAME_RING)
	./$(BINNAME_RING)

#=======================================================================

SOURCE_CHAR = ../source/char_counter.c char_test.c
BINNAME_CHAR = char_test
BINRUN_CHAR = $(addsuffix _run, $(BINNAME_CHAR))
_CHAR_DEPS = char_counter.h
CHAR_DEPS = $(patsubst %, $(INCLUDE)/%, $(_CHAR_DEPS))
_CHAR_OBJ = char_counter.o char_test.o
CHAR_OBJ = $(patsubst %, $(BUILDDIR)/%, $(_CHAR_OBJ))

$(BUILDDIR)/%.o: $(SOURCE_CHAR) $(CHAR_DEPS)
	mkdir -p $(BUILDDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINNAME_CHAR): $(SOURCE_CHAR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BINRUN_CHAR): $(BINNAME_CHAR)
	./$(BINNAME_CHAR)

#=======================================================================

SOURCE_OUTPUT = ../source/output_generator.c output_test.c ../source/ring_buffer.c ../source/char_counter.c
BINNAME_OUTPUT = output_test
BINRUN_OUTPUT = $(addsuffix _run, $(BINNAME_OUTPUT))
_OUTPUT_DEPS = output_generator.h ring_buffer.h char_counter.h
OUTPUT_DEPS = $(patsubst %, $(INCLUDE)/%, $(_OUTPUT_DEPS))
_OUTPUT_OBJ = output_generator.o output_test.o ring_buffer.o char_counter.o
OUTPUT_OBJ = $(patsubst %, $(BUILDDIR)/%, $(_OUTPUT_OBJ))

$(BUILDDIR)/%.o: $(SOURCE_OUTPUT) $(OUTPUT_DEPS)
	mkdir -p $(BUILDDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINNAME_OUTPUT): $(SOURCE_OUTPUT)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BINRUN_OUTPUT): $(BINNAME_OUTPUT)
	./$(BINNAME_OUTPUT)

#=======================================================================

all: $(BINNAME_RING) $(BINNAME_CHAR) $(BINNAME_OUTPUT)
	./$(BINNAME_RING)
	./$(BINNAME_CHAR)
	./$(BINNAME_OUTPUT)

.PHONY: clean

clean:
	rm -f $(BUILDDIR)/*.o *~ core $(INCDIR)/*~ 
	rm $(BINNAME_RING)
	rm $(BINNAME_CHAR)
	rm $(BINNAME_OUTPUT)