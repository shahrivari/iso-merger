#!/bin/bash

for f in /cygdrive/x/network/*.b
do
	echo $f
	for i in 4 5 6 
	do
		time (cat $f-$i.res | ./saeed.exe -s$i > mapped.txt; sort mapped.txt | ./reducer.exe >$f-$i.res.sorted ; wc -l $f-$i.res.sorted)
		tail -n2 $f-$i.out
		echo =======================
	done
done
