#!/bin/bash
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

testing/./vMake.sh
RETVAL=$?
if [ $RETVAL -eq 0 ]; then
        echo -e ""
        echo -e "${GREEN}+++++++++++++++++++++++++${NC}"
        echo -e "${GREEN}+ All Make Tests Passed +${NC}"
        echo -e "${GREEN}+++++++++++++++++++++++++${NC}"
else
        echo ""
        echo -e "${RED}**************************${NC}"
        echo -e "${RED}*Failed During Make Test *${NC}"
        echo -e "${RED}**************************${NC}"
       exit 1
fi

testing/./vProgASCII.sh
RETVAL=$?
if [ $RETVAL -eq 0 ]; then
        echo ""
        echo -e "${GREEN}++++++++++++++++++++++++++++++++${NC}"
        echo -e "${GREEN}+ All ASCII start tests Passed +${NC}"
        echo -e "${GREEN}++++++++++++++++++++++++++++++++${NC}"
else
        echo ""
        echo -e "${RED}****************************${NC}"
        echo -e "${RED}* Failed ASCII start Tests *${NC}"
        echo -e "${RED}****************************${NC}"
        exit 1
fi

make clean
testing/./vProgOpenGL.sh
RETVAL=$?
if [ $RETVAL -eq 0 ]; then
        echo ""
        echo -e "${GREEN}+++++++++++++++++++++++++++++++++${NC}"
        echo -e "${GREEN}+ All OpenGL start tests Passed +${NC}"
        echo -e "${GREEN}+++++++++++++++++++++++++++++++++${NC}"
else
        echo ""
        echo -e "${RED}*****************************${NC}"
        echo -e "${RED}* Failed OpenGL start Tests *${NC}"
        echo -e "${RED}*****************************${NC}"
        exit 1
fi
#testing/./vExitCodes.sh
#RETVAL=$?
#if [ $RETVAL -eq 0 ]; then
#        echo ""
#        echo -e "${GREEN}++++++++++++++++++++++++++++++${NC}"
#        echo -e "${GREEN}+ All Exit Code Tests Passed +${NC}"
#        echo -e "${GREEN}++++++++++++++++++++++++++++++${NC}"
#else
#        echo ""
#        echo -e "${RED}********************************${NC}"
#        echo -e "${RED}* Failed During Exit Code Test *${NC}"
#        echo -e "${RED}********************************${NC}"
#        exit 1
#fi
make clean
testing/./vCatch.sh
RETVAL=$?
if [ $RETVAL -eq 0 ]; then
        echo ""
        echo -e "${GREEN}++++++++++++++++++++++++++${NC}"
        echo -e "${GREEN}+ All Catch Tests Passed +${NC}"
        echo -e "${GREEN}++++++++++++++++++++++++++${NC}"
else
        echo ""
        echo -e "${RED}*******************************${NC}"
        echo -e "${RED}* Failed During Catch Testing *${NC}"
        echo -e "${RED}*******************************${NC}"
        exit 1
fi


#Everything Passed
echo -e "${GREEN}++++++++++++++++++++++++++++++++++++++++++++++++++++++${NC}"
echo -e "${GREEN}+                                                    +${NC}"
echo -e "${GREEN}+               Everything Passed                    +${NC}"
echo -e "${GREEN}+                                                    +${NC}"
echo -e "${GREEN}++++++++++++++++++++++++++++++++++++++++++++++++++++++${NC}"
