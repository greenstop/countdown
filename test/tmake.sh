#!/opt/local/bin/bash
set -x

files="../src/treenode.c"
#files="../src/getword.c"

isExecuted=0

echo "$1"
#compile program
gcc -o ../bin/t.out $1 $files -I ../include 1>errors 2>&1;

if [ $isExecuted -eq 0 ]; then
    #direct output to files
    ../bin/t.out > out_buffer 2>>errors;

    #if output >2000 lines, get only some
    if [ $( wc -l < out_buffer) -gt 2000 ]; then
        head -n 1000 out_buffer > out 2>>errors;
        tail -n 1000 out_buffer >> out 2>>errors;
    else
        cat out_buffer > out;
    fi
fi
