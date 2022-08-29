#!/bin/bash
## Jenil_Patel_202101074
## Print the day of week for all CLA inputs between 1 to 7

echo
for i in $@
do
    echo -n "$i = "
    case $i in
        1) echo "Monday";;
        2) echo "Tuesday";;
        3) echo "Wednesday";;
        4) echo "Thursday";;
        5) echo "Friday";;
        6) echo "Saturday";;
        7) echo "Sonday";;
        *) echo "Invalid day number!"
    esac
done
echo