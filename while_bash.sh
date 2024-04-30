#!/bin/bash

echo "Enter the no : " 
read num

i=0
sum=0

while [ $i -lt $num ]
do
    sum=$(($sum+$i))
    i=$(($i+1))
done

echo "SUM : $(($sum))"