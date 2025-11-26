# Abe Busschau -- busschau@pdx.edu -- Program #3 Makefile

CC=g++
FLAGS=-std=c++17 -g -Wall
SOURCES=$(wildcard *.cpp)
OBJS=$(SOURCES:.cpp=.o)
DEPS=$(wildcard *.h)

ZIPNAME = busschau_prog3.zip
TARGET=race

all: $(TARGET)

# Link Object Files
$(TARGET): $(OBJS)
	$(CC) $(FLAGS) -o $@ $(OBJS)

# Compile Each .cpp into .o
%.o: %.cpp $(DEPS)
	$(CC) $(FLAGS) -c $< -o $@

# Clean Up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Run Program
run: $(TARGET)
	./$(TARGET)

# Zip Files Together
zip:
	zip $(ZIPNAME) $(SOURCES) $(DEPS) Makefile

# Open All files
o:
	vim *h *cpp -p


