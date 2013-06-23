#!/bin/sh

#time sort $1 | ./reducer > "__reduced.txt"
wc -l $1
time ( echo "nautying..."; time cat $1 |./saeed -s $2 > nautied.txt; echo "sorting"; time sort nautied.txt | ./reducer > reduced.txt;echo "=============")
wc -l reduced.txt