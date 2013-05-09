CCFLAGS += -ggdb -static -I /udd/chikhi/paired/judy-1.0.5/include -L /udd/chikhi/paired/judy-1.0.5/lib
LIBS = -lJudy 

all: Judy1DupCheck Judy1OpCheck

Judy1DupCheck: Judy1Dup.c Judy1DupCheck.c
	$(CC) $(CCFLAGS) -o $@ $^ $(LIBS)

Judy1OpCheck: Judy1Op.c Judy1OpCheck.c
	$(CC) $(CCFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f Judy1DupCheck Judy1OpCheck *.o 
