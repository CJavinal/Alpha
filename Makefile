CC = g++
CC_FLAGS = -I./include/
LIB_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

EXEC = eagle
SOURCES = $(sort $(shell find ./src/ -name '*.cpp'))
OBJECTS = $(notdir $(SOURCES:.cpp=.o))
BUILDS = $(addprefix ./build/,$(OBJECTS))


#Main target
$(EXEC) : $(BUILDS)
	echo compiling
	$(CC) $(CC_FLAGS) $(BUILDS)  -o $(EXEC) $(LIB_FLAGS)

$(BUILDS) : $(OBJECTS)
	cp $(OBJECTS) ./build/

$(OBJECTS): %.o : $(addprefix ./src/,%.cpp)
	$(CC) -c $(CC_FLAGS) $< -o $@
	
# To remove generated files
clean:
	rm -f $(EXEC) $(BUILDS)
