#!/bin/bash
## Jenil_Patel_202101074
## Print Factorial using fact() function
## I used recursive technique 
function fact() {
    local n=$1
    if [[ $n -eq 0 ]]; then
        echo 1
    else
        echo $((n*$(fact $n-1)))
    fi
    
}

num=$1
if [[ ! $1 ]]; then
    num=0
fi
echo -e "\n$num!= $(fact $num)\n"