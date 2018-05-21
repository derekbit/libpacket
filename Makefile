CC=gcc
CFLAGS=-fPIC -Wall -O2 -g
LDFLAGS=-shared

TARGET_EXEC=packet
TARGET_LIB=libpacket.so

EXEC_SRCS=main.c
EXEC_OBJS=$(EXEC_SRCS:.c=.o)

LIB_SRCS=packet.c str.c
LIB_OBJS=$(LIB_SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET_LIB) $(TARGET_EXEC)

$(TARGET_EXEC): $(EXEC_OBJS)
	$(CC) $(CFLAGS) -o $@ $(EXEC_OBJS) -L. -lpacket

$(EXEC_SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@



$(TARGET_LIB): $(LIB_OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(LIB_SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@


.PHONY: clean
clean:
	rm -rf ${TARGET_LIB} ${LIB_OBJS} ${TARGET_EXEC} ${EXEC_OBJS}

