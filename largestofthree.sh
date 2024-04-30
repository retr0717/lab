#!/bin/bash

echo "Enter the num1, num2, num3 : "
read num1
read num2
read num3

if [ $num1 -gt $num2 ] && [ $num1 -gt $num3 ]
then
    echo "Num1 is greater : $(($num1))"
elif [ $num2 -gt $num1 ] && [ $num2 -gt $num3 ]
then
    echo "Num2 is greater : $(($num2))"
else
    echo "Num3 is higher : $(($num3))"
fi