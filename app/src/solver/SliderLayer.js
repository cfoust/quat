var quat = quat || {};
quat.solver = quat.solver || {};

/* Layer for letting the user choose a new letter for a given one in
   the current word. */
quat.solver.SliderLayer = cc.Layer.extend({
    ctor:function (gameBounds, currentWord) {
        this._super();
        this.currentWord = currentWord;

        var fontSize = currentWord.fontSize,
            fontGap = currentWord.fontGap,
            halfFontGap = fontGap / 2;

        this.fontSize = fontSize;

        // Used for setting the elements to the proper position
        this.halfFontGap = halfFontGap;
        this.baseX = 0;

        // Store the bounds of all the letters
        var letterBounds = [];
        for (var i = 0; i < 4; i++) {
            letterBounds.push(currentWord.bounds[i]);
        }
        this.letterBounds = letterBounds;

        // Grab the y coordinate
        // Used to shift everything down
        var first = letterBounds[0],
            baseY = first.y + (first.height / 2),
            diff = 0,
            closestFound = false,
            closestIndex = -1;

        // We calculate how many letters can fit on the screen with our params
        var letterPoolCount = Math.ceil(gameBounds.height / fontSize) + 1;

        // Create a pool because we only need so many
        var letterPool = [],
            totalHeight = 0;
        for (var i = 0; i < letterPoolCount; i++) {
            // Initialize the label
            var letterLabel = new cc.LabelTTF("A", "Ubuntu", fontSize);
            letterLabel.x = this.baseX + halfFontGap;

            letterLabel.y = (fontSize / 2) + (i * (fontSize * 1.1));

            // Shifts everything down by a bit to align it with the current word
            if ((letterLabel.y > baseY) && (!closestFound)) {
                diff = baseY - letterLabel.y;
                closestIndex = i;
                this.closestIndex = closestIndex;
                closestFound = true;
            }

            totalHeight = Math.max(letterLabel.y + fontSize, totalHeight);

			// letterLabel.setColor(cc.color(176,196,222,255));
            letterLabel.zIndex = 1;
            this.addChild(letterLabel);
            letterPool.push(letterLabel);
        }
        // Shift the letters down by diff
        for (var i = 0; i < letterPool.length; i++) {
            var letterLabel = letterPool[i];
            letterLabel.y += diff;
        }
        this.letterPool = letterPool;

        // Add a background behind the letter selector
        var colorBackground = new cc.LayerColor(cc.color(25,25,112,255));

        // Make it the same dimensions as the selector
        colorBackground.width = currentWord.fontGap;
        colorBackground.height = totalHeight;
        colorBackground.x = this.baseX;
        colorBackground.y = diff;

        // Make it so the letters sit above it
        colorBackground.zIndex = 0;


        this.colorBackground = colorBackground;
        this.addChild(colorBackground);

        this.uppercase = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';

        return true;
    },

    appear: function(col) {
        var bounds = this.letterBounds[col],
            x = bounds.x + (bounds.width / 2);

        for (var i = 0; i < this.letterPool.length; i++) {
            // Initialize the label
            var letterLabel = this.letterPool[i];
            letterLabel.x = this.baseX + x;
        }
        this.colorBackground.x = this.baseX + x - this.halfFontGap;
    },

    applyTheme: function(theme) {
        this.colorBackground.setColor(theme.colors.darkForeground);

        var textColor = theme.colors.text;
        for (var i = 0; i < this.letterPool.length; i++) {
            this.letterPool[i].setColor(textColor);
        }
    },

    redrawFromLetter: function(index) {
        var uppercase = this.uppercase;

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
        var index = (letter.charCodeAt(0) - 65) + this.closestIndex;
        index %= this.uppercase.length;
        if (index < 0) {
            index += this.uppercase.length;
        }

        this.baseLetterIndex = index;

        this.redrawFromLetter(index);
    },

    letterAtY: function(y) {
        var bestIndex = -1,
            bestCloseness = 99999;

        for (var i = 0; i < this.letterPool.length; i++) {
            var label = this.letterPool[i],
                dist = Math.abs(y - label.y);

            if (dist < bestCloseness) {
                bestCloseness = dist;
                bestIndex = i;
            }
        }

        return this.letterPool[bestIndex].string;
    },

    getBaseLetter: function() {
        return this.letterPool[this.closestIndex].string;
    },

    setOffset: function(offset) {
        var newIndex = this.baseLetterIndex + Math.floor(offset / (this.fontSize * 1.1));
        newIndex %= this.uppercase.length;
        if (newIndex < 0) {
            newIndex += this.uppercase.length;
        }
        this.redrawFromLetter(newIndex);
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