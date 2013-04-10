#!/bin/bash
#

PPWWDD=`pwd`
CSRCDIR=cpp
JSRCDIR=java
TOOLDIR=tool
PACKAGE=com/yomei/myhttpd

TARGET=NanoJsonHttpdMain
FILES="BinaryUtil CTime HttpApi HttpClient HttpSession InputUtil MyAddress MyClock NanoJsonHttpdMain MySort NanoJsonHttpd SafeBufferedReader ThreadManager NanoJsonHttpdError"


echo ------------------------------
echo Step 1 building tools
echo ------------------------------

function compile_tool () {

TOOLOUTFILE="deletecomment"
echo "TOOLOUTFILE=" $TOOLOUTFILE

cd $TOOLDIR
echo gcc -o $TOOLOUTFILE deletecomment.c
gcc -o $TOOLOUTFILE deletecomment.c
if [ $? -ne 0 ] ; then 
echo "######################"
echo "######## tool gcc compile error"
echo "######################"
exit 1
fi
cd $PPWWDD
cp -f $TOOLDIR/$TOOLOUTFILE .

}


if [ ! -f "deletecomment" ] ; then 
compile_tool
fi


echo ------------------------------
echo Step 2 cleaning objects.
echo ------------------------------

rm -r -f $JSRCDIR
rm -r -f $CSRCDIR

mkdir -p $JSRCDIR/$PACKAGE
mkdir -p $CSRCDIR



echo ------------------------------
echo Step 4 cpp to java.
echo ------------------------------



for i in $FILES; do
echo $i
g++ -o $CSRCDIR/$i.p -DJAVA -E $i.cpp
./deletecomment $CSRCDIR/$i.p $JSRCDIR/$PACKAGE/$i.java
done


echo ------------------------------
echo Step 5 comple  for PC java.
echo ------------------------------

cd $JSRCDIR
for i in $FILES; do
echo $i
javac $PACKAGE/$i.java
if [ $? -ne 0 ] ; then 
echo "######################"
echo "######## pc javac error"
echo "######################"
exit 1
fi
done
cd $PPWWDD

echo ------------------------------
echo Step 6 execute on PC java.
echo ------------------------------

cd $JSRCDIR
java $PACKAGE/$TARGET
cd $PPWWDD

echo ------------------------------
echo Build OK!!!!!!!!
echo ------------------------------


