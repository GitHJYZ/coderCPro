src=$(wildcard ./*.c)
objs=$(patsubst %.c,%.o,$(src))
target=Server -g

cflags = -lpthread
option = -Wall

$(target):$(objs)
	$(CC) $^ -o $(target) $(cflags) $(option)
%.o:%.c
	$(CC) -c $< -o $@  $(cflags) $(option)

.PHONY:clean
clean:
		-rm $(objs) -f