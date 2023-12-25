CC = gcc

CFLAGS = -Wall -Wextra -Werror -pedantic -Iheaders/

LDFLAGS = -lncurses

OBJS = main.o array.o rand.o tui.o cli.o

TARGET = rcharg

PREFIX = /usr/local

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

%.o: src/%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

install: $(TARGET)
	install -Dm755 $(TARGET) $(PREFIX)/bin/$(TARGET)

uninstall:
	rm -f $(PREFIX)/bin/$(TARGET)