CC      =	gcc
HEADS   =	$(shell find ./includes -type f -name *.h)
SRCS 	=	$(shell find ./src -type f -name *.c)
OBJS	=	$(SRCS:.c=.o)

all: $(OBJS)
	@echo "linking ..."

$(OBJS): $(SRCS)

%.o: %.c
	$(CC) -c $< -o $(<:.c=.o) -Include $(HEADS)

clean:
	rm -rf src/*.o

relink:
	@echo "relinking ..."