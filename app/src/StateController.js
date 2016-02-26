var quat = quat || {};

quat.StateController = Class.extend({
	states: {},

	init: function() {
		var tempStates = {};
		this.state = 0;

		// Grab the user-defined states
		var stateKeys = Object.keys(this.states);
		for (var i = 0; i < stateKeys.length; i++) {
			var key = stateKeys[i],
			    obj = this.states[key];

			if (typeof obj == "function") {
				this[key] = function(o, n, self) {
					return function() {
						o(self,arguments);
						self.setState(n);
					};
				}(obj, i, this);
			} else {
				this[key] = function(n, self) {
					return function() {
						self.setState(n);
					};
				}(i, this);
			}
			tempStates[key] = i;
		};

		this.states = tempStates;

		this.developer = false;
	},

	stateToText: function(state) {
        var keys = Object.keys(this.states);
        return keys[state];
    },

    setDeveloper: function(enabled) {
    	this.developer = enabled;
    },

	setState: function(state) {
		if (this.developer) {
            console.log(this.stateToText(this.state) + "->" + this.stateToText(state));
        }
		this.state = state;
	}

});