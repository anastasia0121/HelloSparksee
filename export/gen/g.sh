#!/bin/bash

#0|Untilopulus0|2003|2003|2003|2003|Brilliant
for((i=0;$i<10;i++));
do
    echo -n "${i}|"
    echo -n $( sed -n "$(( $RANDOM % 280))p" name )"|" 
    echo -n "$(( $RANDOM % 2005))|"
    echo -n "$(( $RANDOM % 2005))|"
    echo -n "$(( $RANDOM % 2005))|"
    echo -n "$(( $RANDOM % 2005))|"
    echo -n $( sed -n "$(( $RANDOM % 99170))p" /usr/share/dict/words ) 
    echo
done
