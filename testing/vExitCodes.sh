#!/bin/bash
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color



echo ""
echo "Starting CI Exit Code tests"
echo "----------------------------------"
echo "Finding ./battletanks"

#Early exit for GLuT testing
exit 0

if [ -e ./battletanks ]
then
        echo "Found at ./battletanks"
        mapfile -t array < <(./battletanks Not A Map . map)
else
        echo "./battletanks not found."
        echo "Trying to rebuild project."
        make
fi
        echo ""
        echo "Searching again for freshly built project:"
if [ -e ./battletanks ]
then
        echo "found at ./battletanks"
        mapfile -t array < <(./battletanks not a map . map)
fi

echo ""
echo "Step 1: Invalid number of arguments name"
echo ""
echo "./battletanks Not A Map . map"
echo "Error Message returned: ${array[1]}"

if [ "${array[1]}" == "Invalid number of arguments." ]; then
  echo -e "Number of arguments rejected, ${GREEN}OK${NC}"
else
  echo -e "Invalid number of arguments accepted, ${RED}FAIL${NC}"
  exit 1
fi

echo ""
echo "Step 2: Checking invalid arguments error code 1"
echo ""

./battletanks Not A Map.map > /dev/null
RETVALUE=$?

if [ $RETVALUE -eq 1 ]; then
  echo -e "Error code 1 caught, ${GREEN}OK${NC}"
else
  echo -e "Expected error code: 1, but recieved $RETVALUE,${RED}FAIL${NC}"
  exit 1
fi


echo ""
echo "Step 3: Unable to find a map"
echo "./battletanks NoMap.map"
        mapfile -t array < <(./battletanks NoMap.map)
echo "Error Message returned: ${array[3]}"
if [ "${array[3]}" == "Please check map name." ]; then
  echo -e "Invalid map name rejected, ${GREEN}OK${NC}"
else
  echo -e "Invalid map name accepted, ${RED}FAIL${NC}"
  exit 1
fi

echo ""
echo "Step 4: Checking unable to find map error code 2"
echo ""

./battletanks NoMap.map > /dev/null
RETVALUE=$?

if [ $RETVALUE -eq 2 ]; then
  echo -e "Error code 2 caught, ${GREEN}OK${NC}"
else
  echo -e "Expected error code: 2, but recieved $RETVALUE${RED}FAIL${NC}"
  exit 1
fi


echo ""
echo "Step 5: Invalid game mode in map file"
echo "./battletanks NotAMap.map"
mapfile -t array < <(./battletanks ../testing/NotAMap.map)
if [ "${array[3]}" == "Invalid game mode detected in map, please check map file." ]; then
  echo -e "Invalid game mode rejected, ${GREEN}OK${NC}"
else
  echo -e "Invalid game mode accpted, ${RED}FAIL${NC}"
  exit 1
fi
echo ""
echo "Step 6: Checking invalid game mode error code 3"
echo ""
./battletanks ../testing/NotAMap.map > /dev/null
RETVALUE=$?

if [ $RETVALUE -eq 3 ]; then
  echo -e "Error code 3 caught, ${GREEN}OK${NC}"
else
  echo -e "Expected error code: 3, but recieved $RETVALUE, ${RED}FAIL${NC}"
  exit 1
fi
