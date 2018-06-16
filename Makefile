CC=g++
CC_FLAGS=-I./include/
LIB_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system
OBJECTS=./build/SceneNode.o ./build/Entity.o ./build/Aircraft.o ./build/SpriteNode.o ./build/World.o ./build/CommandQueue.o ./build/Player.o ./build/Game.o ./build/main.o


all: ./bin/eagle

$(OBJECTS):
	$(CC) ./include/*.hpp
	$(CC) -c $(CC_FLAGS) ./src/*.cpp
	mv *.o ./build/

./bin/eagle: $(OBJECTS)
	$(CC) $(CC_FLAGS) $(OBJECTS) -o ./bin/eagle $(LIB_FLAGS)
	ln -s ./bin/eagle ./eagle

clean:
	rm ./include/*.gch
	rm ./build/*
	rm ./bin/*
	rm ./eagle
