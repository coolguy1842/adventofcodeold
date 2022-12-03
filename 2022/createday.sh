#!/bin/bash

createday() {
    day=$1

    mkdir -p dayinputs/$day

    ./aoc read -o -p $PWD/dayinputs/$day/puzzle.md -d $day > /dev/null
    ./aoc download -o -i $PWD/dayinputs/$day/input -d $day
}

if [[ $1 == "" ]]; then
    folderCount=`find dayinputs/ -type d | wc -l`

    createday $folderCount
else
    regex='^[0-9]+$'
    if ! [[ $1 =~ $regex ]]; then
        echo "error: Not a number"
        exit 1
    fi

    createday $1
fi
