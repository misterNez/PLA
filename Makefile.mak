CC	= g++
CFLAGS	= -g

PROG	= PLA
OBJ1	= PLA.o

.SUFFIXES: .c .o

$(PROG):	$(OBJ1)
	$(CC) $(CFLAGS) -o $@ $(OBJ1)

.c.o:
	$(CC) $(CFLAGS) -c $(INCLDIRS) $<

clean:
	/bin/rm -f *.o core *.i *.s $(PROG)
