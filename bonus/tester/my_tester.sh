#!/bin/bash

if [ "$#" -eq 1 -a "$1" = "-h" ]; then
    echo -e "$0 [BIN] [DIR]"
    echo -e "\t[BIN] project binary"
    echo -e "\t[DIR] a directory containing '.cor' files to test"
    exit 0
fi

if [ "$#" -ne 2 ]; then
    echo "Error : incorrect number of arguments (it must be 2 but it is $#)."
    exit 84
fi

if [ ! -x "$1" ]; then
    echo "Error : first parameter must be an executable."
    exit 84
fi

if [ ! -d "$2" ]; then
    echo "Error : second parameter must be a directory."
    exit 84
fi

total=$(find "$2" -type f -name "*.cor" | wc -l)
test_nb=0

for file in $(find "$2" -type f -name "*.cor")
do
    ("./$1" "$file" "$file") > /dev/null 2>&1
    ret="$?"

    ((test_nb+=1))

    echo -e "\e[33m[ Test n°$test_nb - executing \"$file\" ]\e[0m"
    if [ $ret -eq 0 ]; then
        echo -e "\e[32mRETURN VALUE : $ret\e[0m\n"
    else
        echo -e "\e[31mRETURN VALUE : $ret\e[0m\n"
    fi
done

echo -e "\e[34m[ TOTAL TESTS : $total ]\e[0m"

exit 0
