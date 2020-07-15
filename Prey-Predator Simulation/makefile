CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

all: Organism.o Ant.o Doodlebug.o PoisonousAnt.o Player.o GamePad.o IntArray.o Position.o PositionArray.o main.o PredatorPrey

PredatorPrey: main.o Organism.o Ant.o Doodlebug.o PoisonousAnt.o Player.o GamePad.o IntArray.o Position.o PositionArray.o
	g++ ${CXXFLAGS} main.o Organism.o Ant.o Doodlebug.o PoisonousAnt.o Player.o GamePad.o IntArray.o Position.o PositionArray.o -o PredatorPrey

main.o: main.cpp
	g++ ${CXXFLAGS} -c main.cpp

Organism.o: Organism.cpp Organism.h
	g++ ${CXXFLAGS} -c Organism.cpp

Ant.o: Ant.cpp Ant.h
	g++ ${CXXFLAGS} -c Ant.cpp

Doodlebug.o: Doodlebug.cpp Doodlebug.h
	g++ ${CXXFLAGS} -c Doodlebug.cpp

PoisonousAnt.o: PoisonousAnt.cpp PoisonousAnt.h
	g++ ${CXXFLAGS} -c PoisonousAnt.cpp

Player.o: Player.cpp Player.h
	g++ ${CXXFLAGS} -c Player.cpp

GamePad.o: GamePad.cpp GamePad.h
	g++ ${CXXFLAGS} -c GamePad.cpp

IntArray.o: IntArray.cpp IntArray.h
	g++ ${CXXFLAGS} -c IntArray.cpp

Position.o: Position.cpp Position.h
	g++ ${CXXFLAGS} -c Position.cpp

PositionArray.o: PositionArray.cpp PositionArray.h
	g++ ${CXXFLAGS} -c PositionArray.cpp

val:
	valgrind --tool=memcheck --leak_check=yes --show-reachable=yes --track-fds=yes ./PredatorPrey

clean:
	rm *.o PredatorPrey
