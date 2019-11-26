
CC=g++
CFLAGS= -I$(IDIR) -fopenmp -std=c++11

IDIR  =include
ODIR  =obj
SDIR  =src
PDIR  =pat

_DEPS = state.h rule.h arguments.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = state.o rule.o arguments.o

_GOLOBJ = gameoflife.o $(_OBJ)
GOLOBJ = $(patsubst %,$(ODIR)/%,$(_GOLOBJ))

_PSOBJ = patterns.o $(_OBJ)
PSOBJ = $(patsubst %,$(ODIR)/%,$(_PSOBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#make: crea todo
all: gameoflife patterns
	

#make: crea gameoflife
gameoflife: $(GOLOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

#crea patterns
patterns: $(PSOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: all, clean

clean:
	rm -f $(ODIR)/*.o gameoflife patterns $(PDIR)/*.pat
	

