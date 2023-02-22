CHARMC      = $(CHARMPP_ROOT)/bin/charmc
OPTS        = -g -O2

OBJS		= primality.o
OBJS_DECL	= primality.decl.h

all: primality

primality: $(OBJS) $(OBJS_DECL)
	$(CHARMC) -o primality $(OBJS) -language charm++ $(OPTS)

primality.decl.h primality.def.h: primality.ci
	$(CHARMC) primality.ci

primality.o: primality.cpp primality.h primality.decl.h primality.def.h
	$(CHARMC) $(OPTS) -o  primality.o primality.cpp

clean:
	rm -f *.decl.h *.def.h *.o charmrun primality