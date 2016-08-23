#!/bin/bash

# Script to compile libraries with ACLiC

if [ -d $1 ]
then
    echo "usage: compile_lib2.sh <filename> <extension>"
    exit
fi

BASE=$1
EXT=$2

FNAME=$BASE"."$EXT
#COMPILE_LOGON="~/n2analysis/customize_root/compile_logon.C"
COMPILE_LOGON="/projects/e15118/n2analysis/customize_root/compile_logon.C"

# compile in root using ACLiC
root.exe -b -n ${COMPILE_LOGON} <<EOF
.L ${FNAME}++
.q
EOF


LIB=$BASE"_"$EXT".so"
if [ $(file /bin/bash | awk '{ print $3 }') == "32-bit" ]; then
  mv $LIB ../lib/lib32/root/
fi
if [ $(file /bin/bash | awk '{ print $3 }') == "64-bit" ]; then
  mv $LIB ../lib/lib64/root/
fi
