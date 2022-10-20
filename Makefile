OS=$(shell uname -s)
ARCH=$(shell uname -m)
CFLAGS=-O -Wall -Wextra -fstack-protector-strong -pipe -MMD
ifeq ($(OS), Darwin)
	CFLAGS+=-arch $(ARCH) -mmacosx-version-min=12.0
endif
RM=rm -fvr
SRCS=pwe.c
OBJS=$(SRCS:.c=.o)
DEPS=$(SRCS:.c=.d)
TARGET=pwe

.PHONY: all clean dist-clean deps

all: $(TARGET)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lmpfr

clean:
	$(RM) $(TARGET) $(OBJS)

dist-clean: clean
	$(RM) $(DEPS)

deps: $(DEPS)

-include $(DEPS)
