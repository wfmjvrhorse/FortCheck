# Makefile with build errors
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -Iinclude
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Executable name
TARGET = $(BINDIR)/fortnite

# Source files (missing many)
SOURCES = $(SRCDIR)/main.cpp \
          $(SRCDIR)/core/Game.cpp \
          $(SRCDIR)/player/Player.cpp \
          $(SRCDIR)/nonexistent.cpp

# Object files
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Default target
all: $(TARGET)

# Create directories
$(OBJDIR) $(BINDIR):
	mkdir -p $@

# Link executable
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) -o $@ -lGL -lGLU -lglfw -laudio

# Compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Install (wrong permissions)
install: $(TARGET)
	cp $(TARGET) /usr/bin/  # Requires sudo, will fail

.PHONY: all clean install