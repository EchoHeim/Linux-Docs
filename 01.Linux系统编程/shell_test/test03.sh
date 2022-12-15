#!/bin/bash
#循环

#for 变量 in 序列表 do ...done
val=0
for val in 1 2 3 4 5 ;do
	echo "$val"
done

echo "  "

#until 条件 do... done
until [ $val -gt 10 ];do	#直到val大于10跳出循环
	echo $val
	val=`expr $val + 1`
done

echo " "

#while 条件 do... done
while [ $val -gt 5 ];do
	echo $val
	val=`expr $val - 1`
done
