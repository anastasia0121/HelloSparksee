#!/bin/bash

max_dragon=$( wc -l ../dragon.csv | cut -f1 -d' ' )
max_mine=$( wc -l ../mine.csv | cut -f1 -d' '  )

#Dragon|0|0
for((i=0;$i<10000;i++));
do
    echo -n "Dragon|"
    echo -n "$(( $RANDOM % $max_dragon ))|"
    echo -n "$(( $RANDOM % $max_mine ))"
    echo
done
