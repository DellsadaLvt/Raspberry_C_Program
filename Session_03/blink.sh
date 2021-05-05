#!/bin/sh


gpio mode 5 output
gpio write 5 0

while true
do
	gpio write 5 1
	sleep 2
	gpio write 5 0
	sleep 2
done
