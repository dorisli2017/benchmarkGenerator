for i in ../../combineFiles/all/*.ct;
do
    for j in ../../combineFiles/all/*.ct;
    do
    	for k in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0
		do
			for l in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0
			do
				for m in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0 1.2 1.4 1.6 1.8 2 4 8
				do
					for s in 1 100 1000 20 200 2000
					do
					./con $i $j $k $l $m $s 
					done
				done
			done
		done
    done
done    
