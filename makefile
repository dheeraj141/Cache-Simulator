all: sim

SRCS	= main.c check_inputs.c cache.c
OBJS	= ${SRCS:.c=.o}
.c.o:
	gcc -c -ansi -pedantic $<

sim: $(OBJS)
	gcc $(OBJS) -o sim

clean:
	rm -rf $(OBJS)  sim
