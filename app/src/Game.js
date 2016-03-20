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
		if (word.length != 4) {
			return;
		}

		// Check if the word exists, and if it does, add it
		if (!(word in this._dict)) {
			this._addMessage(word.toUpperCase() + " IS NOT A WORD");
			return false;
		}

		if (word == this.getCurrentWord()) {
			return false;
		}

		this._moves++;

		// Push the word 
		this._steps.push(word);

		// Check if we're at the goal
		if (this.atGoal()) {
			this._state = this.states.DONE;
			this.stopTime();
		}

		return true;
	},

	init: function(start, end, par, special, specialText) {
		this._super();

		this._dict = quat.dictionary;
		this._start = start;
		this._end = end;
		this._par = par;
		this._steps = [start];
		this._moves = 0;
		this._special = special;
		this._specialText = specialText || "";
		this._timeStarted = false;

		if (special) {
			this._addMessage(specialText.toUpperCase(), true);
		}

		this._state = this.states.NOT_STARTED;
	},

	isDone: function() {
		return this._state == this.states.DONE;
	},

	inProgress: function() {
		return this._state == this.states.PLAYING;
	},

	/**
	 * Whether or not this puzzle is special (has a special message.)
	 */
	isSpecial: function() {
		return this._special;
	},

	getSpecialText: function() {
		return this._specialText;
	},

	/**
	 * Get the current four-letter word (the last one in the solution.)
	 */
	getCurrentWord: function() {
		return this._steps[this._steps.length - 1];
	},

	getPreviousWord: function() {
		return this._steps[this._steps.length - 2];
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
		return this._par;
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
			this._moves++;
		}
	},


	timeStarted: function() {
		return this._timeStarted;
	},

	/**
	 * Start the time counter that 
	 * @return {[type]} [description]
	 */
	startTime: function() {
		this._timeStarted = true;
		this._state = this.states.PLAYING;
		this._startTime = new Date();
	},

	stopTime: function() {
		var difference = new Date() - this._startTime;

		if (isNaN(difference)) {
			return;
		}

		this._timeStarted = false;
		if (this._totalTime) {
			this._totalTime += difference;
		} else {
			this._totalTime = difference;
		}
	},

	toObject: function() {
		this.stopTime();
		this.startTime();
		return {
			start: this._start,
			steps: this._steps,
			end: this._end,
			par: this._par,
			time: this._totalTime,
			special: this._special,
			specialText: this._specialText,
			state: this._state,
			moves: this._moves
		};
	},

	fromObject: function(obj) {
		this._start = obj.start;
		this._end = obj.end;
		this._par = obj.par;
		this._totalTime = obj.time;
		this._special = obj.special;
		this._specialText = obj.specialText;
		this._moves = obj.moves;
		this._state = this.states.PLAYING;

		if (this._special) {
			this._addMessage(this._specialText.toUpperCase(), true);
		}

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

	getPars: function() {
		return this._pars;
	},

	/**
	 * Get this user's number of points.
	 * @return {number} Number of points.
	 */
	getPoints: function() {
		return this._points;
	},

	getPuzzlesPlayed: function() {
		return this._puzzlesPlayed;
	},

	getTimePlayed: function() {
		return this._timePlayed;
	},

	getAveragePuzzleTime: function() {
		return this._averageSolveTime;
	},

	init: function() {
		this._super();
		this._theme = "WASH";
		this._themeProgress = {};
		this._timePlayed = 0;
		this._puzzlesPlayed = 0;
		this._pars = 0;
		this._averageSolveTime = 0;
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

		puzzle.stopTime();
		
		var par = puzzle.getPar(),
			steps = puzzle.getSteps().length,
			points = 0;

		// If the user made par
		if (par == steps) {
			points = par * 2;
			this._pars += 1;
			this._addMessage('MADE PAR!');
		}
		else {
			points = par;
		}


		this._puzzlesPlayed += 1;
		this._averageSolveTime = (this._timePlayed + puzzle.getTime()) / this._puzzlesPlayed;
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

	getTheme: function() {
		return this._theme;
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

	getThemeProgress: function() {
		// If the user doens't already have progress on this theme, zero it out
		if (!(this._theme in this._themeProgress)) {
			this._themeProgress[this._theme] = 0;
		}

		return this._themeProgress[this._theme];
	},

	getThemeProgressForTheme: function(name) {
		if (!(name in this._themeProgress)) {
			return 0;
		}

		return this._themeProgress[name];
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
			puzzlesPlayed: this._puzzlesPlayed,
			pars: this._pars,
			averageSolveTime: this._averageSolveTime
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
		this._averageSolveTime = obj.averageSolveTime;
		this._pars = obj.pars;
		return this;
	}
});

/* Defines a general model for operating on QUAT puzzles to move the business
logic out of the display logic.*/
quat.Game = quat.MessageQueue.extend({

	/**
	 * @return {boolean} Whether or not we can load local persistent data.
	 */
	canLoadFromLocal: function() {
		if (cc.sys.isNative) {
			var path = this._savePath;
			return jsb.fileUtils.isFileExist(path);
		} else {
			return 'quat' in cc.sys.localStorage;
		}
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
			var colors = this.themes[keys[i]].colors, // This theme's colors
				colorKeys = Object.keys(colors); // Their keys

			for (var j = 0; j < colorKeys.length; j++) {
				var colorKey = colorKeys[j];

				// Only translate into a cc.color if it's a string
				// Maybe make this check to see if there's a #
				if (typeof colors[colorKey] == "string") {
					colors[colorKey] = cc.color(colors[colorKey]);
				}
			}
		}

		// Basic data keeping values
		this._puzzle = null;
		this._user = null;
		this._restored = false;

		if (cc.sys.isNative) {
			this._savePath = jsb.fileUtils.getWritablePath() + 'out.json';
		}
	},

	/**
	 * Gets the current puzzle the user can modify.
	 */
	getPuzzle: function() {
		return this._puzzle;
	},

	/**
	 * Sets the current theme. This does not change the GUI, it's just for
	 * recording purposes.
	 */
	setTheme: function(name) {
		// If the puzzle is special, we gotta set back their theme progress
		// because you can't play that puzzle on the new theme
		
		var otherTheme = ((this._puzzle.isSpecial()) && (this._user.getTheme() != name));

		if (otherTheme) {
			this._user.setThemeProgress(this._user.getThemeProgress() - 1);
		}

		this._user.setTheme(name);

		// If the user was solving a special puzzle but chose a new theme
		if (otherTheme) {
			this.newPuzzle();
		}
	},

	/**
	 * Gets a theme object from the list of themes.
	 * @param  {String} Name of theme to get. 
	 * @return {Object} Theme object corresponding to this name.
	 */
	getTheme: function(name) {
		if (!(name in this.themes)) {
			return null;
		}

		return this.themes[name];
	},

	getThemes: function() {
		return this.themes;
	},

	getUser: function() {
		return this._user;
	},

	loadFromLocal: function() {
		
		var data = null;

		// If we're native, load from a file.
		if (cc.sys.isNative) {
			var path = this._savePath;

			// If the file exists, attempt to load it
			if (jsb.fileUtils.isFileExist(path)) {
				// Load and parse the file's data
	            var temp = jsb.fileUtils.getValueMapFromFile(path),
	            	file = JSON.parse(temp.data);

	            data = file;
	        }
		// Otherwise, try local storage.
		} else {
			data = JSON.parse(cc.sys.localStorage.getItem('quat'));
		}
		this._user = new quat.User().fromObject(data.user);
		this._puzzle = new quat.Puzzle().fromObject(data.puzzle);
		this._restored = true;
	},

	/**
	 * Gets a new puzzle for the user to play.
	 */
	newPuzzle: function() {
		var user = this._user,
			theme = this.getTheme(user.getTheme()),
			progress = user.getThemeProgress();

		if (progress < theme.puzzles.length) {
			// Grab the special puzzle from this theme
			var puzzle = theme.puzzles[progress];

			// Increment theme progress
			user.setThemeProgress(progress + 1);

			// Initialize the puzzle object
			this._puzzle = new quat.Puzzle(puzzle.start, puzzle.end, puzzle.par, true, puzzle.text);
		} else  {
			// Generate a random key
			var key = Math.floor(Math.random() * this.puzzles.length);
			var puzzle = this.puzzles[key];
			this._puzzle = new quat.Puzzle(puzzle[0],puzzle[1],puzzle[2], false);
		}

		this.saveToLocal();
	},

	reset: function() {
		this._user = new quat.User();
	},

	saveToLocal: function() {
		var obj = {
			user: this._user.toObject(),
			puzzle: this._puzzle.toObject()
		};

		var out = JSON.stringify(obj);

		if (cc.sys.isNative) {
			// todo: some error checking
			jsb.fileUtils.writeToFile({data:out}, this._savePath);
		} else {
			cc.sys.localStorage.setItem('quat', out);
		}
		
	},

	wasRestored: function() {
		return this._restored;
	}
});

