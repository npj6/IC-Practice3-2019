
CC=g++
CFLAGS= -I$(IDIR) -fopenmp -std=c++11
PFLAGS = -D PARALLEL

PARALLEL=NO

IDIR  =include
ODIR  =obj
SDIR  =src
PDIR  =pat

_DEPS = state.h basicRule.h arguments.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_PARALLELOBJ = state.o basicRule.o
PARALLELOBJ = $(patsubst %,$(ODIR)/%,$(_PARALLELOBJ))

_OBJ = state.o basicRule.o arguments.o

_GOLOBJ = gameoflife.o $(_OBJ)
GOLOBJ = $(patsubst %,$(ODIR)/%,$(_GOLOBJ))

_PSOBJ = patterns.o $(_OBJ)
PSOBJ = $(patsubst %,$(ODIR)/%,$(_PSOBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
ifeq ($(PARALLEL),NO)
	$(CC) -c -o $@ $< $(CFLAGS)
else
	$(CC) -c -o $@ $< $(CFLAGS) $(PFLAGS)
endif

#make: crea todo
all: clean_parallel gameoflife patterns

#crea gameoflife
gameoflife: $(GOLOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

#crea patterns
patterns: $(PSOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: all, clean, clean_parallel, clean_patterns

clean:
	rm -f $(ODIR)/*.o gameoflife patterns $(PDIR)/*.pat patterns_report gameoflife_report

clean_parallel:
	rm -f $(PARALLELOBJ)

clean_patterns:
	rm -f $(PDIR)/*.pat
