CC      =  gcc
CFLAGS  =
EXEC    =  a.out
INCLS   =  
LIBS    = 

OBJS    =  infi_cal.o  func.o  node.o

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
	@$(CC) -c infi_cal.c

node:
	@$(CC) -c node.c


