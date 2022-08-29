#!/bin/bash
## Jenil_Patel_202101074
## Given path find if it exists ?(is is a file or directory : error message) (ternary operator c/c++ ;) )

echo
if [[ -e $1 ]]; then
    if [[ -d $1 ]]; then
        echo "Path given is a Directory."
    else
        echo "Path given is a File."
    fi
else
    echo "Path does not exist."
fi
echo