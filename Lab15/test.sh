#!/bin/sh

PIPE_CNT=2

for (( i = 0; i < $PIPE_CNT; i++ )); do
    mkfifo "pipe_$i"
done

echo "use ^C to exit XDD"

while [ 1 ]; do
    for (( i = 0; i < $PIPE_CNT; i++ )); do
        echo $RANDOM >> "pipe_$i"
        sleep 0.5
    done
done
