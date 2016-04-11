#!/bin/bash

#0|Gira0
for((i=0;$i<1000000000;i++));
do
    echo -n "${i}|"
    echo -n $( sed -n "$(( $RANDOM % 99170 + 1 ))p" /usr/share/dict/words ) 
    echo
done
