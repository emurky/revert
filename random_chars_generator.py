import random
import string

def	get_random_string(length):
	chars = string.printable
	random_string = ''.join(random.choice(chars) for i in range(length))
	print(random_string)

get_random_string(5000000)
