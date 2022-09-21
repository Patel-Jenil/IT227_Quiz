SRCDIR = ${HOME}/Proj/src
IDIR =${HOME}/Proj/include
CC=gcc
CFLAGS=-I$(IDIR)
ODIR=${HOME}/Proj/src/obj
LDIR =${HOME}/lib
_LIBS=libstatic.a
LIBS=$(patsubst %,$(LDIR)/%,$(_LIBS))

_DEPS=202101074_header.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = 202101074_is_digit.o 202101074_is_prime.o 202101074_main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

BUILDDIR = ${HOME}/Proj ${HOME}/Proj/bin ${HOME}/Proj/include ${HOME}/Proj/lib
# COPY_FILES = ./*.c

all: $(BUILDDIR) $(SRCDIR) copy $(ODIR)/202101074_main.o $(ODIR)/202101074_is_prime.o $(ODIR)/202101074_is_digit.o $(SRCDIR)/202101074_main

$(BUILDDIR):
	mkdir -p $@

$(SRCDIR):
	mkdir -p $@; mkdir -p $(ODIR); cp -fv ./*.c $@;

copy:
	cp -f ./*.h $(DEPS)

$(ODIR)/202101074_main.o: $(SRCDIR)/202101074_main.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/202101074_is_prime.o: $(SRCDIR)/202101074_is_prime.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/202101074_is_digit.o: $(SRCDIR)/202101074_is_digit.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# $(LDIR)/libstatic.a: $(ODIR)/202101074_is_prime.o $(ODIR)/202101074_is_digit.o
# 	ar crs $@ $(ODIR)/202101074_is_prime.o $(ODIR)/202101074_is_digit.o

$(SRCDIR)/202101074_main: $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS) 

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~