#!/bin/bash
#case语句

echo "Enter A,B or C:"
read val
case $val in
	A|a) echo "A is going...";;
	B|b) echo "B is going...";;
	C|c) echo "C is going...";;
	*) echo "not A,B,C";;
esac
