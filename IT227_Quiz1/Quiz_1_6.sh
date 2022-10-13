#!/bin/bash
## Jenil_Patel_202101074
## Execute each .out programs from path given through CLArguments and store their exit code in an array.

path_=$1

if [[ ! $1 ]];then
    path_=$(pwd)
fi
cd $path_

##########################################################################################################################
#I've created .out files customed for different exit status.\n So give this folder as path or don't give anything at all"#
##########################################################################################################################
# First targeting every .out file in given path, executing them and then storing their exit status in ans

j=0
for i in ./*.out; do
    echo -e "\nExecuting $i: " && ./$i
    statusArray[$j]=$?
    j=$[ $j + 1 ]
done

echo -en "\nExit Status Array:\n"
k=0
while [ $k -lt $j ]; do
    echo -n "$[statusArray[$k]] "
    k=$[ $k + 1 ]
done
echo;echo;