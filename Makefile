# C++ compiler flags
#Only uncomment one CXXFLAGS section
#Non-Debugging C++ flags:
#CXXFLAGS = -Wall -g -O2 -fmax-errors=5 -std=c++11
#Debugging C++ compiler flags:
override CXXFLAGS += -Wall -g -fmax-errors=5 -std=c++11
COVFLAGS = -fprofile-arcs -ftest-coverage
LDFLAGS = -rdynamic -lalloc2d -Llibraries -ldl
LDCATCHFLAGS = -rdynamic -lcatch -lalloc2d -Llibraries -ldl

# Only main source file
MAIN = main.cpp
#Buffer file for catch
#MAINC = testing/catch/startTanksCatch.cpp

THREADS ?=2

# Utility sources - Needed for production and testing builds
#SRC = alloc2d.cpp
# Class Files
SRC = classes/classGame.cpp classes/classProjectile.cpp classes/classMap.cpp classes/classTank.cpp classes/classObjects.cpp
# other game files
SRC += gameFunctions.cpp
# OpenGL
SRC += callbacks.cpp util.cpp event.cpp game.cpp
# Tank Support files
SRC += comp/base.cpp comp/src/tankLoader.cpp comp/src/constants.h
# api
SRC += api.cpp
# Tank files
TANKS = comp/runner.cpp comp/chaser.cpp comp/qaDestroyer.cpp

#Library files
LIBALLOC = libraries/src/alloc2d.cpp 
LIBCATCH = libraries/src/startTanksCatch.cpp

# source files for catch testing
#tankClass testing
CATCHT = testing/catch/tankTesting.cpp 
#gameClass testing
CATCHG = testing/catch/gameTesting.cpp 
#projectileClass testing
CATCHP = testing/catch/projectileTesting.cpp 
#mapClass testing
CATCHM = testing/catch/mapTesting.cpp
#gameFunction testing
CATCHF = testing/catch/gameFunctionsTesting.cpp

# OpenGL/GLUT libraries for Linux
GL_LIBS = -lglut -lGLU -lGL
# add in POSIX threads library, to prevent driver issues in Linux Lab
GL_LIBS += -lpthread

# Targets
battletanksT: gen-tank-libraries
	make battletanks -j$(THREADS)
battletanks: $(MAIN:.cpp=.o) $(SRC:.cpp=.o)
	g++ $(CXXFLAGS) -o $@ $? $(GL_LIBS) $(LDFLAGS)
9: clean  gen-tank-libraries
	make battletanks -j9

gen-tank-libraries: $(TANKS) 
	mkdir -p comp/Tanks
	g++ -o comp/Tanks/runner.so -fPIC comp/runner.cpp -std=c++11 -shared
	g++ -o comp/Tanks/chaser.so -fPIC comp/chaser.cpp -std=c++11 -shared
	g++ -o comp/Tanks/qaDestroyer.so -fPIC comp/qaDestroyer.cpp -std=c++11 -shared

gen-libraries: gen-libraries-alloc gen-libraries-catchso
gen-libraries-alloc: $(LIBALLOC:.cpp=.o) 	
	ar rs libraries/liballoc2d.a $?

gen-libraries-catch: $(LIBCATCH:.cpp=.o) $(CATCHT:.cpp=.o) $(CATCHG:.cpp=.o) $(CATCHP:.cpp=.o) $(CATCHM:.cpp=.o) $(CATCHF:.cpp=.o)
	g++ libraries/src/catch.hpp
	ar rs libraries/libcatch.a $^ libraries/src/catch.hpp.gch

#This order should mean only 1 compile and multiple links after
catch: clean gen-tank-libraries
	make catch-all -j$(THREADS) CXXFLAGS=-DCATCH

catch-all:	build-catch-all build-catch-tank build-catch-game build-catch-projectile build-catch-map build-catch-gameFunctions
catch-tank:	build-catch-tank
catch-game:	build-catch-game
catch-projectile:	build-catch-projectile
catch-map:	build-catch-map
catch-gameFunctions: build-catch-gameFunctions

clean:
	find . -type f -name '*.o' -exec rm {} +
	rm -f battletanks
	rm -f catch*
	rm -f covT*
	rm -f gameLoop
	rm -f gameFunc
	rm -rf coverage
	rm -f comp/Tanks/*.so

catch-clean: clean #all functions moved to clean

test:
	testing/./runTests.sh

build-catch-all: $(SRC:.cpp=.o) $(CATCHT:.cpp=.o) $(CATCHG:.cpp=.o) $(CATCHP:.cpp=.o) $(CATCHM:.cpp=.o) $(CATCHF:.cpp=.o)
	g++ $(CXXFLAGS) -o catch $^ $(GL_LIBS) $(LDCATCHFLAGS)

build-catch-tank:	$(SRC:.cpp=.o) $(CATCHT:.cpp=.o)
	g++ $(CXXFLAGS) -o catchTank $^ $(GL_LIBS) $(LDCATCHFLAGS)

build-catch-game:	$(SRC:.cpp=.o) $(CATCHG:.cpp=.o)
	g++ $(CXXFLAGS) -o catchGame $^ $(GL_LIBS) $(LDCATCHFLAGS)

build-catch-projectile:	$(SRC:.cpp=.o) $(CATCHP:.cpp=.o)
	g++ $(CXXFLAGS) -o catchProjectile $^ $(GL_LIBS) $(LDCATCHFLAGS)

build-catch-map:	$(SRC:.cpp=.o) $(CATCHM:.cpp=.o)
	g++ $(CXXFLAGS) -o catchMap $^ $(GL_LIBS) $(LDCATCHFLAGS)

build-catch-gameFunctions:	$(SRC:.cpp=.o) $(CATCHF:.cpp=.o)
	g++ $(CXXFLAGS) -o catchGameFunction $^ $(GL_LIBS) $(LDCATCHFLAGS)

coverage: gen-tank-libraries
	make coverage-main -j$(THREADS) CXXFLAGS=-DCATCH

coverage-main: $(SRC:.cpp=.o) $(CATCHT:.cpp=.o) $(CATCHG:.cpp=.o) $(CATCHP:.cpp=.o) $(CATCHL:.cpp=.o) $(CATCHM:.cpp=.o)
	g++ $(CXXFLAGS) $(COVFLAGS) -o classes/classGame.o -c classes/classGame.cpp
	g++ $(CXXFLAGS) $(COVFLAGS) -o classes/classTank.o -c classes/classTank.cpp
	g++ $(CXXFLAGS) $(COVFLAGS) -o classes/classProjectile.o -c classes/classProjectile.cpp
	g++ $(CXXFLAGS) $(COVFLAGS) -o classes/classMap.o -c classes/classMap.cpp
	g++ $(CXXFLAGS) $(COVFLAGS) -o api.o -c api.cpp
	g++ $(CXXFLAGS) $(COVFLAGS) -o gameFunctions.o -c gameFunctions.cpp
	g++ $(CXXFLAGS) -o callbacks.o -c callbacks.cpp
	g++ $(CXXFLAGS) -o util.o -c util.cpp
	g++ $(CXXFLAGS) -o event.o -c event.cpp
	g++ $(CXXFLAGS) $(COVFLAGS) -o game.o -c game.cpp
	g++ $(CXXFLAGS) -o testing/catch/tankTesting.o -c testing/catch/tankTesting.cpp
	g++ $(CXXFLAGS) -o testing/catch/gameTesting.o -c testing/catch/gameTesting.cpp
	g++ $(CXXFLAGS) -o testing/catch/projectileTesting.o -c testing/catch/projectileTesting.cpp
	g++ $(CXXFLAGS) -o testing/catch/mapTesting.o -c testing/catch/mapTesting.cpp
	g++ $(CXXFLAGS) -o testing/catch/gameFunctionsTesting.o -c testing/catch/gameFunctionsTesting.cpp
	g++ $(CXXFLAGS) -o libraries/src/startTanksCatch.o -c libraries/src/startTanksCatch.cpp
	g++ -o covTanks $(COVFLAGS) $^ $(GL_LIBS) $(LDCATCHFLAGS)

coverage-clean: clean
	find . -type f -name '*.gc*' -exec rm {} +

help:
	@echo "Commands:"
	@echo "  make                       - Build default battletanks binary"
	@echo "  make clean                 - Removes all binaries, object files, and coverage files"
	@echo "  make catch                 - Build's all catch testing binaries"
	@echo "  make catch-tanks           - Build only the tank testing binary"
	@echo "  make catch-game            - Build only the game testing binary"
	@echo "  make catch-projectile      - Build only the projectile testing binary"
	@echo "  make catch-map             - Build only the map testing binary"
	@echo "  make catch-gameFunctions   - Build only the gameFunctions binary"
	@echo "  make coverage              - Creates binary file with coverage testing markers"
	@echo "  make coverage-clean        - Removes coverage generated object files"

