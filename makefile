CC      =  gcc
CFLAGS  =
EXEC    =  a.out
INCLS   =  
LIBS    = 

OBJS    =  infi_cal.o  func.o

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
	rm -rf *.out

main:
	@$(CC) -c infi_cal.c

func:
	@$(CC) -c func.c

all:
	@$(CC) -g src/inf_calc.c src/func.c src/cal_fun.c
