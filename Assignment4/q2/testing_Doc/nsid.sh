#!/bin/sh

# Student Name: Yinsheng Dong
# Student Number: 11148648
# NSID: yid164
# Lecture Section: CMPT 214

# the function that check if the input is correct nisd
function is_nsid
{
    # take names before number
    name=${var%%[0-9]*}
    # take number after letters
    num=${var##*[a-z]}

    # the name and num should be 3 digits
    if [[ "${#name}" = 3 && "${#num}" = 3 ]];then
        # the name should only contain letters and the num should only contain number
        if [[ $name =~ ^[a-zA-Z]+$ && $num =~ ^[0-9]+$ ]];then
        # if correct, return 0 otherwise return 1
            return 0
        else
            return 1
        fi
    else
        return 1
    fi
}

# name the variable is from user input
var=$@

# if user input number is 0 then read each potential NSID from standard input
if [[ $# = 0 ]];then
    # searching the standard input
    for var in $(cat $*)
    do
        is_nsid $var
        # if is_nsid return 0 echo valid, otherwise echo not valid
        s=`echo $?`
        if [ $s = 0 ];then
            echo $var" is valid"
        else
            echo '"'$var'"'" is not valid"
        fi
    done
    # exit from $?
    exit $s

# if user input number is 1, then try to know if the input is a file or just input
elif [ $# = 1 ];then
    # if the file exsist then
    if [[ -f $var ]];then
    # scan the file by cat command
    for var in $(cat $var)
    do
        # this is the last param that in the file for testing if it correct or not, it will decide the final exit
        last=`cat $* | awk 'END {print}'`
        is_nsid $var
        #if is_nsid return 0 echo valid, otherwise echo not valid
        s=`echo $?`
        if [[ $s = 0 ]];then
            echo $var" is valid"
        else
            echo '"'$var'"'" is not valid"
        fi
        # let last param from the file be the exit
        if [[ $last = $var ]];then
            exit $s;
        fi
        done
    # if it is only a input
    else
        # just call the is_nsid with the param
        is_nsid $var
        s=`echo $?`
        if [[ $s = 0 ]];then
            echo $var" is valid"
        else
            echo '"'$var'"'"is not valid"
        fi
        exit $s
    fi
# if user input is more than 1
else
    #scan them an try to output them
    for var in $*
    do
    is_nsid $var
    s=`echo $?`
    if [[ $s = 0 ]];then
        echo $var" is valid"
    else
        echo '"'$var'"'"is not valid"
    fi
    done
    exit $s

fi
