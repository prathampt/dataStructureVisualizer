#!/bin/bash

# Prompt the user for input
echo "Enter a number between 1 and 4 (or 0 to Exit):"
echo "1) Menu driven Graph"
echo "2) Menu driven Binary Tree for Int"
echo "3) Menu driven Binary Tree for String"
echo "4) Menu driven AVL Tree"
echo "0) Exit"
read num

# Switch-case statement
case $num in
    1)
        echo "You entered 1."
        gcc graph/main.c -lGL -lGLU -lglut -lm -g
        ;;
    2)
        echo "You entered 2."
        gcc binarySearchTreeForInt/main.c -lGL -lGLU -lglut -lm -g
        ;;
    3)
        echo "You entered 3."
        gcc binarySearchTreeForString/main.c -lGL -lGLU -lglut -lm -g
        ;;
    4)
        echo "You entered 4."
        gcc AVLtreeForString/main.c -lGL -lGLU -lglut -lm -g
        ;;
    0)
        echo "Exiting..."
        exit
        ;;
    *)
        echo "Invalid input! Please enter a number between 0 and 4."
        exit 1
        ;;
esac

# Execute the compiled program
./a.out

# Clean up the compiled file
rm a.out
