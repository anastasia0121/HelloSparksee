#!/bin/bash

max_ore=$( wc -l ../dragon.csv | cut -f1 -d' ' )
max_mine=$( wc -l ../mine.csv | cut -f1 -d' ' )

#|0|0
for((i=0;$i<1000000;i++));
do
    echo -n "|"
    echo -n "$(( $RANDOM % $max_mine ))|"
    echo -n "$(( $RANDOM % $max_ore ))"
    echo
done
