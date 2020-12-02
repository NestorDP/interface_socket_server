
CC = g++
ARCH = arm
CFLAGS = -g -Wall -std=gnu++11
LDFLAGS = -g -Wall

BINDIR = bin
BUILDDIR = build
SRCDIR = src
SOURCES = $(shell find $(SRCDIR) -type f -name *.cpp)
OBJECTS	= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))
INC = -I include

TARGET = $(BINDIR)/server

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) *.a *.o *.~
