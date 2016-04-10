#!/bin/bash

max_ore=$( ./dr.sh | wc -l )
max_mine=$( ./mine.sh | wc -l )

#|0|0
for((i=0;$i<10;i++));
do
    echo -n "|"
    echo -n "$(( $RANDOM % $max_mine ))|"
    echo -n "$(( $RANDOM % $max_ore ))"
    echo
done
