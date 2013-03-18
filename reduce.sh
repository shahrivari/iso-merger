#!/bin/sh

sort $1 | ./reducer > "__reduced.txt"
