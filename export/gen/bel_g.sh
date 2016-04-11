#!/bin/bash

max_g=$( wc -l ../gnome.csv | cut -f1 -d' ' )
max_mine=$( wc -l ../mine.csv | cut -f1 -d' ' )

#Miner|0|0
for((i=0;$i<1000000;i++));
do
    echo -n "Miner|"
    echo -n "$(( $RANDOM % $max_g ))|"
    echo -n "$(( $RANDOM % $max_mine ))"
    echo
done
