CC=gcc
CFLAGS=-fPIC -Wall -O2 -g
LDFLAGS=-shared

TARGET_LIB=libpacket

SRCS=str.c
OBJS=$(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

.PHONY: clean
clean:
	rm -rf ${TARGET_LIB} ${OBJS}

