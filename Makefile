CC = g++
CC_FLAGS = -I./include/ -Wall -Wextra
LIB_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

EXEC = ./bin/eagle
SOURCES = $(sort $(shell find ./src/ -name '*.cpp'))
OBJECTS = $(SOURCES:.cpp=.o)


#Main target
$(EXEC) : $(OBJECTS)
	echo compiling
	$(CC) $(CC_FLAGS) $(OBJECTS)  -o $(EXEC) $(LIB_FLAGS)


$(OBJECTS): %.o : %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@
	
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
