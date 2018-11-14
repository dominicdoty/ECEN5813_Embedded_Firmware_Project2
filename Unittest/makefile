# Based on:
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

CC = gcc
INCLUDE = -I../include -Icunit_headers
LIBRARIES = -llibcunit
SOURCE = ../source/ring_buffer.c unittest.c
CFLAGS = $(INCLUDE) $(LIBRARIES) -Wall
BINNAME = ring_test
BUILDDIR = build


_DEPS = ring_buffer.h
DEPS = $(patsubst %, $(INCLUDE)/%, $(_DEPS))

_OBJ = ring_buffer.o ring_buffer_test.o
OBJ = $(patsubst %, $(BUILDDIR)/%, $(_OBJ))

$(BUILDDIR)/%.o: $(SOURCE) $(DEPS)
	mkdir -p $(BUILDDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINNAME): $(SOURCE)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

test: $(BINNAME)
	./$(BINNAME)

.PHONY: clean

clean:
	rm -f $(BUILDDIR)/*.o *~ core $(INCDIR)/*~ 
	rm $(BINNAME)
