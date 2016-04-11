#!/bin/bash

#0|Arhopolis
for((i=0;$i<100000;i++));
do
    echo -n "${i}|"
    echo -n $( sed -n "$(( $RANDOM % 280 + 1 ))p" name ) 
    echo
done
