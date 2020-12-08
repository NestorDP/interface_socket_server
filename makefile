
PROJECT = server
CC = g++
ARCH = arm
CFLAGS = -g -Wall -std=gnu++11
LDFLAGS = -g -Wall

BINDIR = bin
BUILDDIR = build
INCLUDEDIR = include
SOURCEDIR = src

SOURCES = $(shell find $(SOURCEDIR) -type f -name *.cpp)
OBJECTS	= $(patsubst $(SOURCEDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))
INCLUDES = -I $(INCLUDEDIR)

TARGET = $(BINDIR)/$(PROJECT)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) *.a $(BUILDDIR)/*.o *.~
