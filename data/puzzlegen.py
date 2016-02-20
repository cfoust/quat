#!/usr/bin/python

"""This script takes an input file in which each word is separated by a line and
its (integer) relative frequency is a space away from the word.

As an example:
	word 0\n
is a valid line in the input file.

The input file 'words' comes from a parsing run of Google Ngram I did some time
ago and the 'words.map' is the baked word map for it. Since computing the map 
is somewhat computationally intensive, we just commit the map as line-by-line
changes in 'words' will result in a predictable line change in 'words.map'."""

import csv, random, os, math

# The file containing words and their frequencies (separated by a space)
WORD_FILE = 'words'

# Check to make sure it exists
if not os.path.exists(WORD_FILE):
	print "Word file %s does not exist." % WORD_FILE

words = {}


"""If the map file, which has a cached list of words and their successors, does
not exist, we generate a CSV with that information."""
MAP_FILE = WORD_FILE + '.map'
if not os.path.exists(MAP_FILE):

	print "Map file does not exist for word list '%s'." % WORD_FILE
	
	# Open up the word file
	with open(WORD_FILE) as word_file:

		# Create a temporary array holding each word and its integer frequency
		word_list = []

		# Iterate over all the lines in the word file
		for line in word_file:
			# We strip the string to get the \n off
			parts = line.strip().split()

			# Adds a tuple of (word,frequency) to the list
			word_list.append((parts[0], int(parts[1])))


		# Iterate over all the words we added and find all the possible
		# successors for each word
		for word in word_list:

			# Array of branches off this word
			# Might as well calculate now
			poss = []


			# Look at every word in word_list and see if they differ by
			# 1 letter
			for w in word_list:


				diffs = 0

				# Count the number of differences between the two words
				for i in range(0,4):
					if not word[0][i] == w[0][i]:
						diffs += 1

				# If it's only one, add it to the list of successors
				if diffs == 1:
					poss.append(w[0])

			words[word[0]] = (poss,word[1])

	# Bake it all to a file
	with open(MAP_FILE, 'wb') as map_file:
		map_writer = csv.writer(map_file, delimiter='\t')
		for word in words:
			data = words[word]
			
			map_writer.writerow([word,data[1],','.join(data[0])])
else:
	print "Map exists for word file '%s'." % WORD_FILE

	# Restore the map from the file
	with open(MAP_FILE, 'rb') as map_file:
		map_reader = csv.reader(map_file, delimiter='\t')

		for row in map_reader:
			# The successors are joined by just a comma
			succ = row[2].split(',')

			# If we don't have any successors, keep the array empty
			if len(succ) == 1 and succ[0] == '':
				succ = []

			# Convert the frequency back to an int
			freq = int(row[1])

			# Restore the row to the words dict
			words[row[0]] = (succ,freq)

print "Number of words: %d." % len(words)

"""Solves a pair of four-letter words indicated by start and finish.

Returns an array of steps (including the start and end words) or an array with
no elements if no solution exists."""
def solve(start,finish):
	# We copy the map of words and add some parameters for BFS
	measures = {}
	for word in words:
		data = words[word]

		measures[word] = {
			'distance': -1,
			'predecessor': 'nil',
			'frequency': data[1]
		}

	# This is our queue
	queue = []
	queue.append(start)

	while len(queue) > 0:
		word = queue.pop(0)

		# If we've hit the goal, backtrace the solution
		if word == finish:
			solution = []

			# Add the last word first
			current = word
			solution.append(word)

			# Go backwards through the predecessors until we hit the start word
			while current != start:
				solution.append(measures[current]['predecessor'])
				current = measures[current]['predecessor']
			
			# Reverse the solution to get it in the proper order
			solution.reverse()

			# Return it
			return solution

		# Otherwise, let's look at the successors of this word
		for adjacent in words[word][0]:

			# If the successor node is undiscovered
			if measures[adjacent]['distance'] == -1:

				# Increase its distance based on the current node
				measures[adjacent]['distance'] = measures[word]['distance'] + 1
				# Set its predecessor
				measures[adjacent]['predecessor'] = word

				# Add it to the queue
				queue.append(adjacent)

	# Return no solution; this is only reached if there is no path between
	# the nodes
	return []

# Get the 'easiness' of a word, which is a number that reflects how
# Easy it is to think of words that connect to it
def easiness(word):
	word = words[word]

	frequency = float(word[1])

	# These determine how forgiving the algorithm is to uncommon words
	steps = 4
	threshhold = 30000

	step_size = math.floor(float(threshhold) / float(steps))

	# Keep track of a moving value
	value = 0.0
	frequencies = [words[x][1] for x in word[0]]

	for i in range(steps):
		current_threshhold = threshhold - (step_size * i)
		value += len([f for f in frequencies if f > current_threshhold]) * (pow(10,-i))

	return int(value * pow(10,steps-1))

"""This function returns a word with an integer difficulty higher than difficulty.

It keeps trying until it finds one."""
def getWordOver(difficulty):
	key = random.choice(words.keys())

	while True:
		if easiness(key) >= difficulty:
			break
		else:
			key = random.choice(words.keys())
			word = words[key]
	return key

"""Generates a puzzle with a certain starting and ending difficulty.

'Difficulty' is the inverse of what you would think: lower numbers mean that
a puzzle is more difficult and higher numbers mean it is easier."""
def generate(difficulty):
	first = getWordOver(difficulty)
	second = getWordOver(difficulty)

	while first == second:
		second = getWordOver(difficulty)

	return (first,second,solve(first,second))

## The following generates the puzzles

# Open a handle to the output JS file
puzzles = open('words.js','wb+')

# Number of problems to generate
problems = 1000
difficulty = 4000
puzzles.write('var quat = quat || {};\n')
puzzles.write('quat.puzzles=[')
i = 0
while True:
	# Attempt to generate a puzzle
	problem = generate(difficulty)

	# Pull out the individual parts
	first = problem[0]
	second = problem[1]
	solution = problem[2]
	
	# If we didn't get a solution, try again and don't count it
	if len(solution) == 0 or not solution or len(solution) < 6:
		continue

	i += 1
	problems -= 1

	array = """["%s","%s",%d],""" % (first, second, len(solution))
	puzzles.write(array)

	if problems == 0:
		break
puzzles.write(']')

## Now we write out the dictionary
puzzles.write('\nquat.dictionary={')
for word in words:
	puzzles.write("%s:1," % word)
puzzles.write('}')
