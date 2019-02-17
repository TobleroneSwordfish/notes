from __future__ import print_function

import sys

def product(numbers):
    """Function to return the product of two numbers
    Params:
        numbers: List of two numbers to be multiplied
    Returns:
        product of two numbers
    """
    #Write your solution here
    return float(numbers[0]) * float(numbers[1])

numbers = sys.argv[1:] # sys.argv contains the arguments passed to the program
print(product(numbers))