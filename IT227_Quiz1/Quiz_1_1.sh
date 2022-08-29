#!/bin/bash
## Jenil_Patel_202101074
## Print Sum of all CLAs

sum=0
for i in $@
do
	sum=$[$sum + $i]
done
echo -e "\nSum of all $# command line integer arguments is: ${sum}\n"