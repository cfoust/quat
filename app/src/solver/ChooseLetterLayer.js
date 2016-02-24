var quat = quat || {};
quat.solver = quat.solver || {};

/* Layer for letting the user choose a new letter for a given one in
   the current word. */
quat.solver.ChooseLetterLayer = cc.Layer.extend({
    ctor:function (width, height, fontSize) {
        this._super();
        this.fontSize = fontSize;

        // We calculate how many letters can fit on the screen with our params
        var letterPoolCount = Math.ceil(height / fontSize) + 1;

        // Create a pool because we only need so many
        var letterPool = [];
        for (var i = 0; i < letterPoolCount; i++) {
            // Initialize the label
            var letterLabel = new cc.LabelTTF("A", "Ubuntu", fontSize);
            letterLabel.x = (width / 2);
            letterLabel.y = (fontSize / 2) + (i * fontSize);
			letterLabel.setColor(cc.color(176,196,222,255));
            letterLabel.zIndex = 1;
            this.addChild(letterLabel);
            letterPool.push(letterLabel);
        }
        this.letterPool = letterPool;

        // Add a background behind the letter selector
        var colorBackground = new cc.LayerColor(cc.color(25,25,112,255));

        // Make it the same dimensions as the selector
        colorBackground.width = width;
        colorBackground.height = height;
        colorBackground.x = 0;
        colorBackground.y = 0;

        // Make it so the letters sit above it
        colorBackground.zIndex = 0;


        this.colorBackground = colorBackground;
        this.addChild(colorBackground);

        this.uppercase = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';

        return true;
    },

    redrawFromLetter: function(letter) {
        var uppercase = this.uppercase;
        var index = letter.charCodeAt(0) - 65;

        for (var i = 0; i < this.letterPool.length; i++) {
            var letterLabel = this.letterPool[i];
            var newIndex = (index - i) % uppercase.length;
            if (newIndex < 0) {
                newIndex += uppercase.length;
            }
            letterLabel.string = uppercase[newIndex];
        }
    },

    setBaseLetter: function(letter) {
        letter = letter.toUpperCase();
        this.redrawFromLetter(letter);
        this.baseLetterIndex = letter.charCodeAt(0) - 65;
    },

    letterAtY: function(y) {
        var newIndex = this.baseLetterIndex - Math.floor(y / this.fontSize);
        newIndex %= this.uppercase.length;
        if (newIndex < 0) {
            newIndex += this.uppercase.length;
        }
        return this.uppercase[newIndex];
    },

    getBaseLetter: function() {
        return this.letterPool[0].string;
    },

    setOffset: function(offset) {
        var newIndex = this.baseLetterIndex + Math.floor(offset / this.fontSize);
        newIndex %= this.uppercase.length;
        if (newIndex < 0) {
            newIndex += this.uppercase.length;
        }
        this.redrawFromLetter(this.uppercase[newIndex]);
    },
	
	shift: function(delta) {
		var newIndex = this.baseLetterIndex + delta;
		newIndex %= this.uppercase.length;
        if (newIndex < 0) {
            newIndex += this.uppercase.length;
        }
		this.setBaseLetter(this.uppercase[newIndex]);
	}
});