var quat = quat || {};

quat.MessageQueue = Class.extend({
	_addMessage: function(message, special) {
		var special = special || false;
		this._messages.push({
			text: message,
			special: special
		});
	},

	init: function() {
		this._messages = [];
	},

	hasMessage: function() {
		return this._messages.length > 0;
	},

	/**
	 * Consume a message from the message queue.
	 * @return {[type]} [description]
	 */
	consumeMessage: function() {
		if (!this.hasMessage()) {
			return null;
		}

		var message = this._messages[this._messages.length - 1];
		this._messages = this._messages.slice(0,-1);
		return message;
	}
});

quat.Puzzle = quat.MessageQueue.extend({
	states: {
		NOT_STARTED: 0,
		PLAYING: 1,
		DONE: 2
	},

	atGoal: function() {
		return this.getGoal() == this.getCurrentWord();
	},

	/**
	 * Add a word to the solution. Checks to see if it is a valid move. Returns
	 * true if the word was added successfully and false if it was not.
	 * @param {string} word Four-letter word.
	 */
	addWord: function(word) {
		// Check if the word exists, and if it does, add it
		if (!(word in this._dict)) {
			this._addMessage(word.toUpperCase() + " IS NOT A WORD");
			return false;
		}

		// Push the word 
		this._steps.push(word);

		// Check if we're at the goal
		if (this.atGoal()) {
			this._state = this.states.DONE;
			this.stopTime();
		}

		return true;
	},

	init: function(start, end, par, special) {
		this._super();

		this._dict = quat.dictionary;
		this._start = start;
		this._end = end;
		this._par = par;
		this._steps = [start];
		this._special = special;
		this._state = this.states.NOT_STARTED;
	},

	isDone: function() {
		return this._state == this.states.DONE;
	},

	/**
	 * Whether or not this puzzle is special (has a special message.)
	 */
	isSpecial: function() {
		return this._special;
	},

	/**
	 * Get the current four-letter word (the last one in the solution.)
	 */
	getCurrentWord: function() {
		return this._steps[this._steps.length - 1];
	},

	/**
	 * Gets the goal (four-letter word) for this puzzle.
	 */
	getGoal: function() {
		return this._end;
	},

	/**
	 * Gets the number of moves the user needs to make to get par.
	 */
	getPar: function() {
		return this._par - 1;
	},

	/**
	 * Gets the current solution in its entirety.
	 * @return {Array of Strings} The current steps, including the start word.
	 */
	getSteps: function() {
		return this._steps;
	},

	/**
	 * Get the total amount of time this puzzle has taken so far (since the last
	 * time stopTime() was called).
	 */
	getTime: function() {
		return this._totalTime;
	},

	/**
	 * Delete the most recent step in the solution.
	 */
	goBack: function() {
		if (this._steps.length > 1) {
			// Slice off the last step in the array
			this._steps = this._steps.slice(0,-1);
		}
	},

	/**
	 * Start the time counter that 
	 * @return {[type]} [description]
	 */
	startTime: function() {
		this._state = this.states.PLAYING;
		this._startTime = new Date();
	},

	stopTime: function() {
		var difference = new Date() - this._startTime;

		if (this._totalTime) {
			this._totalTime += difference;
		} else {
			this._totalTime = difference;
		}
	},

	toObject: function() {
		this.stopTime();
		return {
			start: this._start,
			steps: this._steps,
			end: this._end,
			par: this._par,
			time: this._totalTime,
			special: this._special,
			state: this._state,
		};
	},

	fromObject: function(obj) {
		this._start = obj.start;
		this._end = obj.end;
		this._par = obj.par;
		this._totalTime = obj.time;
		this._special = obj.special;
		this._steps = obj.steps;
		return this;
	}
});

quat.User = quat.MessageQueue.extend({
	/**
	 * Add points to this user's profile.
	 * @param {[type]} points [description]
	 */
	addPoints: function(points) {
		// Capture how many points we had before
		var before = this._points;

		this._points += points;

		// Capture how many points we had before
		var after = this._points;

		for (var theme in quat.themes) {
			var obj = quat.themes[theme];

			// Only true if the user just unlocked this theme
			if ((obj.unlock > before) && (obj.unlock <= after)) {
				this._addMessage('UNOOCKED THEME "' + theme + '"');
			}
		}
	},

	/**
	 * Get this user's number of points.
	 * @return {number} Number of points.
	 */
	getPoints: function() {
		return this._points;
	},

	init: function() {
		this._super();
		this._theme = "NONE";
		this._themeProgress = {};
		this._timePlayed = 0;
		this._puzzlesPlayed = 0;
		this._points = 0;
	},

	/**
	 * Takes a completed puzzle and recomputes the user's stats.
	 * @param  {quat.Puzzle} puzzle
	 */
	registerPuzzle: function(puzzle) {
		// Ensure the puzzle is done.
		if (!puzzle.isDone()) {
			return false;
		}

		var par = puzzle.getPar(),
			points = 0;

		// If the user made par
		if (par == puzzle.getSteps().length - 1) {
			points = par * 2;
			this._addMessage('MADE PAR!');
		}
		else {
			points = par;
		}

		this._puzzlesPlayed += 1;
		this._timePlayed += puzzle.getTime();
		this.addPoints(points);
	},

	/**
	 * Sets this user's current theme.
	 * @param {[type]} theme [description]
	 */
	setTheme: function(theme) {
		if (theme in quat.themes) {
			this._theme = theme;
		}
		else {
			this._addMessage("TRIED TO CHANGE TO NONEXISTENT THEME " + theme);
		}
	},

	/**
	 * Sets the number (theme progress) associated with the theme. This refers
	 * to the current index of the NEXT valid special puzzle in the theme that
	 * the user has not seen before, or -1 if they have finished all of them.
	 * @param {number} number Index of next puzzle.
	 */
	setThemeProgress: function(number) {
		this._themeProgress[this._theme] = number;
	},

	/**
	 * Turns this User instance into a json object.
	 * @return {JSON} Key-value representation of this User instance.
	 */
	toObject: function() {
		return {
			points: this._points,
			theme: this._theme,
			themeProgress: this._themeProgress,
			timePlayed: this._timePlayed,
			puzzlesPlayed: this._puzzlesPlayed
		};
	},

	/**
	 * Restores this instance to the one described in the JSON object obj.
	 * @param  {[type]} obj [description]
	 */
	fromObject: function(obj) {
		this._points = obj.points;
		this._theme = obj.theme;
		this._themeProgress = obj.themeProgress;
		this._timePlayed = obj.timePlayed;
		this._puzzlesPlayed = obj.puzzlesPlayed;
		return this;
	}
});

/* Defines a general model for operating on QUAT puzzles to move the business
logic out of the display logic.*/
quat.Game = quat.MessageQueue.extend({
	canLoadFromLocal: function() {
		return 'quat' in localStorage;
	},

	init: function() {
		this._super();

		// Pulls from the global references to quat puzzles and 
		this.puzzles = quat.puzzles;
		this.dictionary = quat.dictionary;
		this.themes = quat.themes;

		// Go through and bake all of the themes' colors into cc.colors
		var keys = Object.keys(this.themes);
		this.themeNames = keys;
		for (var i = 0; i < keys.length; i++) {
			var colors = this.themes[keys[i]].colors;
			var colorKeys = Object.keys(colors);
			for (var j = 0; j < colorKeys.length; j++) {
				var colorKey = colorKeys[j];
				colors[colorKey] = cc.color(colors[colorKey]);
			}
		}

		this._puzzle = null;
		this._user = null;
		this._restored = false;
	},

	getPuzzle: function() {
		return this._puzzle;
	},

	getTheme: function(name) {
		if (!(name in this.themes)) {
			return null;
		}

		return this.themes[name];
	},

	getUser: function() {
		return this._user;
	},

	loadFromLocal: function() {
		var data = JSON.parse(localStorage['quat']);
		this._user = new quat.User().fromObject(data.user);
		this._puzzle = new quat.Puzzle().fromObject(data.puzzle);
		this._restored = true;
	},

	newPuzzle: function() {
		// Generate a random key
		var key = Math.floor(Math.random() * this.puzzles.length);
		var puzzle = this.puzzles[key];

		this._puzzle = new quat.Puzzle(puzzle[0],puzzle[1],puzzle[2], false);

		this.saveToLocal();
	},

	reset: function() {
		this._user = new quat.User();
	},

	saveToLocal: function() {
		var obj = {
			user: this._user.toObject(),
			puzzle: this._puzzle.toObject()
		}
		localStorage['quat'] = JSON.stringify(obj);
	},

	wasRestored: function() {
		return this._restored;
	}
});

