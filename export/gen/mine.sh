#!/bin/bash

#0|Arhopolis
for((i=0;$i<10;i++));
do
    echo -n "${i}|"
    echo -n $( sed -n "$(( $RANDOM % 280))p" name ) 
    echo
done
