CC      =  gcc-9
CFLAGS  =
EXEC    =  infi_cal.out
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