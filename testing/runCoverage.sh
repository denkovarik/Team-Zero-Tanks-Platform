#!/bin/bash
THREAD=${1:-2}
echo "Cleaning extra files"
make coverage-clean

echo ""
echo "Making coverage file"
make coverage THREADS=${THREAD}

echo ""
echo "Running ./covTanks to create gco files"
./covTanks

echo ""
echo "Ceating gcda files"
gcov gameFunctions.gcno
gcov api.gnco
gcov classes/classTank.gcno
gcov classes/classGame.gcno
gcov classes/classProjectile.gcno
gcov classes/classMap.gcno

echo ""
echo "Creating report with lcov"
mkdir -p coverage
lcov --no-external --directory . --capture --output-file coverage/coverage.info
#Moved to below for final output
#lcov --list coverage/coverage.info > coverage/coverage.list

echo ""
echo "Cleaning up after, coverage files in coverage/ folder"
find . -type f -name '*.gc*' -exec rm {} +

echo ""
echo "Create a fancy web page"
genhtml -o coverage/ coverage/coverage.info

echo ""
echo "Leaving lcov output in file and stdout"
lcov --list coverage/coverage.info 2>&1 | tee coverage/coverage.list
