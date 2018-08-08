#!/bin/bash
im1_files=(../../combineFiles/small/small1/*.ct)
im2_files=(../../combineFiles/small/small2/*.ct)

for ((i=0;i<=${#im1_files[@]};i++));
do
    for k in 0.1 #0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0
    do
	for l in 0.1 #0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0
	do
            for m in 0.1 #0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0 1.2 1.4 1.6 1.8 2 4 8
	    do
	        for s in 1 #100 1000 20 200 2000
		do
		    ./con "${im1_files[i]}" "${im2_files[i]}" $k $l $m $s 500
		done
	    done
	done
    done
done    
