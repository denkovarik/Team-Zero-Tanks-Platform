#!/bin/bash
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color


echo "Starting CI verification script"
echo "--------------------------------"

echo ""
echo "Step 1: Cleaning the project."
echo "Executing: make clean"
make clean
RETVAL=$?

if [ $RETVAL -eq 0 ]; then
  echo -e "${GREEN}Clean successful${NC}"
else
  echo -e "${RED}Clean unsuccesful${NC}"
  exit 1
fi

echo ""
echo -e "Step 2: Making the project."
echo -e "Executing: make"

make
RETVAL=$?

if [ $RETVAL -eq 0 ]; then
  echo -e "${GREEN}make Successful${NC}"
else
  echo -e "${RED}make Fail${NC}"
  exit 2  
fi

echo ""
echo -e "${GREEN}+++++++++++++++++++++++++++${NC}"
echo -e "${GREEN}+ Make testing successful +${NC}"
echo -e "${GREEN}+++++++++++++++++++++++++++${NC}"
