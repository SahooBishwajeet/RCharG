# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -pedantic -Iheaders/

# Linker flags
LDFLAGS = -lncurses

# Object files
OBJS = main.o array.o rand.o tui.o cli.o

# Target executable
TARGET = rcharg

# Installation prefix
PREFIX = /usr/local

# Build all targets
all: $(TARGET)

# Link object files to create the target executable
$(TARGET): $(OBJS)
	@$(CC) -o $@ $(OBJS) $(LDFLAGS)

# Compile source files into object files
%.o: src/%.c
	@$(CC) $(CFLAGS) -c $<

# Clean up object files and target executable
clean:
	@rm -f $(OBJS) $(TARGET)

# Install the target executable
install: $(TARGET)
	@install -Dm755 $(TARGET) $(PREFIX)/bin/$(TARGET)

# Uninstall the target executable
uninstall:
	@rm -f $(PREFIX)/bin/$(TARGET)