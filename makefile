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
	@$(CC) -o $(EXEC)  $(OBJS)  $(LIBS)

clean:
	rm -f *.o
	rm -rf *.out

