#!/bin/bash
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color
THREAD=${1:-2}

echo ""
echo "Starting Catch Game Tests"
echo "----------------------------------"
echo "Cleaning catch files"
make catch-clean
echo ""
echo "Making catch files"
echo "----------------------------------"
make catch THREADS=${THREAD}
echo "Finding ./catch"

if [ -e ./catch ]
then
        echo "Found at ./catch"
else
        echo "./catchGame not found."
        echo "Trying to rebuild project."
        make catch THREADS=${THREAD}
        echo ""
        echo "Searching again for freshly built project:"

   if [ -e ./catch ]
   then
        echo "found at ./catch"
   else
        exit 1
   fi
fi

if [ ! -e ./catchTank ]
then
        echo "Problem building catchTank test file"
        exit 1
elif [ ! -e ./catchGame ]
then
        echo "Problem building catchGame test file"
        exit 1
elif [ ! -e ./catchProjectile ]
then
        echo "Problem building catchProjectile test file"
        exit 1
elif [ ! -e ./catchMap ] 
then
        echo "Problem building catchMap test file"
        exit 1
elif [ ! -e ./catchGameFunction ]
then
        echo "Problem building catchGameFunction file"
        exit 1
fi

echo -e ""
echo "Running Tank Catch Tests."
./catchTank -o /dev/null
RETVAL=$?

if [[ $RETVAL -eq 0 ]]; then
  echo -e ""
  echo -e "Catch Tank tests past, ${GREEN}PASSED${NC}"
else
  echo -e ""
  echo -e "Catch Tank tests failed, ${RED}FAIL${NC}"
  echo -e "Please run ./catchTank tests to see what failed."
  exit 1
fi

echo -e ""
echo "Running Game Catch Tests."
./catchGame -o /dev/null
RETVAL=$?

if [[ $RETVAL -eq 0 ]]; then
  echo -e ""
  echo -e "Catch Game tests past, ${GREEN}PASSED${NC}"
else
  echo -e ""
  echo -e "Catch Game tests failed, ${RED}FAIL${NC}"
  echo -e "Please run ./catchGame tests to see what failed."
  exit 1
fi

echo -e ""
echo "Running Projectile Catch Tests."
./catchProjectile -o /dev/null
RETVAL=$?

if [[ $RETVALUE -eq 0 ]]; then
  echo -e ""
  echo -e "Catch Projectile tests past, ${GREEN}PASSED${NC}"
else
  echo -e ""
  echo -e "Catch Projectile tests failed, ${RED}FAIL${NC}"
  echo -e "Please run ./catchProjectile tests to see what failed."
  exit 1
fi

echo -e ""
echo "Running Map Catch Tests."
./catchMap -o /dev/null
RETVAL=$?

if [[ $RETVALUE -eq 0 ]]; then
  echo -e ""
  echo -e "Catch Map tests past, ${GREEN}PASSED${NC}"
else
  echo -e ""
  echo -e "Catch Projectile tests failed, ${RED}FAIL${NC}"
  echo -e "Please run ./catchMap tests to see what failed."
  exit 1
fi

echo -e ""
echo "Running gameLoop Catch Tests."
./catchGameLoop -o /dev/null
RETVAL=$?

if [[ $RETVALUE -eq 0 ]]; then
  echo -e ""
  echo -e "Catch gameLoop tests past, ${GREEN}PASSED${NC}"
else
  echo -e ""
  echo -e "Catch gameLoop tests failed, ${RED}FAIL${NC}"
  echo -e "Please run ./catchGameLoop tests to see what failed."
  exit 1
fi

echo -e ""
echo "Running gameFunctions Catch Tests."
./catchGameFunction -o /dev/null
RETVAL=$?

if [[ $RETVALUE -eq 0 ]]; then
  echo -e ""
  echo -e "Catch gameFunctions tests past, ${GREEN}PASSED${NC}"
else
  echo -e ""
  echo -e "Catch gameFunctions tests failed, ${RED}FAIL${NC}"
  echo -e "Please run ./catchGameFunctions tests to see what failed."
  exit 1
fi

