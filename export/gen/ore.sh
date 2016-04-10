#!/bin/bash

#0|Gira0
for((i=0;$i<10;i++));
do
    echo -n "${i}|"
    echo -n $( sed -n "$(( $RANDOM % 99170))p" /usr/share/dict/words ) 
    echo
done
