MAKEFLAGS += --silent

#directories
SOURCEDIR=src
OBJDIR=lib
INCLUDEDIR=include

#objects
SOURCES=$(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS=$(SOURCES:$(SOURCEDIR)/%.cpp=$(OBJDIR)/%.o)
INCLUDES=$(SOURCES:$(SOURCEDIR)/%.cpp=$(INCLUDEDIR)/%.h)
EXECUTABLE=cream.exe

#compiler
CC=g++
CFLAGS=-Wall -Werror -std=c++17 -g3 -o0 -I $(INCLUDEDIR)


all: $(EXECUTABLE)

clean:
	@printf "cleaning\n"
	rm -f $(OBJECTS)
	rm -f $(EXECUTABLE)
	@printf "finished cleaning\n"

run: $(EXECUTABLE)
	$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@printf "building executable '$@'\n"
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

$(OBJDIR)/%.o: $(SOURCEDIR)/%.cpp
	@printf "building $<\n"
	$(CC) $(CFLAGS) $< -c -o $@