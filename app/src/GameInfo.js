var quat = quat || {};

/* Defines a general model for operating on QUAT puzzles to move the business
logic out of the display logic.*/
quat.GameInfo = function() {
	
};

quat.GameInfo = Class.extend({
	init: function() {
		// Pulls from the global references to quat puzzles and 
		this.puzzles = quat.puzzles;
		this.dictionary = quat.dictionary;

		this.points = 0;
	},
	newPuzzle: function() {
		// Generate a random key
		var key = Math.floor(Math.random() * this.puzzles.length);
		var puzzle = this.puzzles[key];

		// The current steps shown on the 'board'
		this.currentSteps = [puzzle[0]];

		// The goal we're looking for
		this.goal = puzzle[1];

		// The number of steps the computer got
		this.stepsToBeat = puzzle[2];
	},

	/**
	 * Get the word the user can branch off of.
	 * @return {String} The four-letter word at the end of the current solution.
	 */
	getCurrentWord: function() {
		return this.currentSteps[this.currentSteps.length - 1];
	},


	getGoal: function() {
		return this.goal;
	},

	getPar: function() {
		return this.stepsToBeat - 1;
	},

	/**
	 * Gets the current solution in its entirety.
	 * @return {Array of Strings} The current steps, including the start word.
	 */
	getCurrentSteps: function() {
		return this.currentSteps;
	},

	/**
	 * Delete the most recent step in the solution.
	 */
	goBack: function() {
		if (this.currentSteps.length > 1) {
			// Slice off the last step in the array
			this.currentSteps = this.currentSteps.slice(0,-1);
		}
	},

	/**
	 * Adds a word to the solution. If the word is more than one different
	 * than the current word or does not exist in the dictionary, we do not
	 * add it and return false.
	 * @param {String} word Four-letter word.
	 * @return {boolean} whether or not the word got added successfully.
	 */
	addWord: function(word) {
		// Check if the word exists, and if it does, add it
		if (!this.dictionary[word]) {
			return false;
		}

		// Calculate the number of differences between the words
		// (This might not be necessary if the GUI restricts it)
		// It might waste battery over time
		var lastWord = this.getCurrentWord(),
			differences = 0;
		for (var i = 0; i < word.length; i++) {
			if (word[i] != lastWord[i]) {
				differences++;
			}
		}

		if (differences != 1) {
			return false;
		}

		this.currentSteps.push(word);

		if (this.atGoal()) {
			var points = (this.getPar() == this.currentSteps.length - 1) ? this.getPar() * 2 : this.getPar();
			this.pointsAdded = points;
			this.points += points;
		}

		return true;
	},


	/**
	 * Gets whether the current word is the goal word or not.
	 * @return {boolean}  Whether the current word is the goal word or not.
	 */
	atGoal: function() {
		return this.getCurrentWord() == this.goal;
	}
});

