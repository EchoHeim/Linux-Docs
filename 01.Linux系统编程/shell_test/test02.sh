#!/bin/bash
#if...else...

echo "input word1:"
read word1
echo "input word2:"
read word2
echo "input word3:"
read word3
if [ "$word1" = "$word2" ]; then
	echo "match 1 and 2!"
elif [ "$word1" = "$word3" ];then
	echo "match 1 and 3!"
elif [ "$word2" = "$word3" ];then
	echo "match 2 and 3!"
elif [ "$word1" = "$word2" -a "$word2" = "$word3" ];then
	echo "match 1,2 and 3!"
else 
	echo "no match!"
fi

