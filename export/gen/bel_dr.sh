#!/bin/bash

max_dragon=$( ./dr.sh | wc -l )
max_mine=$( ./mine.sh | wc -l )

#Dragon|0|0
for((i=0;$i<10;i++));
do
    echo -n "Dragon|"
    echo -n "$(( $RANDOM % $max_dragon ))|"
    echo -n "$(( $RANDOM % $max_mine ))"
    echo
done
