#!/bin/sh
# by Yinsheng Dong
# Student Number: 11148648
# NSID: yid164
# Lecture: CMPT 214


# cut 4-7 col from substrates.txt to temp1.txt
cut -f 4-7 substrates.txt >temp1.txt;

# cut 1-3 col from substrates.txt to temp2.txt
cut -f 1-3 substrates.txt>temp2.txt

# cut 8-10 col form substrates.txt to temp3.txt
cut -f 8-10 substrates.txt>temp3.txt

# paste all of temp file to substrates2.txt
paste temp1.txt temp2.txt temp3.txt >substrates2.txt

# remove all temporary files
rm -f temp1.txt temp2.txt temp3.txt
