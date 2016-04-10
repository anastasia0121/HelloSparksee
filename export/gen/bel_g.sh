#!/bin/bash

max_g=$( ./g.sh | wc -l )
max_mine=$( ./mine.sh | wc -l )

#Miner|0|0
for((i=0;$i<10;i++));
do
    echo -n "Miner|"
    echo -n "$(( $RANDOM % $max_g ))|"
    echo -n "$(( $RANDOM % $max_mine ))"
    echo
done
