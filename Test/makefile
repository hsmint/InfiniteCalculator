CC      =  gcc-9
CFLAGS  =
EXEC    =  a.out
INCLS   =  
LIBS    = 

OBJS    =  main.o func.o

$(EXEC): $(OBJS)
	@echo "linking ..."
	@$(CC) -o $(EXEC)  $(OBJS)  $(LIBS)

$(OBJS): cal_fun.h
	$(CC) $(INCLS)  -c  $*.c

relink:
	@echo "relinking ..."
	@$(CC) $(INCLS) -c $*.c
	@$(CC) -o $(EXEC)  $(OBJS)  $(LIBS)

clean:
	rm -f *.o
	rm -rf *.out

main:
	@$(CC) -c main.c

func:
	@$(CC) -c func.c