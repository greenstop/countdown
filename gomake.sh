#!/opt/local/bin/bash 

set -x

# nmap <c-s> :wa<cr>:silent !make 1>../data/errors 2>&1 && ../bin/countdown > ../data/out_buffer 2>>../data/errors && ../data/buffer_out.sh<cr>:redraw!<cr>

errors=../data/errors
out=../data/out_buffer
out_less=../data/out
bin=../bin

# change directory
cd $1
basedir="$(basename $(pwd))"

# set program name
case "$basedir" in
    test)
        main=tcountdown
        ;;
    src)
        main=countdown
        ;;
    *)
        main=program_out
        ;;
esac


#if output >2000 lines, get only some
bufferOut () {
    if [ $( wc -l < $out) -gt 2000 ]
        then
            head -n 1000 $out > $out_less 2>> $errors;
            tail -n 1000 $out >> $out_less 2>> $errors;
        else
            cat $out > $out_less;
    fi
}

#execute make
if [ -f makefile ]
    then
    echo "In \"$1\", there is a makefile."
    make > $errors 2>&1
    $bin/$main > $out 2>> $errors
    if [ $basedir == "test" ]
        then
        grep "Assertion" $errors >> $out
    fi
    bufferOut
    else
    echo "In \"$1\", there is no makefile."
fi


