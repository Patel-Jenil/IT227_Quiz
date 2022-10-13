#!/bin/bash
## Jenil_Patel_202101074
## Concatenate log files to a warnings.log file with all 'warning' occured in file.

logFileName=warning.log

if [[ -e $logFileName ]]; then
    echo "" | cat >> $logFileName
    echo -n "New Warnings in logs at " | cat >> $logFileName
    date | cat >> $logFileName
else
    echo -n "Warning log started at " | cat >> $logFileName
    date | cat >> $logFileName
fi

for i in *.log ; do
    grep --exclude=$logFileName -w WARNING $i | cat >> $logFileName
done
echo
echo "Warnings added in $logFileName"
echo
open $logFileName