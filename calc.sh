#!/bin/bash

while true; do
	printf "1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Exit\n"
	read -p "Enter you choice :" option
	case $option in
	1)
		echo "Enter two numbers"
		read a b

		echo "sum : $((a + b))"
		;;
	2)
		echo "Enter two numbers"
		read a b

		echo "Diff : $((a - b))"
		;;
	3)
		echo "Enter two numbers"
		read a b

		echo "Product : $((a * b))"
		;;
	4)
		echo "Enter two numbers"
		read a b

		if [ $a -eq 0 ] || [ $b -eq 0 ]; then
			echo "Division by zero is not possible"
		else
			echo "Division : $((a / b))"
		fi
		;;
	5)
		exit 0
		;;
	*)
		echo "Invalid option"
		;;
	esac
done
