#!/bin/bash
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo ""
echo "Starting OpenGL starting verification script"
echo "--------------------------------------------"
echo "Finding ./battletanks"

if [ ! -e ./battletanks ]
then
        echo "./battletanks not found."
        echo "Trying to rebuild project."
        make CXXFLAGS=-DDEBUG
        echo ""
        echo "Searching again for freshly built project:"

        if [ ! -e ./battletanks ]
        then
          echo "Failed to build or ./battletanks not found."
          exit 1
        fi
fi
echo "Found at ./battletanks"
mapfile -t array -n 17 < <(./battletanks -maxturn 1 -idle 100)
RETVAL=$?

echo ""
echo "Step 1: Welcome text"
if [ "${array[0]}" == "Welcome to BattleTanks" ]; then
  echo -e "Welcome text, ${GREEN}OK${NC}"
else
  echo -e "Welcome text, ${RED}FAIL${NC}"
  echo -e "Looking for text: Welcome to BattleTanks"
  exit 1
fi

echo ""
echo "Step 2: Starting game initilization"
if [ "${array[1]}" == "Game::Starting game init." ]; then
  echo -e "Started Iinitilization, ${GREEN}OK${NC}"
else
  echo -e "Playfield not loaded, ${RED}FAIL${NC}"
  echo -e "Looking for text: Game::Starting game init."
  exit 1
fi

echo ""
echo "Step 3: Saving settings"
if [ "${array[2]}" == "Game::Saving Settings." ]; then
  echo -e "Savd settings, ${GREEN}OK${NC}"
else
  echo -e "Wrong game mode, ${RED}FAIL${NC}"
  echo -e "Looking for text: Game Saving Settings."
  exit 1
fi

echo ""
echo "Step 4: Map Name"
echo -e ${array[3]}
if [ "${array[3]}" == "     Map Name: default.map" ]; then
  echo -e "Correct map name, ${GREEN}OK${NC}"
else
  echo -e "Wrong map size, ${RED}FAIL${NC}"
  echo -e "Looking for text:     Map Name: default.map"
  exit 1
fi

echo ""
echo "Step 5: Max turns"
echo ${array[4]} 
if [ "${array[4]}" == "     Max turns: 1" ]; then
  echo -e "Correct max loaded, ${GREEN}OK${NC}"
else
  echo -e "Wrong max turns, ${RED}FAIL${NC}"
  echo -e "Looking for:     Max turns: 1"
  exit 1
fi

echo ""
echo "Step 6: Idle Speed"
echo 
if [ "${array[5]}" == "     Idle Speed: 100" ]; then
  echo -e "Correct idle speed, ${GREEN}OK${NC}"
else
  echo -e "Wrong Idle Speed, ${RED}FAIL${NC}"
  echo -e "Looking for:     Idle Speed: 100"
  exit 1
fi

echo ""
echo "Step 7: UI Mode"
echo
if [ "${array[6]}" == "     UI Mode: OpenGL" ]; then
  echo -e "Correct UI mode, ${GREEN}OK${NC}"
else
  echo -e "Wrong UI mode, ${RED}FAIL${NC}"
  echo -e "Looking for:      UI Mode: OpenGL"
  exit 1
fi

echo ""
echo "Step 8: Reading Map"
echo 
if [ "${array[7]}" == "Game::Reading Map: default.map" ]; then
  echo -e "Started Reading Map, ${GREEN}OK${NC}"
else
  echo -e "Map reading failed, ${RED}FAIL${NC}"
  echo -e "Looking for: Game::Reading Map: default.map"
  exit 1
fi

echo ""
echo "Step 9: Getting GameMode"
echo 
if [ "${array[8]}" == "     GameMode: tanks" ]; then
  echo -e "Correct game mode, ${GREEN}OK${NC}"
else
  echo -e "Wrong game mode, ${RED}FAIL${NC}"
  echo -e "Looking for:     GameMode: tanks"
  exit 1
fi

echo ""
echo "Step 10: Saving GameMode"
echo 
if [ "${array[9]}" == "Game::Saving game mode." ]; then
  echo -e "Game mode saved, ${GREEN}OK${NC}"
else
  echo -e "Failed to save gamemode, ${RED}FAIL${NC}"
  echo -e "Looking for: Game::Saving game mode."
  exit 1
fi

echo ""
echo "Step 11: Getting Map size"
echo 
if [ "${array[10]}" == "Game::Setting map size:" ]; then
  echo -e "Getting map size, ${GREEN}OK${NC}"
else
  echo -e "Wrong map size, ${RED}FAIL${NC}"
  echo -e "Looking for: Game::Setting map size: "
  exit 1
fi

echo ""
echo "Step 12: FieldX"
echo
if [ "${array[11]}" == "     FieldX: 20" ]; then
  echo -e "Correct X value, ${GREEN}OK${NC}"
else
  echo -e "Wrong X size, ${RED}FAIL${NC}"
  echo -e "Looking for:     FieldX: 20"
  exit 1
fi

echo ""
echo "Step 13: FieldY"
echo 
if [ "${array[12]}" == "     FieldY: 10" ]; then
  echo -e "Correct Y value, ${GREEN}OK${NC}"
else
  echo -e "Wrong Y size, ${RED}FAIL${NC}"
  echo -e "Looking for:      FieldY: 10 "
  exit 1
fi

echo ""
echo "Step 14: Loading tanks"
echo 
if [ "${array[13]}" == "Game::Loading tanks" ]; then
  echo -e "Started loading tanks, ${GREEN}OK${NC}"
else
  echo -e "Could not load tanks, ${RED}FAIL${NC}"
  echo -e "Looking for: Game::Loading tanks"
  exit 1
fi

echo ""
echo "Step 15: Adding tanks from comp/Tanks"
echo 
if [ "${array[14]}" == "Adding tanks from comp/Tanks" ]; then
  echo -e "Correctly set turn counter, ${GREEN}OK${NC}"
else
  echo -e "Turn counter not set, ${RED}FAIL${NC}"
  echo -e "Looking for: Adding tanks from comp/Tanks"
  exit 1
fi

echo ""
echo "Step 16: Return value"
if [ $RETVAL -eq 0 ]; then
  echo -e "Return value is 0, ${GREEN} OK ${NC}"
else
  echo -e "Return value is not 0, ${RED} FAIL ${NC}"
  exit 1
fi
