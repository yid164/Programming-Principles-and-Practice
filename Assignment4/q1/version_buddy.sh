#!/bin/sh

# Name: Yinsheng Dong
# Student Number: 11148648
# NSID: yid164
# Lecture Section: CMPT 214

# name the input variable
var=$@
# the error message
errorMessage="usage: version_buddy <filename>\n where <filename> is of the form Name_Major_Minor.Extension\n and does not contain any whitespace"

# get the name from variable
name=${var%%_*}
x=${var#*_}

#get the ext from the varialbe
ext=${var##*.}

#get the major from the variable
major=${x%_*}
y=${var%.*}

#get the minor from the variable
minor=${y##*_}



# if the input number not equal to 1 get error message and terminate
if [ $# != 1 ];then
    echo $errorMessage
    exit 1
fi

# if the variable is '-v' get option not reconized and error message
if [[ $var = "-v" ]];then
    echo "option "$var" not recognized"
    echo $errorMessage
    exit 1
fi

# if the file name has already exists, output exists
if [[ -e ${name}.${major}.${minor}.${ext} ]];then
    echo "destination file "${name}.${major}.${minor}.${ext}" already exists"
    exit 4
fi

# if the name contains direction name '/' output some error message
failName=`echo $name | grep '/'`
if [[ $failName = $name ]];then
    echo "file must be in the current working directory"
    exit 2
fi






# if the input number is correct then check name major minor and ext
# check if the name only contains a-z A-Z 0-9 or '-'
if [[ $name =~ ^[a-zA-Z0-9'-']+$ ]];then

    # check if the major only contains 0-99 digits
    if [[ $major =~ ^[0-99]+$ ]];then

        # check if the minor only contains 0-99 digits
        if [[ $minor =~ ^[0-99]+$ ]];then

            # check if the ext contains correct text
            if [[ $ext =~ ^[0-9a-zA-Z]+$ ]];then

                # check if the variable exists or not
                if [ -e $var ];then

                    # set the variable name to var1 use mv command to change name and output successful message
                    var1=${name}.${major}.${minor}.${ext}
                    mv ${var} ${var1}
                    echo ${var} "->" ${var1}
                else
                    echo $var" must exist in the current working directory"
                    exit 3
                    fi
            else
                echo "filename is not well-formed"
                exit 2
                fi

        else
            echo "filename is not well-formed"
            exit 2
            fi
    else
        echo "filename is not well-formed"
        exit 2
        fi
else
    echo "filename is not well-formed"
    exit 2
    fi

